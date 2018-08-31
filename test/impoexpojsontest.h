#ifndef IMPOEXPOJSONTEST_H
#define IMPOEXPOJSONTEST_H

#include <QObject>
#include <QtTest>

#include <QDebug>

#include "expoimpo/impoexpojson.h"

class ImpoExpoJsonTest : public QObject
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
    void testJsonExpo();
    void testJsonImpo();
    void testJsonExpoImpoEmptyData();
    void testJsonExpoImpoEmptyData1();
    void testJsonExpoImpoData();

};

#endif // IMPOEXPOJSONTEST_H
