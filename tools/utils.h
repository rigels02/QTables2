#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <QString>
#include <QStringList>
#include <QDate>
#include <QWidget>



class Utils
{
public:



    Utils();
    static QString PackItem(QStringList fld,int maxChars,QWidget *wdg=0);
    static QString PackItemJust(QStringList fld,int maxChars);
    static QStringList getColumnList(QVector<QStringList> *mtable, int colIdx);
    static QString AddSpace(QString txt, int length);
    static QString toStrWithStrip(double v);
    static QString toStrWithDec(double v,int dec);
    static bool isValidRow(QStringList ColsType,QStringList cols2chk);
    static QString ErrorDetails();
    static QString getColumnInfo(int colidx);
    static void setColumnTitles(QStringList colTitles);



};

#endif // UTILS_H
