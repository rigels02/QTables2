#include "qtables2test.h"



void QTables2Test::initTestCase()
{
    QFile fi(IOFileImpl::idxFile);
    if(fi.exists())
       fi.remove();
    for(int i=1; i<=20;i++){
        QString filename = QString("data%0.dat").arg(i);
        QFile fi(filename);
        if(fi.exists()){
            fi.remove();
        }
        fi.close();
    }
}

void QTables2Test::cleanupTestCase()
{

}

void QTables2Test::init()
{

}

void QTables2Test::cleanup()
{

}

void QTables2Test::testHi()
{
    qDebug()<<"Test try..";
}

void QTables2Test::testSortByDate()
{
    QList<TableData> data;

    data.append(TableData(QDate(2017,12,23),"Table_1Cat1",12.34,"Note_1"));
    data.append(TableData(QDate(2017,3,28),"Table_1Cat1",12.34,"Note_1"));
    data.append(TableData(QDate(2017,3,23),"Table_1Cat1",12.34,"Note_1"));

    //qSort(data.begin(),data.end(),TableData::compareByDate);
    std::sort(data.begin(),data.end(),TableData::compareByDate);
    foreach (TableData d, data) {
        qDebug()<< d.toString();
    }

    MTable mtable;

    mtable.setId(1);
    mtable.setName("Table_1");
    mtable.setDate(QDateTime().currentDateTime());

    mtable.addData(TableData(QDate(2017,12,23),"Table_1Cat1",12.34,"Note_1"));
    mtable.addData(TableData(QDate(2017,3,28),"Table_1Cat2",22.34,"Note_2"));
    mtable.addData(TableData(QDate(2017,3,23),"Table_1Cat3",32.34,"Note_3"));
    mtable.sortByDate();
    qDebug()<<mtable.toString();

}

QList<MTable> tables;
void QTables2Test::testExpoCSV()
{

    for(int i=1; i<=3;i++){
        MTable mtable;
        mtable.setId(1);
        mtable.setName(QString("Table_%1").arg(i));
        mtable.setDate(QDateTime().currentDateTime());

        mtable.addData(TableData(QDate(2017,2,23),QString("Table_%1%2").arg(i).arg("Cat1"),12.34,"Note_1"));
        mtable.addData(TableData(QDate(2017,3,23),QString("Table_%1%2").arg(i).arg("Cat2"),22.34,"Note_2"));
        mtable.addData(TableData(QDate(2017,4,23),QString("Table_%1%2").arg(i).arg("Cat3"),32.34,"Note_3"));
        tables.append(mtable);
    }
    T_CSV<MTable> csv;
    csv.exportData("testCSV.txt",tables);

}

void QTables2Test::testImpoCSV()
{

 QList<MTable> tables_1;
 T_CSV<MTable> csv;
 tables_1 = csv.importData("testCSV.txt");

 foreach (MTable table, tables_1) {
     qDebug()<< table.toString();
 }
 bool tableEq1= tables.at(0).getName()==tables_1.at(0).getName();
 bool tableEq2= tables.at(1).getName()==tables_1.at(1).getName();
 bool tableEq3= tables.at(2).getName()==tables_1.at(2).getName();
 QVERIFY(tableEq1);
 QVERIFY(tableEq2);
 QVERIFY(tableEq3);
 for(int i=0;i< 3;i++){
     for(int k=0; k< tables.at(i).getData().size();k++) {
         TableData dd= tables.at(i).getData().at(k);
         TableData dd1= tables_1.at(i).getData().at(k);
         QCOMPARE(dd.toString(),dd1.toString());
     }

 }

}
/**
 * @brief QTables2Test::makeTables
 * @param num skip data population for table with index = num (num= 1..3)
 * @return
 */
QList<MTable> QTables2Test::makeTables(int num)
{
    QList<MTable> tables;
    for(int i=1; i<=3;i++){
        MTable mtable;
        mtable.setId(1);
        mtable.setName(QString("Table_%1").arg(i));
        mtable.setDate(QDateTime().currentDateTime());

        if(i != num){
        mtable.addData(TableData(QDate(2017,2,23),QString("Table_%1%2").arg(i).arg("Cat1"),12.34,"Note_1"));
        mtable.addData(TableData(QDate(2017,3,23),QString("Table_%1%2").arg(i).arg("Cat2"),22.34,"Note_2"));
        mtable.addData(TableData(QDate(2017,4,23),QString("Table_%1%2").arg(i).arg("Cat3"),32.34,"Note_3"));
        }
        tables.append(mtable);
    }
    return tables;
}

