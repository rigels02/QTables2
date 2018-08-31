#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <QString>
#include <QDate>


#include "idatastream.h"

class TableData:public IDataStream
{
public:
    TableData(){}
    TableData(QDate cdate, QString cat, double amount, QString note):
               Id(0),cdate(cdate),cat(cat),amount(amount),note(note){}
    virtual ~TableData() {}
    //getters/setters


    qint64 getId() const {return Id;}
    void setId(const qint64 &value) {Id= value;}

    QDate getCdate() const {return cdate;}
    void setCdate(const QDate &value) {cdate=value;}

    QString getCat() const {return cat;}
    void setCat(const QString &value) {cat = value;}

    double getAmount() const {return amount;}
    void setAmount(double value) {amount= value;}

    QString getNote() const {return note;}
    void setNote(const QString &value) {note=value;}
    //
    QString formated();
    QString toString();


    bool operator ==(TableData other);

    static bool compareByDate( const TableData &d1,const TableData &d2){
        return d1.getCdate()<d2.getCdate();
    }
    void writeData(QDataStream &ds) const override;
    void readData(QDataStream &ds) override;

    QString print() const;
private:
    qint64 Id;
    QDate  cdate;
    QString cat;
    double amount;
    QString note;
private:
    bool validate(QString &info) const;
};



#endif // TABLEDATA_H
