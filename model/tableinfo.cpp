#include "tableinfo.h"


QString TableInfo::toString()
{
  return QString("TableInfo{ Id= %1, name= %2 ,modTime= %3 }").arg(Id).arg(name).arg(date.toString("dd/MM/yyyy"));
}

QString TableInfo::fomated()
{
    return QString("Id= %1, name= %2, modTime= %3").arg(Id).arg(name).arg(date.toString("dd/MM/yyyy"));
}




bool TableInfo::operator ==(TableInfo other)
{
 return this->getId()==other.getId()&&
            this->getDate()==other.getDate()&&
            this->getName()==other.getName();
}

void TableInfo::writeData(QDataStream &ds) const
{
    ds<< this->Id;
     ds<< this->name;
    ds<< this->date;

}

void TableInfo::readData(QDataStream &ds){
    ds>> this->Id;
     ds>> this->name;
    ds>> this->date;

}