QList<MTable> QTables2Test::makeTables_1(int num)
{
    QList<MTable> tables;
    for(int i=1; i<=3;i++){
        MTable mtable;
        mtable.setId(1);
        mtable.setName(QString("Table_%1").arg(i));
        mtable.setDate(QDateTime().currentDateTime());

        if(i != num){
        mtable.addData(TableData(QDate(2017,2,23),QString("Table_%1%2").arg(i).arg("Cat1"),12.34,""));
        mtable.addData(TableData(QDate(2017,3,23),QString("Table_%1%2").arg(i).arg("Cat2"),22.34,""));
        mtable.addData(TableData(QDate(2017,4,23),QString("Table_%1%2").arg(i).arg("Cat3"),32.34,""));
        }
        tables.append(mtable);
    }
    return tables;
}

QList<MTable> QTables2Test::makeTables_2(int num)
{

        QList<MTable> tables;
        for(int i=1; i<=3;i++){
            MTable mtable;
            mtable.setId(1);
            mtable.setName(QString("Table_%1").arg(i));
            mtable.setDate(QDateTime().currentDateTime());

            if(i != num){
            mtable.addData(TableData(QDate(2017,2,23),QString("Table_%1%2").arg(i).arg("Cat1"),12.34,"Note_1,Delim"));
            mtable.addData(TableData(QDate(2017,3,23),QString("Table_%1%2").arg(i).arg("Cat2"),22.34,"Note_2,Delim"));
            mtable.addData(TableData(QDate(2017,4,23),QString("Table_%1%2").arg(i).arg("Cat3"),32.34,"Note_3,Delim"));
            }
            tables.append(mtable);
        }
        return tables;

}

void QTables2Test::testImpoCSV_1()
{
    QList<MTable> tables = makeTables(1);
    T_CSV<MTable> csv;
    csv.exportData("testCSV.txt",tables);
    QList<MTable> tables_1;
    T_CSV<MTable> impo;
    tables_1 = impo.importData("testCSV.txt");

//    foreach (MTable table, tables_1) {
//        qDebug()<< table.toString();
//    }
    bool tableEq1= tables.at(0).getName()==tables_1.at(0).getName();
    bool tableEq2= tables.at(1).getName()==tables_1.at(1).getName();
    bool tableEq3= tables.at(2).getName()==tables_1.at(2).getName();
    QVERIFY(tableEq1);
    QVERIFY(tableEq2);
    QVERIFY(tableEq3);
    for(int i=0;i< 3;i++){
        for(int k=0; k< tables.at(i).getData().size();k++) {
            TableData dd= tables.at(i).getData().at(k);
            TableData dd1= tables_1.at(i).getData().at(k);
            QCOMPARE(dd.toString(),dd1.toString());
        }

    }
}

void QTables2Test::testImpoCSV_2()
{
    QList<MTable> tables = makeTables(2);
    T_CSV<MTable> csv;
    csv.exportData("testCSV.txt",tables);
    QList<MTable> tables_1;
    T_CSV<MTable> impo;
    tables_1 = impo.importData("testCSV.txt");

    bool tableEq1= tables.at(0).getName()==tables_1.at(0).getName();
    bool tableEq2= tables.at(1).getName()==tables_1.at(1).getName();
    bool tableEq3= tables.at(2).getName()==tables_1.at(2).getName();
    QVERIFY(tableEq1);
    QVERIFY(tableEq2);
    QVERIFY(tableEq3);
    for(int i=0;i< 3;i++){
        for(int k=0; k< tables.at(i).getData().size();k++) {
            TableData dd= tables.at(i).getData().at(k);
            TableData dd1= tables_1.at(i).getData().at(k);
            QCOMPARE(dd.toString(),dd1.toString());
        }

    }
}

