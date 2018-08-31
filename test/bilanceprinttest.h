#ifndef BILANCEPRINTTEST_H
#define BILANCEPRINTTEST_H

#include <QObject>
#include <QtTest>
#include <QDebug>
#include "report/bilanceprint.h"
#include "tools/utils.h"

class BilancePrintTest : public QObject
{
    Q_OBJECT
public:

private slots:
    // functions executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    // functions executed by QtTest before and after each test
    void init();
    void cleanup();

    // test functions - all functions prefixed with "test" will be ran as tests
    void testHi();
    void testBilancePrint();

};

#endif // BILANCEPRINTTEST_H
