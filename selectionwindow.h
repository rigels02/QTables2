#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>

#include <QDebug>

#include "io/iiofile.h"
#include "report/bilanceprint.h"
#include "tablereportwindow.h"


namespace Ui {
class SelectionWindow;
}

class SelectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectionWindow(QWidget *parent = 0, IIOFile *repo=0);
    ~SelectionWindow();

    void closeEvent(QCloseEvent *event) override;

signals:
    void  selectionReturn();


private slots:
    void on_btnReport_clicked();
     void  on_tableReportReturn();
     void highlightChecked(QListWidgetItem*item);

private:
    Ui::SelectionWindow *ui;
    IIOFile *repo;
    TableReportWindow *m_tr;

private:
    void updateWidgetList(const QList<TableInfo> tables);
};

#endif // SELECTIONWINDOW_H