void QTables2Test::testImpoCSV_3()
{
    QList<MTable> tables = makeTables(3);
    T_CSV<MTable> csv;
    csv.exportData("testCSV.txt",tables);
    QList<MTable> tables_1;
    T_CSV<MTable> impo;
    tables_1 = impo.importData("testCSV.txt");

    bool tableEq1= tables.at(0).getName()==tables_1.at(0).getName();
    bool tableEq2= tables.at(1).getName()==tables_1.at(1).getName();
    bool tableEq3= tables.at(2).getName()==tables_1.at(2).getName();
    QVERIFY(tableEq1);
    QVERIFY(tableEq2);
    QVERIFY(tableEq3);
    for(int i=0;i< 3;i++){
        for(int k=0; k< tables.at(i).getData().size();k++) {
            TableData dd= tables.at(i).getData().at(k);
            TableData dd1= tables_1.at(i).getData().at(k);
            QCOMPARE(dd.toString(),dd1.toString());
        }

    }
}

void QTables2Test::testImpoCSV_4()
{
    QList<MTable> tables = makeTables_1(-1);
    T_CSV<MTable> csv;
    csv.exportData("testCSV.txt",tables);
    QList<MTable> tables_1;
    T_CSV<MTable> impo;
    tables_1 = impo.importData("testCSV.txt");

    bool tableEq1= tables.at(0).getName()==tables_1.at(0).getName();
    bool tableEq2= tables.at(1).getName()==tables_1.at(1).getName();
    bool tableEq3= tables.at(2).getName()==tables_1.at(2).getName();
    QVERIFY(tableEq1);
    QVERIFY(tableEq2);
    QVERIFY(tableEq3);
    for(int i=0;i< 3;i++){
        for(int k=0; k< tables.at(i).getData().size();k++) {
            TableData dd= tables.at(i).getData().at(k);
            TableData dd1= tables_1.at(i).getData().at(k);
            QCOMPARE(dd.toString(),dd1.toString());
        }

    }
}

void QTables2Test::testExpoImpoSpecDelimiter()
{
    QList<MTable> tables = makeTables_1(-1);
    T_CSV<MTable> csv("|");
    csv.exportData("testCSV.txt",tables);
    QList<MTable> tables_1;
    T_CSV<MTable> impo("|");
    tables_1 = impo.importData("testCSV.txt");

    bool tableEq1= tables.at(0).getName()==tables_1.at(0).getName();
    bool tableEq2= tables.at(1).getName()==tables_1.at(1).getName();
    bool tableEq3= tables.at(2).getName()==tables_1.at(2).getName();
    QVERIFY(tableEq1);
    QVERIFY(tableEq2);
    QVERIFY(tableEq3);
    for(int i=0;i< 3;i++){
        for(int k=0; k< tables.at(i).getData().size();k++) {
            TableData dd= tables.at(i).getData().at(k);
            TableData dd1= tables_1.at(i).getData().at(k);
            QCOMPARE(dd.toString(),dd1.toString());
        }

    }
}

void QTables2Test::testExpoDelimiterReplacemant()
{

    QList<MTable> tables = makeTables_2(-1);
    T_CSV<MTable> csv(",");
    csv.exportData("testCSV.txt",tables);
    QList<MTable> tables_1;
    T_CSV<MTable> impo(",");
    tables_1 = impo.importData("testCSV.txt");

    bool tableEq1= tables.at(0).getName()==tables_1.at(0).getName();
    bool tableEq2= tables.at(1).getName()==tables_1.at(1).getName();
    bool tableEq3= tables.at(2).getName()==tables_1.at(2).getName();
    QVERIFY(tableEq1);
    QVERIFY(tableEq2);
    QVERIFY(tableEq3);
    for(int i=0;i< 3;i++){
        for(int k=0; k< tables.at(i).getData().size();k++) {
            //TableData dd= tables.at(i).getData().at(k);
            TableData dd1= tables_1.at(i).getData().at(k);
            bool notComma = !dd1.getNote().contains(",");
            QVERIFY(notComma);
        }

    }
}

void QTables2Test::testCreateIOFile()
{

    IOFileImpl io;

    QList<TableInfo> ti = io.getTablesInfo();
    QVERIFY(ti.size()==0);

}

void QTables2Test::testCreateSomeTables(){
  IOFileImpl io;
    io.createTable("Tables_1");
    QVERIFY(io.getTablesInfo().size()==1);
    QVERIFY(io.getTablesInfo().at(0).getId()==1);
    io.createTable("Tables_2");
    QVERIFY(io.getTablesInfo().size()==2);
    QVERIFY(io.getTablesInfo().at(1).getId()==2);
    io.createTable("Tables_3");
    QVERIFY(io.getTablesInfo().size()==3);
    QVERIFY(io.getTablesInfo().at(2).getId()==3);

}


