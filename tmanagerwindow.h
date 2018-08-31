#ifndef TMANAGERWINDOW_H
#define TMANAGERWINDOW_H

#include <QMainWindow>
#include "QMessageBox"
#include <QInputDialog>
#include <QListWidgetItem>

#include "model/mtable.h"
#include "io/iiofile.h"


namespace Ui {
class TManagerWindow;
}

class TManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TManagerWindow(QWidget *parent = 0,int currentTabId= -1, IIOFile *repo=0);
    ~TManagerWindow();

    void closeEvent(QCloseEvent *event) override;

signals:

    void tmanagerReturn( const int currentTableId);

private slots:
    void on_btnAdd_clicked();

    void on_btnRename_clicked();

    void on_btnDelete_clicked();

    void on_btnSelect_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionDelete_ALL_triggered();

private:
    Ui::TManagerWindow *ui;
    int currentTableId;
    IIOFile *m_repo;
    //QList<TableInfo> *m_Tables;
    void updateWidgetList(const QList<TableInfo> tables);
    QString simpleItem(TableInfo ti);
};

#endif // TMANAGERWINDOW_H
