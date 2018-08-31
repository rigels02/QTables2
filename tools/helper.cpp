#include "helper.h"

Helper::Helper()
{

}

QVector<QStringList> Helper::composeVector(const QList<TableData> *data)
{
    QVector<QStringList> vector;
    for(int i=0; i< data->size();i++){
       QStringList slist;
       slist<<QString("%0").arg(i); //keep index for use with hyperlink after filtering
       slist<< data->at(i).getCdate().toString("dd/MM/yyyy");
       slist<< data->at(i).getCat();
       slist<< QString("%0").arg(data->at(i).getAmount());
       slist<< data->at(i).getNote();
        vector.append(slist);
     }
    return vector;

}

void Helper::sortByCategory(QList<TableData> &slist)
{
   std::sort(slist.begin(),slist.end(),
              [](const TableData a, const TableData b)-> bool {return a.getCat()<b.getCat();});
}

void Helper::sortByDate(QList<TableData> &slist)
{
    std::sort(slist.begin(),slist.end(),
               [](const TableData a, const TableData b)-> bool {return a.getCdate()<b.getCdate();});

}

void Helper::sortByDateReverse(QList<TableData> &slist)
{
    std::sort(slist.begin(),slist.end(),
               [](const TableData a, const TableData b)-> bool {return a.getCdate()>b.getCdate();});

}
void Helper::sort(QStringList &slist)
{
    std::sort(slist.begin(),slist.end(),
               [](const QString a, const QString b)-> bool {return a < b;});

}

/**
 * @brief Helper::filter
 * returns vector with stringList containing smatch in column col
 * @param col column in stringList, from 0 to row.size-1.
 * @param incom input vector
 * @param smatch word to search for
 * @return vector
 */
QVector<QStringList> Helper::filterForColumn(int col, const QVector<QStringList> &incom, QString smatch)
{   QVector<QStringList> vector;
    if(incom.isEmpty()) return vector;
    if(col<0 || col >= incom.at(0).size())
        throw "Illegal argument!";
    for(int i=0; i<incom.size(); i++){
        QString el= incom.at(i).at(col);
        if(smatch.isEmpty()){
             if( el.isEmpty())
                vector.append(incom.at(i));
        }else  if(el.contains(smatch,Qt::CaseInsensitive)){
            vector.append(incom.at(i));
        }
    }
    return vector;
}

QWidget* Helper::getBusyBox(QString msg){
    QVBoxLayout* layout = new QVBoxLayout;
    QWidget*  win = new QWidget;

    QProgressDialog* progress = new QProgressDialog(msg, QString(), 0, 0);
    progress->setWindowModality(Qt::WindowModal);
    progress->setMinimumDuration(1500); // 1.5 sec
    layout->addWidget(progress,Qt::AlignCenter);

    //Important: QProgressDialog Should be added to QWidget here
    win->setLayout(layout);
    win->setWindowTitle("Please wait");
    //for progress dialog better looks if use show() instead of showMaximized()
    //N701
    win->show();

    return win;
}
