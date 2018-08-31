#ifndef IMPEXP_H
#define IMPEXP_H

#include <QString>
#include <QStringList>
#include <QVector>

#include <QDebug>

#include "../../model/mtable.h"

#include "../../tools/utils.h"
#include "../iexportimport.h"



class ImpExp : public IExportImport<MTable>
{
public:
    ImpExp(QList<MTable> *tables=0);
    ~ImpExp();
    QString errorTxt();

    QString exportData();

    bool OK;
     bool execImport(QString imptxt);
     QList<MTable> getImportedTables() const;

     void exportData(QString filePath,QList<MTable> tables) override; /*throws Exception;*/
     QList<MTable> importData(QString filePath) override; /* throws IOException, Exception;*/

private:

     /**
     * @brief m_inputTables
     * Tables for export
     */
    QList<MTable> *m_inputTables;
    /**
     * @brief m_tables
     * Imported tables;
     */
    QList<MTable> m_tables;
    /**
     * @brief mtable
     * Table data (TableData) for current table in export/import process
     */
    QVector<QStringList> mtable;
    //QStringList Titles;
    QString DumpTxt;
    QString ErrTxt;
    QString Delim;
    int helmidx;
    QVector<QStringList> htable;
    QString impTxt;
    int idx1,idxn,idx2;
    int tType;
    QStringList colnames,coltypes;
    void error(QString txt);
    bool getMTable(int tableIdx);
    void dumpHeader(QStringList *helm);
    void addMTable();

    int rowsnumber(QString rows);
    int colsnumber(QString row);
    int hcolsnumber(QString row);
    QStringList getHCols(QString row);
    bool getCols(QString row);
    bool getColType(QString row);
    bool getData();
    QString getBlock();
    bool getColumns();
    int getTableType();
    bool readHeader();
    bool isDuplicateTableName(QString title);

    void dumpData();
    bool makeOldExport();


    bool get2Import(bool store);

    QString substring(QString str,int startidx,int lastidx);
    void ttt();
    bool getTableData(QString tableStoreName);
    bool getTableDataByIdx(int idx);
    QStringList getDataRow(TableData row);
    QStringList makeHeader(int idx);
    void addTableRecord(QStringList sheader);
};

#endif // IMPEXP_H
