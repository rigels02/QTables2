#ifndef CSVEXPOIMPO_H
#define CSVEXPOIMPO_H

#include <QString>
#include <QList>
#include <QFile>

#include "iexportimport.h"

#include <QDebug>

class ICSV{

public:
    virtual QString formatHeader()=0;
    virtual QString getHeaderMarker()=0;
    virtual void parseHeader(QString headerString)=0;
    virtual void readCSVString(QString csvRows, QString delimiter)=0; /*throws Exception;*/
    virtual QString writeCSVString(QString delimiter)=0;
};



class T:public ICSV{

};

template <class T>
class T_CSV:public IExportImport<T>{

public:
        T_CSV():delimiter(","){}
        T_CSV(QString delimiter):delimiter(delimiter){}
        void myTesto();
        virtual void exportData(QString filePath, QList<T> tables);
        virtual QList<T> importData(QString filePath);

private:
 QString delimiter;
};

template<class T>
void T_CSV<T>::exportData(QString filePath, QList<T> tables){
    QString csv;

    foreach (T table, tables) {
        csv.append(table.formatHeader()).append("\n");
        csv.append(table.writeCSVString(delimiter));
    }
    //qDebug()<<csv;
    QFile fi(filePath);
    if(fi.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream tos(&fi);
        tos.setCodec("UTF-8");
        tos<<csv;
        fi.close();
    }
}
/**
 *throws QString
 */
template<class T>
QList<T> T_CSV<T>::importData(QString filePath){
    T table;
    QString csv;
    QFile fi(filePath);
    if(fi.open(QIODevice::ReadOnly)){
        QTextStream tis(&fi);
        tis.setCodec("UTF-8");
        csv = tis.readAll();
        fi.close();
    }
    QStringList lines = csv.split("\n");
    QList<int> indexes;
    QString marker= table.getHeaderMarker();
    //fill in indexes for comments with markers
    for (int i=0; i< lines.size();i++) {
        QString el= lines.at(i);
        if( el.startsWith(marker)){
            indexes.append(i);
        }
    }
    QList<T> tables;
    for(int i=0; i< indexes.size();i++){
        T table;
        int idx1= indexes.at(i);
        int idx2= (i< indexes.size() - 1)?indexes.at(i+1):-1;
        table.parseHeader(lines.at(idx1));
        QString csv;
        if(idx2 != -1){ //not last line
            for (int s = idx1 + 1; s < idx2; s++) {
                csv.append(lines[s]).append("\n");
            }
        }else{
            for (int s = idx1 + 1; s < lines.size(); s++) {
                csv.append(lines[s]).append("\n");
            }
        }
        try{
            table.readCSVString(csv,delimiter);
        }catch(QString ex){
            throw ex;
        }
        tables.append(table);
    }
    return tables;
}


#endif // CSVEXPOIMPO_H