void QTables2Test::testCreateTableSaveDataAndReadData()
{
    QFile fi(IOFileImpl::idxFile);
    if(fi.exists())
       fi.remove();

    IOFileImpl io;
    TableInfo ti0= io.createTable("Tables_1");
    QList<TableData> data;
    for(int i=1; i<=3; i++){
        TableData dd(QDate().currentDate(),QString("Cat_%0").arg(i),10+i,QString("Note_%0").arg(i));
        data.append(dd);
    }
    try{
     io.saveData(ti0.getId(),data);
    }catch(const char* msg){
     qDebug()<<msg;
     QFAIL(msg);
    }
     //new instance
     IOFileImpl io1;
     TableInfo ti= io1.getTablesInfo().at(0);
     QList<TableData> data1 = io1.loadData(ti.getId());
     foreach (TableData dd, data1) {
         qDebug()<<dd.toString();

     }
     for(int i=0; i< data.size();i++){
         QCOMPARE(data[i].toString(),data1[i].toString());
     }

}

void QTables2Test::testSaveReadDataWrongIndex()
{
    QFile fi(IOFileImpl::idxFile);
    if(fi.exists())
       fi.remove();

    IOFileImpl io;
    QList<TableData> data;
    bool except= false;
    try{
     io.saveData(99,data);
    }catch(const char* msg){
     qDebug()<<msg;
     except=true;
    }
    QVERIFY(except);
    except=false;
     //new instance
     IOFileImpl io1;

     QList<TableData> data1;
     try {
     data1= io1.loadData(99);
    }catch(const char* msg){
         qDebug()<<msg;
      except=true;
     }
    QVERIFY(except);
}

void QTables2Test::test3TablesWithDataAndRead()
{
    initTestCase();

    IOFileImpl io;
     TableInfo ti1= io.createTable("Tables_1");
    QList<TableData> data1;
    for(int i=1; i<=3; i++){
        TableData dd(QDate().currentDate(),QString("Cat_1%0").arg(i),10+i,QString("Note_1%0").arg(i));
        data1.append(dd);
    }
    try{
     io.saveData(ti1.getId(),data1);
    }catch(const char* msg){
     QFAIL(msg);
    }
     TableInfo ti2=io.createTable("Tables_2");
  QList<TableData> data2;
  for(int i=1; i<=3; i++){
      TableData dd(QDate().currentDate(),QString("Cat_2%0").arg(i),10+i,QString("Note_2%0").arg(i));
      data2.append(dd);
  }
  try{
   io.saveData(ti2.getId(),data2);
  }catch(const char* msg){
   QFAIL(msg);
  }
   TableInfo ti3=io.createTable("Tables_3");
QList<TableData> data3;
for(int i=1; i<=3; i++){
    TableData dd(QDate().currentDate(),QString("Cat_3%0").arg(i),10+i,QString("Note_3%0").arg(i));
    data3.append(dd);
}
try{
 io.saveData(ti3.getId(),data3);
}catch(const char* msg){
 QFAIL(msg);
}
//---------------Read-------//

QList<TableData>data11= io.loadData(ti1.getId());
for(int i=0; i<data11.size();i++){
    QCOMPARE(data11[i].toString(),data1[i].toString());
}

data11= io.loadData(ti2.getId());
for(int i=0; i<data11.size();i++){
    QCOMPARE(data11[i].toString(),data2[i].toString());
}

data11= io.loadData(ti3.getId());
for(int i=0; i<data11.size();i++){
    QCOMPARE(data11[i].toString(),data3[i].toString());
}

}

void QTables2Test::testSaveAndReadEmptyTable()
{
    initTestCase();

    IOFileImpl io;
     TableInfo ti= io.createTable("Tables_1");
    QList<TableData> data;

    try {
     io.saveData(ti.getId(),data);
    }catch(const char* mag){
        QFAIL(mag);
    }
    IOFileImpl io1;
    QList<TableData> data1;

    try {
     data1= io.loadData(ti.getId());
    }catch(const char* mag){
        QFAIL(mag);
    }
    QVERIFY(data1.size()==0);

}

QString mTabletoString(MTable table)
{
    TableInfo ti = table;
    QString sti= QString("%0%1").arg(ti.getName()).arg(ti.getDate().toString());
    QString sdata;
    foreach (TableData el, table.getData()) {
        sdata.append( el.toString());
    }
    return QString("MTable{ %1 ,data= %2}").arg(sti).arg(sdata);
}


