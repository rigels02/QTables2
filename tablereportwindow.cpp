#include "tablereportwindow.h"
#include "ui_tablereportwindow.h"

extern void printToFile(QString fileName, QString txt);


TableReportWindow::TableReportWindow(QWidget *parent, QString report) :
    QMainWindow(parent),
    ui(new Ui::TableReportWindow)
{
    ui->setupUi(this);
    //ui->txtEdit->setText(report);
    this->report= report;
    ui->txtEdit->setHtml(this->report);
}

TableReportWindow::~TableReportWindow()
{
    delete ui;
}

void TableReportWindow::closeEvent(QCloseEvent *event)
{
    emit tableReportReturn();

}

void TableReportWindow::on_actionSave_To_file_triggered()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setWindowTitle("Select file to save");
  #ifndef Q_OS_WIN
      fd.showMaximized();
  #endif

   int result = fd.exec();
   if(result == QDialog::Accepted){
       QStringList filename = fd.selectedFiles();
       if(filename.isEmpty() || filename.at(0).isEmpty()) return;
       printToFile(filename.at(0),this->report);
       QMessageBox::information(this,"Report","Report saved!");
    }
}
