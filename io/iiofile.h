#ifndef IIOFILE_H
#define IIOFILE_H

#include "model/mtable.h"

class IIOFile
{

public:

   //IIOFile(){}
   //virtual ~IIOFile()=0;

    virtual void saveAll(QList<MTable> data)=0;
    virtual QList<MTable> loadAll()=0;

    virtual        TableInfo createTable(QString name)=0;
    virtual  const TableInfo *renameTable(int id,QString name)=0;
    virtual  bool deleteTable(int id)=0;
    virtual  bool deleteAll()=0;

    virtual void saveData(int tid,QList<TableData> data)=0;
    virtual QList<TableData> loadData(int tid) =0;

    virtual QList<TableInfo> getTablesInfo() const=0;

};
#endif // IIOFILE_H
