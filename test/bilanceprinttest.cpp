#include "bilanceprinttest.h"



void BilancePrintTest::initTestCase()
{

}

void BilancePrintTest::cleanupTestCase()
{

}

void BilancePrintTest::init()
{

}

void BilancePrintTest::cleanup()
{

}

void BilancePrintTest::testHi()
{
    qDebug()<<"Hi test";
}

void BilancePrintTest::testBilancePrint()
{
    QList<TableData> data;
    for(int i=1; i<=3; i++){
        TableData td(QDate().currentDate(),QString("Cat_%0").arg(i),10+i,QString("Note_%0").arg(i));
        data.append(td);
    }
    BilancePrint bp("Table_1",&data,1);
    QString report = bp.printBilance();
    qDebug()<<report;
}
