#include "mainwindow.h"
#include <QApplication>

#include <io/iofileimpl.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IOFileImpl repo;
    MainWindow w(0,&repo);
    w.show();

    return a.exec();

}
