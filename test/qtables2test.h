#ifndef MYEASYNOTESTEST_H
#define MYEASYNOTESTEST_H

#include <QObject>
#include <QtTest>
#include <QDebug>

#include "expoimpo/csvexpoimpo.h"
#include "model/tableinfo.h"
#include "model/mtable.h"
#include "model/tabledata.h"
#include "io/iofileimpl.h"

class QTables2Test : public QObject
{
    Q_OBJECT
private slots:
    // functions executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    // functions executed by QtTest before and after each test
    void init();
    void cleanup();

    // test functions - all functions prefixed with "test" will be ran as tests
    void testHi();
    void testSortByDate();
        void testExpoCSV();
        void testImpoCSV();
        QList<MTable> makeTables(int num);
        QList<MTable> makeTables_1(int num);
        QList<MTable> makeTables_2(int num);
        void testImpoCSV_1();
        void testImpoCSV_2();
        void testImpoCSV_3();
        void testImpoCSV_4();
        void testExpoImpoSpecDelimiter();
        void testExpoDelimiterReplacemant();
        void testCreateIOFile();

        void testCreateSomeTables();

        void testCreateTableSaveDataAndReadData();
        void testSaveReadDataWrongIndex();
        void test3TablesWithDataAndRead();
        void testSaveAndReadEmptyTable();
        void testSaveAllAndReadAll();
        void testRenameTable();
        void testDeleteTable();
        void testDeleteAll();
        void testCreateTableWithDataThenUpdateLessData();

};

#endif // MYEASYNOTESTEST_H
