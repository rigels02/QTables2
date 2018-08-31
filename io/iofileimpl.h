#ifndef IOFILEIMPL_H
#define IOFILEIMPL_H

#include <QDataStream>
#include <QString>
#include <QList>
#include <QDate>
#include <QMessageBox>
#include <QException>

#include "io/iiofile.h"
#include "model/mtable.h"

#include <QDebug>


class IOFileImpl:public IIOFile
{
public:
     static const QString idxFile;
private:
     static const QString dataFile;
     static const QString dataExt;
     static const QString magicSign;

public:

    IOFileImpl();
    //~IOFileImpl(){}

    void saveAll(QList<MTable> data) override;
    QList<MTable> loadAll() override;

           TableInfo createTable(QString name) override;
     const TableInfo *renameTable(int id,QString name) override;
      bool deleteTable(int id) override;
     bool deleteAll() override;

    void saveData(int tid,QList<TableData> data) override;
         QList<TableData> loadData(int tid) override;

         QList<TableInfo> getTablesInfo() const override;

protected:
    void createIdxFile(QFile &fi);
    void readIdxFile();
    void writeIdxFile();
    int getNewIndex();
    TableInfo *getInfo(int tid);

    int getTableInfoIndex(int tid);
private:

    void createDataFile(QFile &fi);
    void openDataFileForRead(QFile &fi);
    void openDataFileForWrite(QFile &fi);
    void writeHeader(QDataStream &ds);
    void readHeader(QDataStream &ds);

    QString composeFileName(int tid);

    QList<TableInfo> tablesInfo;

    void _saveData(int tid, QList<TableData> data);
    bool deleteDataFile(QString fn);
};

#endif // IOFILEIMPL_H
