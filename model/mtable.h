#ifndef MTABLE_H
#define MTABLE_H

#include <QList>

#include "tabledata.h"
#include "tableinfo.h"
#include "expoimpo/csvexpoimpo.h"

#include <QDebug>

class MTable : public TableInfo,public ICSV
{
public:
    MTable();
    MTable(const TableInfo& tableInfo):
        TableInfo(tableInfo.getId(),tableInfo.getName(),tableInfo.getDate()){}

    virtual ~MTable(){/*qDebug()<<"MTable destr."; */}

    QList<TableData> getData() const {return data;}
     QList<TableData>& getDataForModify() {return data;}

    void setData(const QList<TableData> value) {data= value;}
    void addData(const TableData &value) {data.append(value);}
    void modifyData(int idx, const TableData &value);
    void deleteData(int idx);
    void sortByDate();
    QString toString();
    virtual QString getHeaderMarker();
    virtual QString formatHeader();
    virtual void parseHeader(QString headerString);
    virtual QString writeCSVString(QString delimiter);
    virtual void readCSVString(QString csvRows,QString delimiter);
    //bool operator ==(MTable other);


private:
    QList<TableData> data;
};


#endif // MTABLE_H
