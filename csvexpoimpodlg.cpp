#include "csvexpoimpodlg.h"
#include "ui_csvexpoimpodlg.h"

CsvExpoImpoDlg::CsvExpoImpoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvExpoImpoDlg)
{
    ui->setupUi(this);
}

CsvExpoImpoDlg::~CsvExpoImpoDlg()
{
    delete ui;
}

QString CsvExpoImpoDlg::getDelimitersInfo(){

   if( ui->rbtnComma->isChecked()) return ",";
   if( ui->rbtnSpec->isChecked()) return "|";
   if( ui->rbtnTab->isChecked()) return "\t";
   return ",";
}
