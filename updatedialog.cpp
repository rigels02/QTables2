#include "updatedialog.h"
#include "ui_updatedialog.h"

#include <QDebug>

UpdateDialog::UpdateDialog(QWidget *parent, QList<TableData> *data) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
    ui->edDate->setDisplayFormat("dd/MM/yyyy");
    ui->edAmount->setValidator(new QDoubleValidator(-999999,999999,2,this));
    /****
    ui->btnUpdate->setStyleSheet(
    "QPushButton {background-color: red;border-width: 2px;"
    "border-radius: 10px;border-color: beige;font: bold 14px;"
    "min-width: 10em;padding: 6px;}"
    "QPushButton:pressed {background-color: rgb(224, 0, 0);"
    "border-style: inset;}");
    ***/
    //int width = box->fontMetrics().width(str);
    //QString spacing = "QCheckBox{spacing:%1px}";
    //box->setStyleSheet( spacing.arg(box->width() - width - 25) );

    m_data= data;
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

bool UpdateDialog::isValid(QString &info) const
{
    if(ui->cbCat->currentText().isEmpty()
            || ui->edAmount->text().isEmpty()){
        info= "Category or Amount fields must not be empty!";
        return false;
    }
    return true;
}

TableData UpdateDialog::fromForm() const
{
    TableData data;

    data.setCdate(ui->edDate->date());
    data.setCat(ui->cbCat->currentText());
    data.setAmount(ui->edAmount->text().toDouble());
    QString note= ui->cbNote->currentText().trimmed();
    data.setNote(note);
    return data;
}

void UpdateDialog::toForm(int selIdx)
{
    if(m_data==0) return;
    if(selIdx< 0 || selIdx> m_data->size()) return;

    QStringList catLst= categoryList();
    QStringList noteLst= noteList();
    TableData data= m_data->at(selIdx);
    ui->edDate->setDate(data.getCdate());
    ui->edAmount->setText(QString("%0").arg(data.getAmount()));
    ui->cbCat->addItems(catLst);
    ui->cbNote->addItems(noteLst);
    ui->cbCat->setCurrentIndex(catLst.indexOf(data.getCat()));
    ui->cbNote->setCurrentIndex(noteLst.indexOf(data.getNote()));

}

void UpdateDialog::addForm()
{
    ui->edDate->setDate(QDate().currentDate());
    ui->edAmount->setText("0.0");

    QStringList catLst= categoryList();
    QStringList noteLst= noteList();
    ui->cbCat->addItems(catLst);
    ui->cbNote->addItems(noteLst);


}

void UpdateDialog::on_btnUpdate_clicked()
{
    QString info;
    if(!isValid(info)){

        //QMessageBox::information(this,"Error","info",QMessageBox::Ok,QMessageBox::Cancel);
         QMessageBox::information(this,"Error",info);
        return;
    }
 this->accept();
}

QStringList UpdateDialog::categoryList() const
{
    QStringList lst;
     if(m_data==0) return lst;
    for(int i=0; i<m_data->size();i++){
        TableData el= m_data->at(i);
        if( !lst.contains(el.getCat(),Qt::CaseInsensitive)){
            lst<< el.getCat();
        }
    }

   return lst;
}

QStringList UpdateDialog::noteList() const
{
    QString empty=" ";
    QStringList lst;
     if(m_data==0) return lst;
     for(int i=0; i<m_data->size();i++){
         TableData el= m_data->at(i);
         QString note= el.getNote().trimmed();
         if(note.isEmpty())
             note= empty;
         if( !lst.contains(note,Qt::CaseInsensitive)){
             lst<< note;
         }
     }
     return lst;
}





void UpdateDialog::on_btnCat_clicked()
{
  bool ok=false;
  QString scat = QInputDialog::getText(this,"Input","Input category: ",QLineEdit::Normal,"",&ok);
  if(ok && !scat.isEmpty()){
      qDebug()<<QString("Result %0").arg(scat);
      ui->cbCat->addItem(scat);
      ui->cbCat->setCurrentIndex(ui->cbCat->count());
      ui->cbCat->setCurrentText(scat);
  }
}

void UpdateDialog::on_btnNote_clicked()
{
    bool ok=false;
    QString snote = QInputDialog::getText(this,"Input","Input Note: ",QLineEdit::Normal,"",&ok);
    if(ok && !snote.isEmpty()){
        qDebug()<<QString("Result %0").arg(snote);
        ui->cbNote->addItem(snote);

        ui->cbNote->setCurrentIndex(ui->cbNote->count());
        ui->cbNote->setCurrentText(snote);
    }
}
