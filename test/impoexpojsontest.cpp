#include "impoexpojsontest.h"

extern QList<MTable> mtables2(int);
extern QList<MTable> mtables0();
extern QList<MTable> mtables3(int nodataIdx);
extern void tprintToFile(QString fileName, QString txt);
extern QString treadTextFile(QString fileName);


void ImpoExpoJsonTest::initTestCase()
{

}

void ImpoExpoJsonTest::cleanupTestCase()
{

}

void ImpoExpoJsonTest::init()
{

}

void ImpoExpoJsonTest::cleanup()
{

}

void ImpoExpoJsonTest::testHi()
{
    qDebug()<<"Hi test!";
}


void ImpoExpoJsonTest::testJsonExpo()
{
  QList<MTable> tables= mtables2(-1);
  foreach (MTable table, tables) {
      qDebug()<< table.toString();
  }
  ImpoExpoJson expo;
  expo.expoJson("jsonExpo.txt",tables);
}

void ImpoExpoJsonTest::testJsonImpo()
{
    QList<MTable> tablesExp= mtables2(-1);
    QList<MTable> result;

    ImpoExpoJson impo;
    try{
    result= impo.impoJson("jsonExpo.txt");
    }catch(const char* msg ){
        qDebug()<< msg;
        QFAIL(msg);
    }
    QVERIFY(tablesExp.size()==result.size());
    for(int i=0; i< tablesExp.size();i++){
        MTable table1= tablesExp.at(i);
        MTable table= result.at(i);
       qDebug()<< table1.toString();
       QCOMPARE(table1.toString(),table.toString());
    }
}

void ImpoExpoJsonTest::testJsonExpoImpoEmptyData()
{
    //2nd table has no data
    QList<MTable> tablesExp= mtables2(2);
    QList<MTable> result;
    ImpoExpoJson expo;
    expo.expoJson("jsonExpoNoData.txt",tablesExp);

    ImpoExpoJson impo;
    try{
    result= impo.impoJson("jsonExpoNoData.txt");
    }catch(const char* msg ){
        qDebug()<< msg;
        QFAIL(msg);
    }
    QVERIFY(tablesExp.size()==result.size());
    for(int i=0; i< tablesExp.size();i++){
        MTable table1= tablesExp.at(i);
        MTable table= result.at(i);
       qDebug()<< table1.toString();
       QCOMPARE(table1.toString(),table.toString());
    }
}

void ImpoExpoJsonTest::testJsonExpoImpoEmptyData1()
{
    QList<MTable> tablesExp= mtables0();
    QList<MTable> result;
    ImpoExpoJson expo;
    expo.expoJson("jsonExpoNoData.txt",tablesExp);

    ImpoExpoJson impo;
    try{
    result= impo.impoJson("jsonExpoNoData.txt");
    }catch(const char* msg ){
        qDebug()<< msg;
        QFAIL(msg);
    }
    QVERIFY(tablesExp.size()==result.size());
    for(int i=0; i< tablesExp.size();i++){
        MTable table1= tablesExp.at(i);
        MTable table= result.at(i);
       qDebug()<< table1.toString();
       QCOMPARE(table1.toString(),table.toString());
    }
}

void ImpoExpoJsonTest::testJsonExpoImpoData()
{
    QList<MTable> tablesExp= mtables3(-1);
    QList<MTable> result;
    ImpoExpoJson expo;
    expo.expoJson("jsonExpoData.txt",tablesExp);

    ImpoExpoJson impo;
    try{
    result= impo.impoJson("jsonExpoData.txt");
    }catch(const char* msg ){
        qDebug()<< msg;
        QFAIL(msg);
    }
    QVERIFY(tablesExp.size()==result.size());
    for(int i=0; i< tablesExp.size();i++){
        MTable table1= tablesExp.at(i);
        MTable table= result.at(i);
       qDebug()<< table1.toString();
       QCOMPARE(table1.toString(),table.toString());
    }
}
