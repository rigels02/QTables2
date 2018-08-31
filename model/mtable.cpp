#include "mtable.h"



MTable::MTable():TableInfo()
{
  // qDebug()<<"MTable constr.";


}



void MTable::modifyData(int idx, const TableData &value)
{
    deleteData(idx);
    data.insert(idx,value);

}
/**
 * throws exception
 * @brief MTable::deleteData
 * @param idx
 */
void MTable::deleteData(int idx)
{
    if(idx<0 || idx>data.size()-1) throw "Idx out of range!";
    data.removeAt(idx);
}

void MTable::sortByDate()
{
   // qSort(data.begin(),data.end(),TableData::compareByDate);
    std::sort(data.begin(),data.end(),TableData::compareByDate);
}

QString MTable::toString()
{
    QString sdata;
    foreach (TableData el, data) {
        sdata.append( el.toString());
    }
    return QString("MTable{ %1 ,data= %2}").arg(TableInfo::toString()).arg(sdata);
}



QString MTable::getHeaderMarker(){
    return "#MTable";
}
QString MTable::formatHeader(){
    return "#MTable "+getName();
}
void MTable::parseHeader(QString headerString){
  QString name= headerString.mid(getHeaderMarker().length()).trimmed();
  this->setName(name);
  this->setId(0);
  //set DateTime to Null - QDateTime()
  this->setDate(QDateTime());
  //this->setDate(QDateTime().currentDateTime());

}
QString MTable::writeCSVString(QString delimiter){
    QString csv;
    foreach (TableData d, data) {

        csv.append(d.getCdate().toString("dd/MM/yyyy")).append(delimiter)
                .append(d.getCat()).append(delimiter).append(QString("%1").arg(d.getAmount()))
                .append(delimiter).append(d.getNote().replace(delimiter," ")).append("\n");
    }
    return csv;
}
void MTable::readCSVString(QString csvRows,QString delimiter){
 QStringList rows = csvRows.split("\n");
 foreach (QString row, rows) {
     if(row.isEmpty()) return;
     QStringList fields = row.split(delimiter);
     bool ok=true;
     TableData tdata;
     tdata.setId(0);
     tdata.setCdate(QDate().fromString(fields[0],"dd/MM/yyyy"));
     tdata.setCat(fields[1]);
     tdata.setAmount(fields[2].toDouble(&ok));
     if(!ok)
         throw QString("Double parse error! row: %1").arg(row);
     tdata.setNote(fields[3]);
    data.append(tdata);
 }

}
/**
bool MTable::operator ==(MTable other)
{
   bool p1= this->getId()==other.getId() &&
    this->getName()==other.getName() &&
    this->getDate()==other.getDate() &&
    this->getSelected()==other.getSelected() &&
    this->getData().size()==other.getData().size();
   if(!p1) return false;
   for (int i=0;i< this->getData().size();i++) {
       if(! (((TableData)this->getData().at(i))==((TableData)other.getData().at(i))) ) return false;
   }
   return true;
}
**/



