#ifndef IMPOEXPOJSON_H
#define IMPOEXPOJSON_H

#include <QString>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "model/mtable.h"
#include "expoimpo/iexportimport.h"

#include <QDebug>

class ImpoExpoJson:public IExportImport<MTable>
{
public:
    ImpoExpoJson();
    void expoJson(const QString filePath, const QList<MTable> tables);
    QList<MTable> impoJson(const QString filePath);
    void exportData(QString filePath, QList<MTable> tables) override;
    QList<MTable> importData(QString filePath) override;

private:

    QJsonDocument toJsonArrayDoc(const QList<MTable> tables);
    QList<MTable>   fromJsonArrayDoc(const QJsonDocument doc);
    static QDate makeQDateFromEpoch(qint64 msec);
    static qint64 makeMSecSinceEpoch(QDate date);
    static QDateTime makeQDateTimeFromEpoch(qint64 msec);
    static qint64 makeMSecSinceEpochDT(QDateTime date);
};

#endif // IMPOEXPOJSON_H
