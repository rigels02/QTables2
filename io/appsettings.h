#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QFile>
#include <QDataStream>

class AppSettings
{
public:
    AppSettings(QString fileName);

    void saveTableIdx(int idx);
    int readTableIdx();

private:
    QString fileName;
};

#endif // APPSETTINGS_H
