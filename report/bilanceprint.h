#ifndef BILANCEPRINT_H
#define BILANCEPRINT_H

/**
 * Get balance data from default Table.
 * Table must be default table.
 * @author rbrodezh
 * @version 1.05
 */

#include <QVector>

#include "model/mtable.h"
#include "tools/utils.h"

class BilancePrint
{
public:
    bool isForBilancePrint;
    double   TotalRemainSum;

public:
    BilancePrint(QString tableName,QList<TableData> *data=0,bool sethtml=1);
    ~BilancePrint();
    double getTotalByCategory(QString Cat);
    QString printTotalForCategories();
    QString printTotalForCategoriesTbl();
    double getTotalPerMonthByCategory(QString mm,QString Cat);
    double getTotalPerMonthYearByCategory(QString mm,QString Cat);
    QString printTotalPerMonth(QString mm);
    QString printTotalPerMonthTbl(QString mm);
    QString printTotalForMonths();
    QString printBilance();

    QString printBilanceForTableAndMonth(QString tableName, QString mmYY);

private:
    QVector<QStringList> mtable;
        QString tableName;
        QStringList *categoryLst;
        QStringList *monthsLst;

        bool htmlprint;

        bool isInList(QStringList Lst,QString txt);
        void getCategories();
        void getMonths();
        void getMonthYears();
        QString hr();
        QString nl();

        QVector<QStringList> convertToQVector(QList<TableData> *data);
};

#endif // BILANCEPRINT_H
