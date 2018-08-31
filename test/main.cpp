#include <QtTest>
#include "test/qtables2test.h"
#include "test/bilanceprinttest.h"
#include "test/oldimpoexpotest.h"
#include "test/impoexpojsontest.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

  //QTables2Test myTest;
  //BilancePrintTest bilTest;
  //  OldImpoExpoTest oimpo;
    ImpoExpoJsonTest ieJsonTest;
    // multiple test suites can be ran like this
  //return QTest::qExec(&myTest, argc, argv);
  //return QTest::qExec(&bilTest, argc, argv);
   // return QTest::qExec(&oimpo, argc, argv);
     return QTest::qExec(&ieJsonTest, argc, argv);

}
