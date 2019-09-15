#include "tmanagerwindow.h"
#include "ui_tmanagerwindow.h"

static QIcon iconN;


TManagerWindow::TManagerWindow(QWidget *parent, int currentTabId, IIOFile *repo) :
    QMainWindow(parent),
    ui(new Ui::TManagerWindow)
{
    ui->setupUi(this);
    this->currentTableId= currentTabId;
    iconN.addFile(":/images/images/note.png",QSize(),QIcon::Normal,QIcon::On);
    this->m_repo= repo;
#ifdef Q_OS_WIN
            QFont font;
            font.setPointSize(10);
            ui->listWidget->setFont(font);
#endif

    updateWidgetList(repo->getTablesInfo());

}

TManagerWindow::~TManagerWindow()
{
    delete ui;
}

QString TManagerWindow::simpleItem(TableInfo ti){
   return QString("%0\n\t%1")
           .arg(ti.getName())
           .arg(ti.getDate()
           .toString("dd/MM/yyyy HH:mm:ss"));
}

void TManagerWindow::updateWidgetList(const QList<TableInfo> tables){

    ui->listWidget->clear();
    int idx=0;
    foreach (TableInfo ti, tables) {
       QString stitle= simpleItem(ti);
       QListWidgetItem* wi1 = new QListWidgetItem(stitle);
       //wi1->setData(Qt::UserRole,note.getId());
       if(ti.getId()==currentTableId){

           wi1->setIcon(iconN);
       }
       wi1->setData(Qt::UserRole,ti.getId());
       ui->listWidget->insertItem(idx,wi1);
       idx++;
    }
    ui->lblInfo->setText(QString("Tables number is %0").arg(tables.size()));
}
void TManagerWindow::closeEvent(QCloseEvent *event)
{
    /**
    qDebug()<<"Are you closing???";
   int res= QMessageBox::information(this,"Closing","Are you closing?",QMessageBox::Ok,QMessageBox::Cancel);
  if(res== QMessageBox::Ok){
      qDebug()<<"Closing...";

  }
  **/

  emit tmanagerReturn(this->currentTableId);
}

void TManagerWindow::on_btnAdd_clicked()
{
    bool ok=false;
    QString ntable = QInputDialog::getText(this,"Add Table","Input Table name: ",QLineEdit::Normal,"",&ok);
    if(ok && !ntable.isEmpty()){
        qDebug()<<QString("Result %0").arg(ntable);
        TableInfo ti = m_repo->createTable(ntable);
        currentTableId= ti.getId();
        updateWidgetList(m_repo->getTablesInfo());
        QMessageBox::information(this,"Info",QString("Table %0 is created!").arg(ntable));

    }

}

void TManagerWindow::on_btnRename_clicked()
{
   QListWidgetItem *wi= ui->listWidget->currentItem();
   if(wi == nullptr) return;
   int idx= wi->data(Qt::UserRole).toInt();
   bool ok;
   QString ntable = QInputDialog::getText(this,"Rename Table","Table new name: ",QLineEdit::Normal,"",&ok);
   if(ok && !ntable.isEmpty()){
       qDebug()<<QString("Result %0").arg(ntable);
       const TableInfo *ti = m_repo->renameTable(idx,ntable);
       currentTableId= ti->getId();
       updateWidgetList(m_repo->getTablesInfo());
       QMessageBox::information(this,"Info",QString("Table %0 was renamed!").arg(ntable));

   }
}

void TManagerWindow::on_btnDelete_clicked()
{
    QListWidgetItem *wi= ui->listWidget->currentItem();
    if(wi == nullptr) return;
    int idx= ui->listWidget->currentRow();
    int id= wi->data(Qt::UserRole).toInt();
    QList<TableInfo> tables = m_repo->getTablesInfo();

    int res= QMessageBox::question(this,"Delete?",
                          QString("Sure to delete table %0?").arg(tables.at(idx).getName()),
                          QMessageBox::Ok,QMessageBox::Cancel
                          );
    if(res == QMessageBox::Ok){
        m_repo->deleteTable(id);
        QList<TableInfo> tables= m_repo->getTablesInfo();
        if(tables.size()>0){
            currentTableId=tables[0].getId();
        }else {
            currentTableId= -1;
        }
        updateWidgetList(tables);

        QMessageBox::information(this,"Info",QString("Table was deleted!"));

    }
}

void TManagerWindow::on_btnSelect_clicked()
{
    QListWidgetItem *wi= ui->listWidget->currentItem();
    if(wi == nullptr) return;
    //int idx= ui->listWidget->currentRow();
    int id= wi->data(Qt::UserRole).toInt();
    currentTableId = id;
    updateWidgetList(m_repo->getTablesInfo());

}

void TManagerWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    on_btnSelect_clicked();
}

void TManagerWindow::on_actionDelete_ALL_triggered()
{
    int res= QMessageBox::question(this,"Delete ALL?!",
                                   "Are You sure? Delete ALL Tables?!",
                                   QMessageBox::Ok,QMessageBox::Cancel
                                   );
    if(res== QMessageBox::Ok){
       bool ok= m_repo->deleteAll();
       if(!ok){
           QMessageBox::critical(this,"Error",
                                 "There was an error to delete tables!"
                                 );
       this->currentTableId= -1;
       return;
       }
       QMessageBox::information(this,"Completed","All tables deleted!");
       this->currentTableId= -1;
       ui->listWidget->clear();
      ui->lblInfo->setText("");
    }
}
