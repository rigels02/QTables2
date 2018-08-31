#ifndef OLDIMPOEXPOTEST_H
#define OLDIMPOEXPOTEST_H

#include <QObject>
#include <QtTest>
#include <QDebug>

#include "expoimpo/old/impexp.h"

class OldImpoExpoTest : public QObject
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
    void testOldExport();
    void testOldImport();
    void testImportEmptyTables();
    void testImportBadRecods();
    void testRedudanteSpaceChars();
    void testUTF8file();
};

#endif // OLDIMPOEXPOTEST_H
