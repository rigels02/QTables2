#ifndef HELPER_H
#define HELPER_H

#include <QList>
#include <QWidget>
#include <QVBoxLayout>
#include <QProgressDialog>

#include "model/mtable.h"

class Helper
{
public:
    Helper();
    static QVector<QStringList> composeVector(const QList<TableData> *data);
    static void sortByCategory(QList<TableData> &slist);
    static void sortByDate(QList<TableData> &slist);
    static void sortByDateReverse(QList<TableData> &slist);
    static void sort(QStringList &slist);
    static QVector<QStringList> filterForColumn(int col, const QVector<QStringList> &incom, QString smatch);
    static QWidget *getBusyBox(QString msg);
};

#endif // HELPER_H
