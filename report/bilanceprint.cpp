#include "bilanceprint.h"

#define SP "&nbsp;"
#define HR "<hr>"
#define NL "<br>"

BilancePrint::BilancePrint(QString tableName, QList<TableData> *data, bool sethtml)
{


        if(data==0) return;

        mtable= convertToQVector(data);


        isForBilancePrint =true;
        TotalRemainSum=0;
        htmlprint=sethtml;
        this->tableName=tableName;
        categoryLst = new QStringList();
        monthsLst= new QStringList();
        //--------------------//
        getCategories();
        //getMonths();
        getMonthYears();

}
QVector<QStringList> BilancePrint::convertToQVector(QList<TableData> *data){
    QVector<QStringList> vector;
    for(int i=0; i<data->size(); i++){
        QStringList row;
        row<<data->at(i).getCdate().toString("dd/MM/yyyy");
        row<<data->at(i).getCat();
        row<<QString("%0").arg(data->at(i).getAmount());
        row<<data->at(i).getNote();
        vector.append(row);
    }
    return vector;
}


BilancePrint::~BilancePrint(){
    delete categoryLst;
    delete monthsLst;
}


QString BilancePrint::hr(){
    return ((htmlprint)? "<hr>":"--------------------");
}
QString BilancePrint::nl(){
return ((htmlprint)? "<br>":"\n");
    //return "\n";
}
/**
Is txt int the Lst?
*/
bool BilancePrint::isInList(QStringList Lst, QString txt){
    QString lstTxt;
    for(int i=0;i<Lst.size();i++){
            lstTxt = Lst.at(i);
            if(lstTxt.compare(txt)==0)
                 return true;

            }
            return false;

}
void BilancePrint::getCategories(){
    int sz= mtable.size();
            QString cat;
            for(int i=0;i<sz;i++){
                cat= mtable.at(i).at(1);//get Category

                if(! isInList(*categoryLst, cat))
                       categoryLst->append(cat);
            }

}
void BilancePrint::getMonths(){
    //date is in format dd/mm/yyyy
            int sz= mtable.size();
            QString date;
            for(int i=0;i<sz;i++){
                date= mtable.at(i).at(0); //get Date
                QString mm=date.section("/",1,1);
                //String mm =date.substring(3, 5);
                if(! isInList(*monthsLst, mm))
                       monthsLst->append(mm);
            }
}

void BilancePrint::getMonthYears()
{
    //date is in format dd/mm/yyyy
            int sz= mtable.size();
            QString date;
            for(int i=0;i<sz;i++){
                date= mtable.at(i).at(0); //get Date
                QString mm=date.section("/",1,2);
                //String mm =date.substring(3, 5);
                if(! isInList(*monthsLst, mm))
                       monthsLst->append(mm);
            }
}

double BilancePrint::getTotalByCategory(QString Cat){
    double Sum=0.0;
    QStringList elm;
    bool ok;
            if(!isInList(*categoryLst, Cat))
                 return 0.0;
            //Sum
            for(int i=0;i<mtable.size();i++){
                elm= mtable.at(i);
                if(elm.at(1).compare(Cat)==0)
                      Sum+=elm.at(2).toDouble(&ok); //get amount
            }
            return Sum;

}
QString BilancePrint::printTotalForCategories(){
    double Sum=0.0;
            double TotalSum=0.0;
            double TotalMin=0.0;
            QString Cat;
            QString txt="";
            if(categoryLst->size()==0) return "";
            if(htmlprint)
                txt+="<font color='blue'>Balance by categories:</font><br>";
            else
                txt+="Balance by categories:"+nl();
            for(int i=0;i<categoryLst->size();i++){
                Cat=categoryLst->at(i);
                Sum = getTotalByCategory(Cat);
            if(Sum>0){
                txt+=Utils::AddSpace(Utils::AddSpace(Cat, 10)+" " +Utils::toStrWithStrip(Sum),17)+" :"+nl();
            }else{
                TotalMin+=Sum;
                txt+=Utils::AddSpace(Cat, 17)+" : "+Utils::toStrWithStrip(Sum)+nl();
            }
             TotalSum+=Sum;
             //Sum=0;
            }
            //String sTotalSum= Float.toString(TotalSum);
            //String sTotalMin;
            QString sTotalSum= Utils::toStrWithStrip(TotalSum);
            QString sTotalMin= Utils::toStrWithStrip(TotalMin);
            txt+=hr()+nl()+sTotalSum+"  :  "+sTotalMin+nl();
            return txt;
}

