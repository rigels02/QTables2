#include "selectionwindow.h"
#include "ui_selectionwindow.h"

SelectionWindow::SelectionWindow(QWidget *parent, IIOFile *repo) :
    QMainWindow(parent),
    ui(new Ui::SelectionWindow)
{
    ui->setupUi(this);
    this->repo= repo;
    if(repo==0) return;
    updateWidgetList(repo->getTablesInfo());
    ui->dateEdit->setDate(QDate::currentDate());
    connect(ui->listWidget,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(highlightChecked(QListWidgetItem*)));

}

SelectionWindow::~SelectionWindow()
{
    delete ui;
}

void SelectionWindow::closeEvent(QCloseEvent *event){

    emit selectionReturn();
}

void SelectionWindow::updateWidgetList(const QList<TableInfo> tables){

    ui->listWidget->clear();
    int idx=0;
    foreach (TableInfo ti, tables) {
       QString stitle= ti.getName();
       QListWidgetItem* wi1 = new QListWidgetItem(stitle);
       //wi1->setData(Qt::UserRole,note.getId());

       wi1->setData(Qt::UserRole,ti.getId());
       wi1->setData(555,ti.getName());
       wi1->setFlags(wi1->flags()|Qt::ItemIsUserCheckable);
       wi1->setCheckState(Qt::Unchecked);
       ui->listWidget->insertItem(idx,wi1);
       idx++;
    }
   // ui->lblInfo->setText(QString("Tables number is %0").arg(tables.size()));
}

void SelectionWindow::on_btnReport_clicked()
{
   QMap<int,QString> ids;
   QListWidgetItem *it;
   for(int i=0;i< ui->listWidget->count(); i++){
       it= ui->listWidget->item(i);
       if(it->checkState() == Qt::Checked){
        int ti= it->data(Qt::UserRole).toInt();
        QString n= it->data(555).toString();
        ids.insert(ti,n);
        }
   }
  if(ids.isEmpty()){
      QMessageBox::information(this,"Error","No any table selected!");
      return;
  }
  QDate selDate= ui->dateEdit->date();
  //qDebug()<< QString("selected date: %0").arg(selDate.toString("MM/yyyy"));
  QMapIterator<int,QString> i(ids);
  QString report;
    while (i.hasNext()) {
        i.next();
       // qDebug()<<QString("Table: id=%0, name= %1").arg(i.key()).arg(i.value());
        QList<TableData> data= repo->loadData(i.key());
        BilancePrint bi(i.value(),&data,true);
        report+=bi.printBilanceForTableAndMonth(i.value(),selDate.toString("MM/yyyy"));
    }
    //qDebug()<<report;
    m_tr = new TableReportWindow(0,report);
    connect(m_tr,SIGNAL(tableReportReturn()),this,SLOT(on_tableReportReturn()));
    m_tr->setWindowTitle(selDate.toString("MM/yyyy")+" Report");
    m_tr->show();
}

void SelectionWindow::on_tableReportReturn()
{
    delete m_tr;
}


void SelectionWindow::highlightChecked(QListWidgetItem *item)
{

    if(item->checkState()==Qt::Checked){
        item->setBackgroundColor(Qt::yellow);
    }else{
       // item->setBackgroundColor(defaultItemBkgColor);
        item->setBackgroundColor(Qt::white);
    }
}


