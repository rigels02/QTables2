#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QDebug>


//QSettings AppSettings("QTable2Settings.ini",QSettings::IniFormat);

AppSettings settings("QTable2Settings.ini");

static QIcon iconN, iconNo;

QList<TableData> populateTestData();

const QString MainWindow::CURRTABLEIDX="currentTableId";

MainWindow::MainWindow(QWidget *parent, IIOFile *repository) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->repo = repository;

    iconN.addFile(":/images/images/note.png",QSize(),QIcon::Normal,QIcon::On);
    iconNo.addFile(":/images/images/nonote.png",QSize(),QIcon::Normal,QIcon::On);
    //AppSettings.setValue("savedword","Hi there!");
    //currentTableId= AppSettings.value(MainWindow::CURRTABLEIDX,-1).toInt();
    restoreSettings();
    //Init data
    //QList<TableData> data= populateTestData();
#ifdef Q_OS_WIN
    QFont font;
    font.setPointSize(10);
    ui->listWidget->setFont(font);
#endif
   updateListView();

  // qDebug()<<APP_VERSION;
}

QList<TableData> populateTestData(){
    QList<TableData> data;
    for(int i=1; i<=3; i++){
        QString note=(i==2)?"":QString("Note%0").arg(i);
        TableData dd(QDate().currentDate(),QString("Cat%0").arg(i),10+i,note);
        data.append(dd);
    }
    return data;
}

void MainWindow::restoreSettings(){
   // currentTableId= AppSettings.value(MainWindow::CURRTABLEIDX,-1).toInt();
    currentTableId = settings.readTableIdx();

}
void MainWindow::storeSettings(){
 //AppSettings.setValue(MainWindow::CURRTABLEIDX,currentTableId);
    settings.saveTableIdx(currentTableId);
}