QString BilancePrint::printTotalForCategoriesTbl()
{
    double Sum=0.0;
            double TotalSum=0.0;
            double TotalMin=0.0;
            QString Cat;
            QString txt="";
            if(categoryLst->size()==0) return "";

            txt+="<font color='blue'>Balance by categories:</font><br>";

            txt+="<table cellspacing='1' cellpadding='1' >";
            for(int i=0;i<categoryLst->size();i++){

                Cat=categoryLst->at(i);
                Sum = getTotalByCategory(Cat);
            if(Sum>0){
                txt+="<tr><td>"+Cat+"</td>"+QString("<td>  %0</td>").arg(Sum)+"<td>:</td>"+"<td></td></tr>";

            }else{
                TotalMin+=Sum;
                txt+="<tr><td>"+Cat+"</td>"+"<td></td>"+"<td>:</td>"+QString("<td> %0</td></tr>").arg(Sum);
            }

             TotalSum+=Sum;
             //Sum=0;
            }
            txt+="</table>";
            QString sTotalSum= Utils::toStrWithStrip(TotalSum);
            QString sTotalMin= Utils::toStrWithStrip(TotalMin);
            txt+=nl()+hr()+nl()+sTotalSum+"  :  "+sTotalMin+nl();
            return txt;

}
double BilancePrint::getTotalPerMonthByCategory(QString mm, QString Cat){
    double Sum=0.0;
    QStringList elm;
    bool ok;
            if(!isInList(*monthsLst, mm))
                 return 0.0;
            //Sum
            for(int i=0;i<mtable.size();i++){
                elm= mtable.at(i);
                if((elm.at(0).section("/",1,1).compare(mm)==0)
                 &&
                        (elm.at(1).compare(Cat)==0)
                        )
                      Sum+=elm.at(2).toDouble(&ok); //get amount
            }
            return Sum;

}

/**
 * @brief BilancePrint::getTotalPerMonthYearByCategory
 * @param mm monthYear in format mm/yyyy
 * @param Cat
 * @return
 */
double BilancePrint::getTotalPerMonthYearByCategory(QString mm, QString Cat)
{
    double Sum=0.0;
    QStringList elm;
    bool ok;
            if(!isInList(*monthsLst, mm))
                 return 0.0;
            //Sum
            for(int i=0;i<mtable.size();i++){
                elm= mtable.at(i);
                if((elm.at(0).section("/",1,2).compare(mm)==0)
                 &&
                        (elm.at(1).compare(Cat)==0)
                        )
                      Sum+=elm.at(2).toDouble(&ok); //get amount
            }
            return Sum;

}

QString BilancePrint::printTotalPerMonth(QString mm){
    double Sum=0.0;
            double TotalSum=0.0;
            double TotalMin=0.0;
            QString txt="";
            if(!isInList(*monthsLst, mm))
                    return "";
            //Sum
            if(htmlprint)
                txt+="<br><font color='blue'>Total per month: "+mm+"</font><br>";
            else
                txt+=nl()+"Total per month: "+mm+nl();
            for(int i=0; i< categoryLst->size();i++){
                QString Cat=  categoryLst->at(i);
                Sum= getTotalPerMonthByCategory(mm, Cat);
                if(Sum>0){
                    txt+=Utils::AddSpace(Utils::AddSpace(Cat, 10)+" "+Utils::toStrWithStrip(Sum),17)+" :"+nl();
                }else {
                 TotalMin+=Sum;
                 if(Sum!= 0)
                   txt+=Utils::AddSpace(Cat, 17)+ " : "+Utils::toStrWithStrip(Sum)+nl();
                }
            TotalSum+=Sum;

            }
            TotalRemainSum += TotalSum;
            QString sTotalSum= Utils::toStrWithStrip(TotalSum);
            QString sTotalMin= Utils::toStrWithStrip(TotalMin);
            txt+=hr()+nl()+sTotalSum+"  :  "+sTotalMin+nl();
            if(htmlprint){
             txt+="<font color='red'>Total Balance= "+Utils::toStrWithDec(TotalRemainSum,3)+"</font><br>";
            }else {
                txt+="Total Balance= "+Utils::toStrWithDec(TotalRemainSum,3)+nl();
            }
            return txt;

}

