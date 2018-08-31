#ifndef DATASEARCHWINDOW_H
#define DATASEARCHWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "model/mtable.h"
#include "tools/helper.h"

namespace Ui {
class DataSearchWindow;
}

class DataSearchWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void DataSearchReturn();

public:
    explicit DataSearchWindow(QWidget *parent = 0, QList<TableData> *data = 0);
    ~DataSearchWindow();

private slots:
    void on_link_triggered(QString link);

    void on_btnFilter_clicked();

private:
    Ui::DataSearchWindow *ui;

    /**
    * m_data
    *Data vector, every row is represented as string list of columns
    *Vector element column:  0,      1,      2,      3,     4
    *                       id     cdate    cat     amount  note
    * id is used internally by this class and is assigned during convertion
    * from QList<TableData> data to QVector by Helper::composeVector()
    */
    QVector<QStringList>  m_data;

private:
    void closeEvent(QCloseEvent *event);
    void initFields();
    QStringList getCatStringList();
    QStringList getNoteStringList();
    void makeSearch();
    QVector<QStringList> filterByDate(const QVector<QStringList> &incom, QString sdate);
    QVector<QStringList> filterByCategory(const QVector<QStringList> &incom, QString scategory);
    QVector<QStringList> filterByNote(const QVector<QStringList> &incom, QString snote);
    QString makeSimpleItem(QStringList row);
    void addHyperLink(QString label, QString linkidx);
    void clearHyperLinks();
    void updateSumLabel(double sum);
    QString makeItemInfo(QStringList row);
};

#endif // DATASEARCHWINDOW_H
