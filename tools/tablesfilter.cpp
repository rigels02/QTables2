#include "tablesfilter.h"

QList<TableInfo> TablesFilter::doFilter(const QList<TableInfo> &list, const QString words){

  if(list.isEmpty() || words.isEmpty()) return list;
  QStringList sw = prepareWords(words);
   return TablesFilter::doFilter(list,sw);

}
QList<TableInfo> TablesFilter::doFilter(const QList<TableInfo> &list, const QStringList words){
    if(list.isEmpty() || words.isEmpty()) return list;
    QList<TableInfo> filtered;
    foreach (TableInfo tableInfo, list) {
        foreach (QString w, words) {
            if( tableInfo.getName().contains(w,Qt::CaseInsensitive) ){
                filtered<<tableInfo;
            }
        }
    }
    return filtered;
}
QStringList TablesFilter::prepareWords(QString words){
   QString words1= words.replace(QRegExp("[.,?]")," ");
   QStringList sw= words1.split(" ");
   QStringList sw1;
   foreach (QString w, sw) {
       if(!w.isEmpty()){
           sw1<<w;
       }
   }
   return sw1;
}
int TablesFilter::wordPos(const QString inputString, QString words){
    int pos= -1;
    if(inputString.isEmpty() || words.isEmpty()) return -1;
    QStringList sl= TablesFilter::prepareWords(words);
    //select pos for first word

    foreach (QString w, sl) {
        if(inputString.contains(w,Qt::CaseInsensitive)){
           pos= inputString.indexOf(w,0,Qt::CaseInsensitive);

           return pos;
        }
    }
    return pos;
}