QString BilancePrint::printTotalPerMonthTbl(QString mm)
{
    double Sum=0.0;
            double TotalSum=0.0;
            double TotalMin=0.0;
            QString txt="";
            if(!isInList(*monthsLst, mm))
                    return "";
            //Sum

            txt+="<br><font color='blue'>Total per month: "+mm+"</font><br>";

            txt+="<table cellspacing='0' cellpadding='0'>";
            for(int i=0; i< categoryLst->size();i++){

                QString Cat=  categoryLst->at(i);
                Sum= getTotalPerMonthYearByCategory(mm, Cat);
                if(Sum>0){

                    txt+="<tr><td>"+Cat+"</td>"+QString("<td>  %0</td>").arg(Sum)+"<td>:</td>"+"<td></td></tr>";
                }else {
                 TotalMin+=Sum;
                 if(Sum!= 0)
                    txt+="<tr><td>"+Cat+"</td>"+"<td></td>"+"<td>:</td>"+QString("<td> %0</td></tr>").arg(Sum);
                }

            TotalSum+=Sum;

            }
            txt+="</table>";
            TotalRemainSum += TotalSum;
            QString sTotalSum= Utils::toStrWithStrip(TotalSum);
            QString sTotalMin= Utils::toStrWithStrip(TotalMin);
            txt+=nl()+hr()+nl()+sTotalSum+"  :  "+sTotalMin+nl();
            txt+="<font color='red'>Total Balance= "+Utils::toStrWithDec(TotalRemainSum,3)+"</font><br>";

            return txt;

}
QString BilancePrint::printTotalForMonths(){
    if(monthsLst->size()==0) return "";
            QString txt="";
            for(int i=0;i< monthsLst->size();i++){
                //txt+=printTotalPerMonth(monthsLst->at(i));
                txt+=printTotalPerMonthTbl(monthsLst->at(i));
            }
            return txt;

}
QString BilancePrint::printBilance(){

    if(!isForBilancePrint) return "";
            QString txt=(htmlprint)?"<pre>":"";
            //txt+="<h1>Table name: "+tableName+"</h1>\n";
            if(htmlprint)
            txt+="<big>Table name: <big>"+tableName+"</big></big><br>";
            else
                txt+="Table name: "+tableName+nl();
            txt+=Utils::AddSpace("Balance", 5)+" : "+Utils::AddSpace("Payed",5)+nl();
            txt+="------------------"+nl();
            //txt+=printTotalForCategories();
            txt+=printTotalForCategoriesTbl();
            txt+=printTotalForMonths();
            txt+=(htmlprint)?"</pre>":"";

            return txt;

}
QString BilancePrint::printBilanceForTableAndMonth(QString tableName, QString mmYY){


            QString txt="<pre>";
            txt+="<big>Table name: <big>"+tableName+"</big></big><br>";

            txt+=Utils::AddSpace("Balance", 5)+" : "+Utils::AddSpace("Payed",5)+nl();
            txt+="------------------"+nl();
            //txt+=printTotalForCategories();
            //txt+=printTotalForCategoriesTbl();
            txt+=printTotalPerMonthTbl(mmYY);

            txt+="</pre>";

            return txt;

}
