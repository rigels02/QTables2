#ifndef TABLEREPORTWINDOW_H
#define TABLEREPORTWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class TableReportWindow;
}

class TableReportWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void tableReportReturn();

public:
    explicit TableReportWindow(QWidget *parent = 0,QString report="");
    ~TableReportWindow();

private slots:
    void on_actionSave_To_file_triggered();

private:
    Ui::TableReportWindow *ui;
    QString report;

private:
    void closeEvent(QCloseEvent *event);
};

#endif // TABLEREPORTWINDOW_H
