#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include <QFileDialog>
//#include <QSettings>
//#include <QtGlobal>

#include "model/mtable.h"
#include "io/iiofile.h"
#include "io/appsettings.h"
#include "updatedialog.h"
#include "tmanagerwindow.h"
#include "report/bilanceprint.h"
#include "tablereportwindow.h"
#include "tools/helper.h"
#include "datasearchwindow.h"
#include "expoimpo/csvexpoimpo.h"
#include "expoimpo/old/impexp.h"
#include "expoimpo/impoexpojson.h"
#include "csvexpoimpodlg.h"
#include "selectionwindow.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
static const QString CURRTABLEIDX;

public:
    explicit MainWindow(QWidget *parent = 0, IIOFile *repository=0);
    ~MainWindow();


void restoreSettings();
void storeSettings();


private slots:
    void on_btnAdd_clicked();

    void on_btnUpdate_clicked();

    void on_actionManage_Tables_triggered();
    void on_tmanagerReturn(const int currentTableId);
    void on_tableReportReturn();
    void on_dataSearchReturn();
    void on_btnDelete_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_actionTable_Report_triggered();

    void on_actionSort_By_Date_triggered();

    void on_actionData_Filter_triggered();


    void on_actionImport_Old_triggered();

    void on_actionExport_Old_triggered();

    void on_actionImport_CSV_triggered();

    void on_actionExport_CSV_triggered();

    void on_selectionReturn();
    void on_actionTablesMonthReport_triggered();

    void on_actionImport_JSON_triggered();

    void on_actionExport_JSON_triggered();

    void on_actionInfo_triggered();

private:
    Ui::MainWindow *ui;
    TManagerWindow *m_tm;
    TableReportWindow *m_tr;
    DataSearchWindow *m_ds;
    SelectionWindow *m_sw;

    IIOFile *repo;
    int currentTableId;
    QList<TableData> data;

    QString makeItemString(TableData dd);
    void addSimpleItems(const QList<TableData> &data);
    void addWidgetItems(const QList<TableData> &data);

    void updateListView();
    void updateStatus();
    void sortByDate();
    void sortByDateLastFirst();
    QString findTableName(QList<TableInfo> tables, int id);
    void doExport(IExportImport<MTable> &expo);
    void doImport(IExportImport<MTable> &impo);
};

#endif // MAINWINDOW_H
