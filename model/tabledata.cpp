#include "tabledata.h"

QString TableData::toString(){
    return QString("TableData{ Id= %1, cdate= %2 ,cat= %3, amount= %4, note= %5 }")
            .arg(Id).arg(cdate.toString("dd/MM/yyyy")).arg(cat).arg(amount).arg(note);

}

QString TableData::print() const
{
    return QString("cdate= %1 ,cat= %2, amount= %3, note= %4")
                .arg(cdate.toString("dd/MM/yyyy")).arg(cat).arg(amount).arg(note);

}

bool TableData::operator ==(TableData other)
{
    return this->getId()==other.getId()&&
            this->getCdate()==other.getCdate()&&
            this->getCat()==other.getCat()&&
            this->getAmount()==other.getAmount()&&
            this->getNote()==other.getNote();
}

void TableData::writeData(QDataStream &ds) const
{

    ds<<Id;

    ds<<this->cdate;
    ds<<this->cat;
    ds<<this->amount;
    ds<<this->note;
}

void TableData::readData(QDataStream &ds)
{
    ds>>this->Id;
    ds>>this->cdate;
    ds>>this->cat;
    ds>>this->amount;
    ds>>this->note;
}

//bool TableData::compareByDate(const TableData &data1, const TableData &data2)
//{
//    return data1.getCdate()<data2.getCdate();
//}
QString TableData::formated(){
    return QString("cdate= %1 ,cat= %2, amount= %3, note= %4")
            .arg(cdate.toString("dd/MM/yyyy")).arg(cat).arg(amount).arg(note);


}