void MainWindow::updateListView(){
    data.clear();
    if(currentTableId> -1){
     try {
     data= repo->loadData(currentTableId);
        }catch(const char* msg){
            QMessageBox::critical(this,"Error",
                                  QString("Cannot load data!\n%0").arg(msg));
            return;
        }
    }
   // addSimpleItems(data);
   addWidgetItems(data);
   updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::findTableName(QList<TableInfo> tables,int id){
    foreach (TableInfo ti, tables) {
        if(ti.getId()== id){

            return ti.getName();
        }
    }
    return "";
}
void MainWindow::updateStatus() {
    QString fmt("SUM= %0%1");
    QString mstatus;
    QString tableInfo="";
    if(currentTableId> -1){
        QList<TableInfo> ti= repo->getTablesInfo();
        tableInfo= QString(", Table:%0").arg(findTableName(ti,currentTableId));

    }
    if(this->data.isEmpty()){
        mstatus= fmt.arg(0.0).arg(tableInfo);

    }else{
        double sum=0.0;
        foreach (TableData td, data) {
            sum= sum+td.getAmount();
        }
        mstatus= fmt.arg(sum).arg(tableInfo);
    }
    ui->lblStatus->setText(mstatus);
}
void MainWindow::addSimpleItems(const QList<TableData> &data){
    QStringList slst= QStringList();
    foreach (TableData dd, data) {
        slst<< makeItemString(dd);
    }
    ui->listWidget->clear();
    ui->listWidget->addItems(slst);
    /**
    int sz= ui->listWidget->count();
    for(int i=0; i< sz; i++){
       QListWidgetItem *wit= ui->listWidget->item(i);
       wit->setIcon(iconT);
    }
    **/
}


void MainWindow::addWidgetItems(const QList<TableData> &data)
{
    ui->listWidget->clear();
    int idx=0;
    foreach (TableData dd, data) {
       QString stitle= makeItemString(dd);
       QListWidgetItem* wi1 = new QListWidgetItem(stitle);
       //wi1->setData(Qt::UserRole,note.getId());
       if(!dd.getNote().isEmpty()){

           wi1->setIcon(iconN);
       }else{
           wi1->setIcon(iconNo);
       }

       ui->listWidget->insertItem(idx,wi1);
       idx++;
    }


}
QString MainWindow::makeItemString(TableData dd){
    QString fmt="%0/%1/%2\n%3\t%4\t%5";

   return fmt.arg(dd.getCdate().day(),2,10)
          .arg(dd.getCdate().month(),2,10)
          .arg(dd.getCdate().year())
          .arg(dd.getCat())
          .arg(dd.getAmount())
          .arg(dd.getNote());

}
/**
void MainWindow::on_btnSave_clicked()
{
   AppSettings.setValue("savedword","Hi there!");

}

void MainWindow::on_btnRetriev_clicked()
{

    QVariant val = AppSettings.value("savedword","None");
    qDebug()<<val.toString();

}
**/

void MainWindow::on_btnAdd_clicked()
{
    if(currentTableId < 0){
        QMessageBox::information(this,"Info","Please, create table first!");
        return;
    }
    UpdateDialog udlg(nullptr,&data);
    udlg.setWindowTitle("Add record");
#ifndef Q_OS_WIN
    udlg.showMaximized();
#endif
    udlg.addForm();
   int result= udlg.exec();
   if(result==QDialog::Accepted){
    TableData dd= udlg.fromForm();
    QString msg= QString("Accepted Result %0: data= %1").arg(result).arg(dd.toString());

    qDebug()<<msg;
    data.append(dd);
    repo->saveData(currentTableId,data);
    //QMessageBox::information(this,"Info",msg);
    updateListView();
    return;
   }


}

void MainWindow::on_btnUpdate_clicked()
{
 /***
 this->updFrm = new UpdateForm();
//updFrm->setAttribute(Qt::WA_DeleteOnClose);
    connect(updFrm,SIGNAL(updateFormAccepted(TableData)),this,SLOT(on_updateFormAccepted(TableData)));
    connect(updFrm,SIGNAL(updateFormCanceled()),this,SLOT(on_updateFormCanceled()));

    updFrm->show();
  ***/
    if(currentTableId < 0){
        return;
    }
    int idx = ui->listWidget->currentIndex().row();
    if(idx< 0) return;
    UpdateDialog udlg(nullptr,&data);
    udlg.setWindowTitle(QString("Update record #%0").arg(idx+1));

#ifndef Q_OS_WIN
    udlg.showMaximized();
#endif

    udlg.toForm(idx);
    int result= udlg.exec();

    if(result==QDialog::Accepted){
        TableData dd= udlg.fromForm();
        QString msg= QString("Accepted Result %0: data= %1").arg(result).arg(dd.toString());

        qDebug()<<msg;
        data.replace(idx,dd);

        repo->saveData(currentTableId,data);
        //QMessageBox::information(this,"Info",msg);
        updateListView();
        return;
    }


}


void MainWindow::on_actionManage_Tables_triggered()
{
    m_tm= new TManagerWindow(this,this->currentTableId,this->repo);
    connect(m_tm,SIGNAL(tmanagerReturn(int)),this,SLOT(on_tmanagerReturn(int)));
    m_tm->setWindowTitle("Table Manager");
    m_tm->show();
}


void MainWindow::on_tmanagerReturn(const int currentTableId)
{
    delete m_tm;
    this->currentTableId = currentTableId;
    storeSettings();
    updateListView();
}

void MainWindow::on_tableReportReturn()
{
    delete m_tr;

}

void MainWindow::on_dataSearchReturn()
{

 delete m_ds;
 this->show();
}



void MainWindow::on_btnDelete_clicked()
{
    int idx = ui->listWidget->currentIndex().row();
    if(idx< 0 ) return;
    TableData dd= this->data.at(idx);
    int res= QMessageBox::question(this,"Delete?",
                                   QString("Delete record #%0?\n%1").arg(idx+1).arg(dd.print()),
                                   QMessageBox::Ok,QMessageBox::Cancel
                                   );
    if(res== QMessageBox::Ok){
      this->data.removeAt(idx);
      repo->saveData(currentTableId,this->data);
      updateListView();
    }
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    on_btnUpdate_clicked();
}

void MainWindow::on_actionTable_Report_triggered()
{
    if(currentTableId < 0) return;
    QString tableName;
    QList<TableInfo> tables = repo->getTablesInfo();
    foreach (TableInfo ti, tables) {
        if(ti.getId()==currentTableId){
            tableName= ti.getName();
            break;
        }

    }

    BilancePrint bp(tableName,&data,true);
    QString report = bp.printBilance();
    m_tr = new TableReportWindow(nullptr,report);
    connect(m_tr,SIGNAL(tableReportReturn()),this,SLOT(on_tableReportReturn()));
    m_tr->show();
}
void MainWindow::sortByDate()
{
    if(currentTableId<0 ) return;

    Helper::sortByDate(data);
    repo->saveData(currentTableId,data);
    updateListView();

}

void MainWindow::sortByDateLastFirst()
{
    if(currentTableId<0 ) return;

    Helper::sortByDateReverse(data);
    repo->saveData(currentTableId,data);
    updateListView();
}

void MainWindow::on_actionSort_By_Date_triggered()
{
    sortByDate();
}

void MainWindow::on_actionData_Filter_triggered()
{
    m_ds = new DataSearchWindow(nullptr,&data);
    connect(m_ds,SIGNAL(DataSearchReturn()),this,SLOT(on_dataSearchReturn()));
    this->hide();
    m_ds->show();
}

QString readTextFile(QString fileName){
    QFile fi(fileName);
    fi.open(QFile::ReadOnly);
    QTextStream ds(&fi);
    ds.setCodec("UTF-8");
    QString txt;
    txt = ds.readAll();
    fi.close();
    return txt;
}


void MainWindow::on_actionImport_Old_triggered()
{
    ImpExp impo;
    doImport(impo);

}

void printToFile(QString fileName, QString txt){
    QFile fi(fileName);
    fi.open(QFile::WriteOnly|QFile::Truncate);
    QTextStream ds(&fi);
    ds.setCodec("UTF-8");
    ds << txt;
    fi.close();
}

void MainWindow::on_actionExport_Old_triggered()
{
    ImpExp expo;
    doExport(expo);

}

void MainWindow::on_actionImport_CSV_triggered()
{
    CsvExpoImpoDlg dlg;
#ifndef Q_OS_WIN
    dlg.showMaximized();
#endif
    int res = dlg.exec();
    if(res != QDialog::Accepted)
             return;
    QString delimiter = dlg.getDelimitersInfo();

 T_CSV<MTable> csvImpo(delimiter);
    doImport(csvImpo);
}

void MainWindow::on_actionExport_CSV_triggered()
{
    CsvExpoImpoDlg dlg;
#ifndef Q_OS_WIN
    dlg.showMaximized();
#endif
    int res = dlg.exec();
    if(res != QDialog::Accepted)
             return;
    QString delimiter = dlg.getDelimitersInfo();
     T_CSV<MTable> csvExpo(delimiter);
    doExport(csvExpo);
}


void MainWindow::on_selectionReturn(){
     delete m_sw;
}

void MainWindow::on_actionTablesMonthReport_triggered()
{
    m_sw= new SelectionWindow(this,this->repo);
    connect(m_sw,SIGNAL(selectionReturn()),this,SLOT(on_selectionReturn()));
    //m_sw->setWindowTitle("Table Manager");
    m_sw->show();
}


void MainWindow::doExport(IExportImport<MTable> &expo){
    QFileDialog fd;
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setWindowTitle("Select/type file to export");
  #ifndef Q_OS_WIN
      fd.showMaximized();
  #endif

   int result = fd.exec();
   if(result == QDialog::Accepted){
       QStringList filename = fd.selectedFiles();
       if(filename.isEmpty() || filename.at(0).isEmpty()) return;

       QList<MTable> tables;

       try{
       tables= repo->loadAll();
        expo.exportData(filename.at(0),tables);
       }catch(const char* msg){
           QMessageBox::critical(this,"Export error",
                                 QString("Cannot load data: %0").arg(msg),
                                 QMessageBox::Ok);
           return;
       }

       QMessageBox::information(this,
                                "Export",
                                QString("Data export completed to file %0!")
                                .arg(filename.at(0)),QMessageBox::Ok);

   }

}

void MainWindow::doImport(IExportImport<MTable> &impo){
    QFileDialog fd;
    fd.setFileMode(QFileDialog::ExistingFile);
    fd.setWindowTitle("Select file to import from");
   #ifndef Q_OS_WIN
    fd.showMaximized();
   #endif

    int result = fd.exec();
    if(result == QDialog::Accepted){
        QStringList filename = fd.selectedFiles();
        if(filename.isEmpty() || filename.at(0).isEmpty()) return;
        int conf= QMessageBox::question(this,"Confirm Import",
                                        "Old data will be deleted!!\nAre you sure to continue??",
                                        QMessageBox::Ok,QMessageBox::Cancel);
        if(conf== QMessageBox::Cancel) return;

        QList<MTable> tables ;

        try{

        tables = impo.importData(filename[0]);
       // tables= jsonImpo.impoJson(filename[0]);
        if(tables.isEmpty()) return;
        repo->saveAll(tables);
        }catch(const char* msg){
            QMessageBox::critical(this,"Import error",
                                  QString("Error: %0").arg(msg),
                                  QMessageBox::Ok);
            return;
        }catch(QString msg){
            QMessageBox::critical(this,"Import error",
                                  QString("Error: %0").arg(msg),
                                  QMessageBox::Ok);
            return;
        }

        QList<TableInfo> ti = repo->getTablesInfo();
        this->currentTableId = ti.at(0).getId();
        storeSettings();
        QMessageBox::information(this,"Import",
                                 QString("Data import completed from file %0!")
                                 .arg(filename[0]),
                                 QMessageBox::Ok);

      updateListView();
    }

}

void MainWindow::on_actionImport_JSON_triggered()
{

  ImpoExpoJson jsonImpo;
  IExportImport<MTable>& impo = jsonImpo;
    doImport(impo);
}

void MainWindow::on_actionExport_JSON_triggered()
{
    ImpoExpoJson jsonExpo;
    IExportImport<MTable>& expo = jsonExpo;

    doExport(expo);

}

void MainWindow::on_actionInfo_triggered()
{
    QFile fi(":/doc/TableInfoinfo.html");
    fi.open(QFile::ReadOnly);
    QTextStream ts(&fi);
    ts.setCodec("UTF-8");
    QString report;
    report = QString("APP VER.= ")+APP_VERSION+ts.readAll();
    fi.close();
    m_tr = new TableReportWindow(0,report);
    connect(m_tr,SIGNAL(tableReportReturn()),this,SLOT(on_tableReportReturn()));
    m_tr->setWindowTitle("Info");
    m_tr->show();

}