void QTables2Test::testSaveAllAndReadAll()
{
    QList<MTable> tables;
    for(int i=1; i<=3; i++){
        MTable table;
        table.setName(QString("Table_%0").arg(i));
        table.setDate(QDateTime().currentDateTime());
        for(int d=1; d<= 3; d++){
            TableData data(QDate().currentDate(),
                           QString("Cat%0%1").arg(i).arg(d),
                           10+i,
                           QString("Note%0%1").arg(i).arg(d));
         table.addData(data);
        }
        tables.append(table);
    }

  IOFileImpl io;
  io.saveAll(tables);
    //---------Read all --/
  IOFileImpl io1;
  QList<MTable> tables1= io.loadAll();

  for(int i=0; i< tables.size(); i++) {
      MTable table = tables.at(i);
      MTable table1 = tables1.at(i);
      QCOMPARE(mTabletoString(table), mTabletoString(table1));
  }
}

void QTables2Test::testRenameTable()
{
    initTestCase();

    IOFileImpl io;
     TableInfo ti= io.createTable("Tables_1");
     io.renameTable(ti.getId(),"TableChanged");
     IOFileImpl io1;
     QList<TableInfo> tins = io1.getTablesInfo();
     QCOMPARE(tins.at(0).getName(),QString("TableChanged"));

}

void QTables2Test::testDeleteTable()
{
    initTestCase();

    IOFileImpl io;
     TableInfo ti= io.createTable("Tables_1");
     QList<TableData> datas;
     TableData data(QDate().currentDate(),"Catxx",11,"Note_xx");
     datas.append(data);
     io.saveData(ti.getId(),datas);
     QList<TableInfo> tins = io.getTablesInfo();
     QVERIFY(tins.size()==1);
    IOFileImpl io1;
     tins = io1.getTablesInfo();
      QVERIFY(tins.size()==1);
     io1.deleteTable(tins.at(0).getId());
     IOFileImpl io2;
      tins = io2.getTablesInfo();
       QVERIFY(tins.size()==0);

}

void QTables2Test::testDeleteAll()
{
    initTestCase();

    QList<MTable> tables;
    for(int i=1; i<=3; i++){
        MTable table;
        table.setName(QString("Table_%0").arg(i));
        table.setDate(QDateTime().currentDateTime());
        for(int d=1; d<= 3; d++){
            TableData data(QDate().currentDate(),
                           QString("Cat%0%1").arg(i).arg(d),
                           10+i,
                           QString("Note%0%1").arg(i).arg(d));
         table.addData(data);
        }
        tables.append(table);
    }

  IOFileImpl io;
  io.saveAll(tables);
  //----delete All ---//
    bool ok= io.deleteAll();
    QVERIFY(ok);
    IOFileImpl io1;
    QList<TableInfo> tinfo= io1.getTablesInfo();
    QVERIFY(tinfo.size()==0);
}

void QTables2Test::testCreateTableWithDataThenUpdateLessData()
{
    initTestCase();

    QList<MTable> tables;
    for(int i=1; i<=1; i++){
        MTable table;
        table.setName(QString("Table_%0").arg(i));
        table.setDate(QDateTime().currentDateTime());
        for(int d=1; d<= 3; d++){
            TableData data(QDate().currentDate(),
                           QString("Cat%0%1").arg(i).arg(d),
                           10+i,
                           QString("Note%0%1").arg(i).arg(d));
         table.addData(data);
        }
        tables.append(table);
    }

  IOFileImpl io;
  io.saveAll(tables);
  QList<TableData> data1;
  TableData dd(QDate().currentDate(),"CatXX",100,"Note_XX");
data1.append(dd);
  QList<TableInfo> infos = io.getTablesInfo();
  io.saveData(infos.at(0).getId(),data1);
  infos= io.getTablesInfo();
  QList<TableData> data2= io.loadData(infos.at(0).getId());
  QVERIFY(data2.size()==1);
  //Look at data1.dat file by hex editor
  //there must be only one TableData record
  //file must be truncated when it is rewritten.
  IOFileImpl io1;
  infos= io1.getTablesInfo();
  QList<TableData> data3= io1.loadData(infos.at(0).getId());
   QVERIFY(data3.size()==1);
   QCOMPARE(data1[0].toString(),data3[0].toString());
}





