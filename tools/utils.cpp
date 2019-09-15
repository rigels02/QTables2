#include "utils.h"

/**
 * Column valid types: "text","float","choice","date"
 */
 static QStringList types= QStringList()<<"text"<<"float"<<"choice"<<"date";

 static QStringList columnTitles= QStringList();

 /**
 Detailed error message
*/
 static QString _DetErrMsg;

Utils::Utils()
{
}

/**
 * Get info about column with error.
 * If there is columnTitles defined then get column name,
 * otherwise just index.
 * @param colidx column index in form where error occures
 * @return string of message to be included for user
 */

QString Utils::getColumnInfo(int colidx){
    if(columnTitles.isEmpty()){

            return QString(": Column= %1").arg(colidx+1);
        }
        QString info=QString(" in column: %1").arg(columnTitles.at(colidx));
        columnTitles.clear();
        return info;
}

void Utils::setColumnTitles(QStringList colTitles){
    columnTitles=colTitles;

}

QString Utils::PackItem(QStringList fld, int maxChars, QWidget *wdg){
 //int len= fld.size();
 QString sep=" ";
QString pitem="";
if(wdg==nullptr){
pitem= fld.join(sep);
pitem = pitem.trimmed();
while(pitem.length()<maxChars){
     sep.append(" ");
     pitem=fld.join(sep);
     pitem = pitem.trimmed();
 }
 return pitem;
}
pitem=fld.join(sep);
pitem = pitem.trimmed();
int w= wdg->geometry().width()-40;
int sw=wdg->fontMetrics().width(pitem);

while(sw<w){
    sep.append(" ");
    pitem=fld.join(sep);
    pitem = pitem.trimmed();
    sw=wdg->fontMetrics().width(pitem);
}
return pitem;
}
QString Utils::PackItemJust(QStringList fld, int maxChars){
    QString sep=" ";
   QString pitem="";
   pitem= fld.join(sep);
   pitem = pitem.trimmed();
   int spacecnt=1;

   while(pitem.length()<maxChars){
       pitem="";
       spacecnt++;

       for(int i=0;i<fld.size();i++){
           if(i== fld.size()-1){ //last element
                          pitem.append(fld.at(i));
                         return pitem;
                         //pitem.trimmed();
            }
           else if(i==0){ //first element

           pitem.append(fld.at(i).leftJustified(fld.at(i).length()+2,' '));

           }else  {

           pitem.append(fld.at(i).leftJustified(fld.at(i).length()+spacecnt,' '));

           }

       }

    }

    return pitem;

}
/**
  Get elements list for column by index colIdx
  */
QStringList Utils::getColumnList(QVector<QStringList> *mtable, int colIdx){
    if(mtable==nullptr || mtable->size()==0) return QStringList();
    QVector<QString> vec(0);
    for(int i=0;i<mtable->size();i++){
    QString tmp=mtable->at(i).at(colIdx).trimmed();
    //tmp=tmp.toUpper();
    if(! tmp.isEmpty())
        if(! vec.contains(tmp))
            vec.append(tmp);
    }
    QList<QString> list= vec.toList();
    QStringList ql= list;
    return ql;
}

/**
 * Add spaces to the end of text to make it of given length
 * @param txt - text to be formated
 * @param length - string length to be reached
 * @return - formated string
 */

QString Utils::AddSpace(QString txt, int length){

        int maxln=length;
        if(txt.length()>= length) return txt;
        QString str=txt;
        while(str.length()<maxln){
            str=str+" ";
        }
        return str;


}

/**
 * Convert float to string and strip the last decimal digits until
 * 2 digits.
 * @param v - float value to be converted
 * @return - String result
 */
QString Utils::toStrWithStrip(double v){
    QString res="";
    res=QString("%1").arg(v,0,'f',2);

   return res;
}
QString Utils::toStrWithDec(double v,int dec){
    QString res="";
    res=QString("%1").arg(v,0,'f',dec);

   return res;
}

QString Utils::ErrorDetails(){
    return _DetErrMsg;

}

/**
 *
 * Check that passed  table columns row contains valid values.
 * @see constant types
 * @param ColsType - String array of columns valid types, see constant types
 * @param cols2chk - String array of columns to be checked
 * @return - true if ok, false if is not valid
 *
 */


bool Utils::isValidRow(QStringList ColsType, QStringList cols2chk){
    _DetErrMsg=QString();
    QDate td;
    //td.setYMD(2012,1,1);
    //QString sdate;

    bool ok;
       if(ColsType.isEmpty() || cols2chk.isEmpty()) return false;
       if(ColsType.length() != cols2chk.length()) return false;
        int sw=0;
        for(int i=0;i< cols2chk.length(); i++){
            for(int k=0;k<types.length();k++){
                //find in types
                if(ColsType.at(i).compare(types.at(k))==0)
                    sw=k;
            }
            switch(sw){
            case 0: //text

                break;
            case 1: //float
                cols2chk.at(i).toFloat(&ok);
                if( !ok ) {
                _DetErrMsg=QString("Float value missing%1").arg(getColumnInfo(i));
                    return false;
                }
                break;
            case 2: //choice
                if(cols2chk.at(i).trimmed().length()==0) {
                    _DetErrMsg=QString("Choice can not be blank%1").arg(getColumnInfo(i));
                    return false; //cannot be blank
                }
                break;
            case 3: //date

                //sdate=cols2chk.at(i);
                td= QDate::fromString(cols2chk.at(i),"dd/MM/yyyy");

                if(!td.isValid()) {
                    _DetErrMsg=QString("Date Format:\ndd/mm/yyyy%1").arg(getColumnInfo(i));
                    return false;
                }
                break;


            default:
                _DetErrMsg="Unknown Column type!";
                return false;
            }
        }
        return true;

}


