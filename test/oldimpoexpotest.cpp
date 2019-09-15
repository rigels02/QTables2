#include "oldimpoexpotest.h"



void OldImpoExpoTest::initTestCase()
{

}

void OldImpoExpoTest::cleanupTestCase()
{

}

void OldImpoExpoTest::init()
{

}

void OldImpoExpoTest::cleanup()
{

}

void OldImpoExpoTest::testHi()
{
    qDebug()<<"Hi test!";
}

QList<MTable> mtables0(){
    QList<MTable> tables;
    for(int i=1; i<= 3; i++){
        TableInfo ti(0,QString("Table_%0").arg(i),QDateTime::currentDateTime());
        MTable table(ti);

      tables.append(table);
    }
    return tables;
}

QList<MTable> mtables1(int nodataIdx){
    QList<MTable> tables;
    for(int i=1; i<= 3; i++){
        TableInfo ti(0,QString("Table_%0").arg(i),QDateTime::currentDateTime());
        MTable table(ti);
        if(i!= nodataIdx){
            for(int d=1; d<= 3; d++){
                TableData td(QDate::currentDate(),
                             QString("Cat_%0%1").arg(i).arg(d),
                             10.34+d,
                             QString("Note_%0%1").arg(i).arg(d));
             table.addData(td);
            }
        }
      tables.append(table);
    }
    return tables;
}

QList<MTable> mtables2(int nodataIdx){
    QList<MTable> tables;
    for(int i=1; i<= 3; i++){
        TableInfo ti(0,QString("Table_%0").arg(i),QDateTime::currentDateTime());
        MTable table(ti);
        if(i!= nodataIdx){
            for(int d=1; d<= 3; d++){
                TableData td(QDate::currentDate(),
                             QString("Āboli_%0%1").arg(i).arg(d),
                             10.34+d,
                             QString("Note_%0%1").arg(i).arg(d));
             table.addData(td);
            }
        }
      tables.append(table);
    }
    return tables;
}

QList<MTable> mtables3(int nodataIdx){
    QList<MTable> tables;
    for(int i=1; i<= 3; i++){
        TableInfo ti(0,QString("Table_%0").arg(i),QDateTime::currentDateTime());
        MTable table(ti);
        if(i!= nodataIdx){
            for(int d=1; d<= 3; d++){
                TableData td(QDate::currentDate(),
                             QString("Āboli_%0%1").arg(i).arg(d),
                             10+d,
                             QString("Note_%0%1").arg(i).arg(d));
             table.addData(td);
            }
        }
      tables.append(table);
    }
    return tables;
}

void tprintToFile(QString fileName, QString txt){
    QFile fi(fileName);
    fi.open(QFile::WriteOnly|QFile::Truncate);

    QTextStream ds(&fi);
    ds.setCodec("UTF-8");
    ds << txt;
    fi.close();
}

QString treadTextFile(QString fileName){
    QFile fi(fileName);
    fi.open(QFile::ReadOnly);
    QTextStream ds(&fi);
    ds.setCodec("UTF-8");
    QString txt;
    txt = ds.readAll();
    fi.close();
    return txt;
}
void OldImpoExpoTest::testOldExport()
{
 QList<MTable> tables= mtables1(-1);
 ImpExp impo(&tables);

 QString result= impo.exportData();

 //qDebug()<< result;
 tprintToFile("ExpoOld.txt",result);
}

void OldImpoExpoTest::testOldImport()
{
    QList<MTable> tables= mtables1(-1);
    ImpExp expo(&tables);

    QString result= expo.exportData();


    tprintToFile("ExpoOld.txt",result);
    //----impo----//
    ImpExp impo;
    bool ok = impo.execImport(result);
     QList<MTable> tables1= impo.getImportedTables();
     for(int i=0; i< tables.size();i++){
         MTable table1= tables1.at(i);
         MTable table= tables.at(i);
        qDebug()<< table1.toString();
        QCOMPARE(table1.toString(),table.toString());
     }


}

void OldImpoExpoTest::testImportEmptyTables()
{
    QList<MTable> tables= mtables1(2); //2nd table empty data
    ImpExp expo(&tables);

    QString result= expo.exportData();


    tprintToFile("ExpoOld.txt",result);

    //----impo----//
    ImpExp impo;
    bool ok = impo.execImport(result);
     QList<MTable> tables1= impo.getImportedTables();
     for(int i=0; i< tables.size();i++){
         MTable table1= tables1.at(i);
         MTable table= tables.at(i);
        qDebug()<< table1.toString();
        QCOMPARE(table1.toString(),table.toString());
     }

}

void OldImpoExpoTest::testImportBadRecods()
{

    QString impoTxt= treadTextFile("://resources/ImportOldTestBadRecords.txt");

    qDebug()<<"Bad date column format!";
    ImpExp impo;
    bool ok = impo.execImport(impoTxt);
    QVERIFY(!ok);
    QString etxt= impo.errorTxt();
    QVERIFY(etxt.size()>0);
    qDebug()<<etxt;
    QList<MTable> tables= impo.getImportedTables();
    QVERIFY(tables.isEmpty());
    impoTxt= treadTextFile("://resources/ImportOldTestBadRecords_1.txt");

    qDebug()<<"Bad Amount column format!";
    ok = impo.execImport(impoTxt);
    QVERIFY(!ok);
    etxt= impo.errorTxt();
    QVERIFY(etxt.size()>0);
    qDebug()<<etxt;
    tables= impo.getImportedTables();
    QVERIFY(tables.isEmpty());
}

void OldImpoExpoTest::testRedudanteSpaceChars()
{
    QList<MTable> tables= mtables1(-1);

    QString impoTxt= treadTextFile("://resources/ImportOldTestBadRecords_2.txt");

    qDebug()<<"More spaces...";
    ImpExp impo;
    bool ok = impo.execImport(impoTxt);
    QVERIFY(ok);

    QList<MTable> tables1= impo.getImportedTables();
    QVERIFY(!tables1.isEmpty());
    for(int i=0; i< tables.size();i++){
        MTable table1= tables1.at(i);
        MTable table= tables.at(i);
       qDebug()<< table1.toString();
       QCOMPARE(table1.toString(),table.toString());
    }

}

void OldImpoExpoTest::testUTF8file()
{
    QList<MTable> tables= mtables2(-1);
    ImpExp impo(&tables);

    QString result= impo.exportData();

    //qDebug()<< result;
    tprintToFile("ExpoOldUTF8.txt",result);
}
