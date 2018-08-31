#ifndef TABLEINFO_H
#define TABLEINFO_H

#include <QString>
#include <QDateTime>
#include <QDataStream>

#include "idatastream.h"

#include <QDebug>

class TableInfo:public IDataStream
{
public:
    TableInfo():name(""),date(QDateTime()){/*qDebug()<<"TableInfo constr.";*/}
    TableInfo(QString name, QDateTime modTime):name(name),date(modTime){}
    TableInfo(qint64 Id, QString name, QDateTime modTime):Id(Id),name(name),date(modTime){}


    virtual ~TableInfo(){/*qDebug()<<"TableInfo destr.";*/}

    //getters, setters
    qint64 getId() const {return Id;}
    void setId(const qint64 &value){ Id=value;}

    QString getName() const {return name;}
    void setName(const QString &value) {name=value;}

    QDateTime getDate() const {return date;}
    void setDate(const QDateTime &value){date= value;}

    //
    QString toString();
    QString fomated();


    bool operator ==(TableInfo other);

    void writeData(QDataStream &ds) const override;
    void readData(QDataStream &ds) override;

private:
    qint64 Id;
    QString name;
    QDateTime   date;

};


#endif // TABLEINFO_H
