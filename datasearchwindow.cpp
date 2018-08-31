#include "datasearchwindow.h"
#include "ui_datasearchwindow.h"

DataSearchWindow::DataSearchWindow(QWidget *parent, QList<TableData> *data) :
    QMainWindow(parent),
    ui(new Ui::DataSearchWindow)
{
    ui->setupUi(this);

    if(data!=0){
    //fillin data vector
    this->m_data = Helper::composeVector(data);

    }
    initFields();
}

DataSearchWindow::~DataSearchWindow()
{
    delete ui;
}

void DataSearchWindow::closeEvent(QCloseEvent *event){

    emit DataSearchReturn();
}

void DataSearchWindow::initFields()
{
    if(m_data.isEmpty()) return;
    QDate cdate= QDate::currentDate();
    QString dd= QString("%1").arg(cdate.day(),2,10,QChar('0'))+"/";
    QString mm= "/"+QString("%1").arg(cdate.month(),2,10,QChar('0'))+"/";
    QString yy= "/"+QString("%1").arg(cdate.year());
    ui->date_cb->addItem("/");
    ui->date_cb->addItem(dd);
    ui->date_cb->addItem(mm);
    ui->date_cb->addItem(yy);
    ui->date_cb->setCurrentIndex(1);
    QStringList noteLst= getNoteStringList();
    Helper::sort(noteLst);
    QStringList catLst= getCatStringList();
    Helper::sort(catLst);
    ui->category_cb->addItems(catLst);
    ui->note_cb->addItems(noteLst);
}
QStringList DataSearchWindow::getCatStringList(){
    /**
    *
    *Vector row 0,      1,      2,      3,     4
    *          id     cdate   cat     amount  note
    */
    QStringList slst;
    if(m_data.isEmpty()) return slst;
    for(int i=0; i< m_data.size(); i++){
        if(!slst.contains(m_data.at(i).at(2))){
            slst<< m_data.at(i).at(2);
        }
    }
    return slst;
}

QStringList DataSearchWindow::getNoteStringList(){
    /**
    *
    *Vector row 0,      1,      2,      3,     4
    *          id     cdate   cat     amount  note
    */
    QStringList slst;
    if(m_data.isEmpty()) return slst;
    for(int i=0; i< m_data.size(); i++){
        if(!slst.contains(m_data.at(i).at(4))){
            slst<< m_data.at(i).at(4);
        }
    }
    return slst;
}

void DataSearchWindow::makeSearch()
{
    //QWidget *busy= Helper::getBusyBox("Searching...");
   //Take search patterns from combo boxes
   QString d_m=ui->date_cb->currentText().trimmed();
   QString c_m=ui->category_cb->currentText().trimmed();
   QString n_m=ui->note_cb->currentText().trimmed();
   bool d_all=false,c_all=false,n_all=false;
   if(d_m.compare("*")==0 || d_m.compare("/")==0||d_m.isEmpty())
           d_all=true;
   if(c_m.compare("*")==0||c_m.isEmpty()) c_all=true;
   if(n_m.compare("*")==0) n_all=true;

   //search
   clearHyperLinks(); //clear old links if any

   double sum=0; //reset result

   QVector<QStringList> filtered= m_data;

   if(!d_all){
     filtered= filterByDate(filtered,d_m);

   }
   if(!c_all){
       filtered = filterByCategory(filtered,c_m);

   }
   if(!n_all){
       filtered = filterByNote(filtered,n_m);

   }
   /**
   if(d_all && c_all && n_all)
        filtered= m_data;
        **/
   if( !filtered.isEmpty() ){

       for(int i=0; i< filtered.size();i++){

           //element index is store at 0 column
       addHyperLink(makeSimpleItem(filtered.at(i)),filtered.at(i).at(0));
       //update sum
       bool ok=false;
       QString vv= filtered.at(i).at(3);
       double dd= vv.toDouble(&ok);
       if(!ok)
           throw "Double parsing error!";
       sum= sum+dd;
       }
   }
   //delete busy;

   updateSumLabel(sum);

}
void DataSearchWindow::updateSumLabel(double sum){
    ui->sumLabel->setText(QString("Sum= %0").arg(sum));
}
void DataSearchWindow::addHyperLink(QString label, QString linkidx){
 QLabel *lbl= new QLabel();
 lbl->setTextInteractionFlags(Qt::LinksAccessibleByMouse|
                              Qt::TextSelectableByMouse);
 lbl->setText("<a href=\'"+linkidx+"\'>"+label+"<\a>");
 connect(lbl,SIGNAL(linkActivated(QString)),this,SLOT(on_link_triggered(QString)));
 ui->formLayout->setWidget(linkidx.toInt(),QFormLayout::LabelRole,lbl);

}
void DataSearchWindow::on_link_triggered(QString link){

    bool ok;
    int idx;
    idx=link.toInt(&ok);
    if(!ok){
        qDebug("**** link idx error!");
    return;
    }
//show info for item by index idx
    //QString txt= mlist->getElmInfoTxt(idx);
    QString txt= makeItemInfo(m_data.at(idx));
    QMessageBox::information(this,"Item's details",txt);
}
void DataSearchWindow::clearHyperLinks(){

    QList<QLabel*> lbls=ui->sWidget->findChildren<QLabel*>();
        if(lbls.size()==0) return;
        for(int i=0; i< lbls.size();i++){

            ui->formLayout->removeWidget(lbls.at(i));
        QLabel *lbl= lbls.at(i);
        delete lbl;
        }
}
QString DataSearchWindow::makeSimpleItem(QStringList row){
   return QString("%0 %1 %2 %3")
            .arg(row.at(1)).arg(row.at(2)).arg(row.at(3)).arg(row.at(4));
}

QString DataSearchWindow::makeItemInfo(QStringList row){
   return QString("Date: %0, Cat: %1, Amount: %2, Note: %3")
            .arg(row.at(1)).arg(row.at(2)).arg(row.at(3)).arg(row.at(4));
}

QVector<QStringList> DataSearchWindow::filterByDate(const QVector<QStringList> &incom, QString sdate)
{
    //0 column is arranged for index
    return Helper::filterForColumn(1,incom,sdate);
}

QVector<QStringList> DataSearchWindow::filterByCategory(const QVector<QStringList> &incom, QString scategory)
{
    //0 column is arranged for index
    return Helper::filterForColumn(2,incom,scategory);
}

QVector<QStringList> DataSearchWindow::filterByNote(const QVector<QStringList> &incom, QString snote)
{
    //0 column is arranged for index
return Helper::filterForColumn(4,incom,snote);
}

void DataSearchWindow::on_btnFilter_clicked()
{
    makeSearch();
}
