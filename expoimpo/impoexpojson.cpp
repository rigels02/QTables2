#include "impoexpojson.h"

ImpoExpoJson::ImpoExpoJson()
{

}

void ImpoExpoJson::expoJson(const QString filePath, const QList<MTable> tables)
{
    QFile fi(filePath);
    fi.open(QFile::WriteOnly);

   QJsonDocument doc= toJsonArrayDoc(tables);
    fi.write(doc.toJson(QJsonDocument::Compact));
    fi.close();
}
/**
 * throws Exception
 * @brief ImpoExpoJson::impoJson
 * @param filePath
 * @return
 */
QList<MTable> ImpoExpoJson::impoJson(const QString filePath)
{
    QFile fi(filePath);
    fi.open(QFile::ReadOnly);
   QJsonDocument jdoc = QJsonDocument::fromJson(fi.readAll());

   if(jdoc.isNull()){
       fi.close();
       throw "JSON Doc parsing error!";
   }

    fi.close();
    return fromJsonArrayDoc(jdoc);
}

void ImpoExpoJson::exportData(QString filePath, QList<MTable> tables)
{
    expoJson(filePath, tables);
}

QList<MTable> ImpoExpoJson::importData(QString filePath)
{
    QList<MTable> tables;
    try {
       tables = impoJson(filePath);
    }catch(const char* msg){
        throw msg;
    }
    return tables;
}

const QString tables_str("tables");
const QString name_str("name");
const QString mdate_str("mdate");
const QString data_str("data");
const QString date_str("date");
const QString cat_str("cat");
const QString amount_str("amount");
const QString note_str("note");


QJsonDocument ImpoExpoJson::toJsonArrayDoc(const QList<MTable> tables)
{
    QJsonArray tables_array;

    foreach (MTable table, tables) {
        QJsonObject itemData;
        itemData.insert(name_str,table.getName());

        itemData.insert(mdate_str,ImpoExpoJson::makeMSecSinceEpochDT(table.getDate()));
        QJsonArray data_array;
        foreach (TableData data, table.getData()) {
            QJsonObject e_data;
            e_data.insert(date_str,ImpoExpoJson::makeMSecSinceEpoch(data.getCdate()));
            e_data.insert(cat_str,data.getCat());
            e_data.insert(amount_str,data.getAmount());
            e_data.insert(note_str,data.getNote());
            data_array.append(QJsonValue(e_data));
        }
        itemData.insert(data_str,QJsonValue(data_array));
        tables_array.append(QJsonValue(itemData));
    }
    QJsonObject finalObj;
    finalObj.insert(tables_str,QJsonValue(tables_array));
    QJsonDocument jdoc;
    jdoc.setObject(finalObj);
    return jdoc;
}

QList<MTable> ImpoExpoJson::fromJsonArrayDoc(const QJsonDocument doc)
{
    QList<MTable> tables;
    QJsonObject rootObj = doc.object();
    QJsonValue av = rootObj.value(tables_str);
    QJsonArray array = av.toArray();
    foreach (const QJsonValue &val, array) {
        MTable table;
        table.setId(0);
        table.setName(val.toObject().value(name_str).toString());

        double num = val.toObject().value(mdate_str).toDouble();
        QDateTime dd = ImpoExpoJson::makeQDateTimeFromEpoch(num);
        table.setDate(dd);
        QJsonArray jdata = val.toObject().value(data_str).toArray();
        QList<TableData> data;
        foreach (const QJsonValue &val, jdata) {
            TableData ed;
            ed.setId(0);
            double num= val.toObject().value(date_str).toDouble();
            //QDate dd = QDate::fromJulianDay(num);
            QDate dd= ImpoExpoJson::makeQDateFromEpoch(num);
            ed.setCdate(dd);
            ed.setCat(val.toObject().value(cat_str).toString());
            ed.setAmount(val.toObject().value(amount_str).toDouble());
            ed.setNote(val.toObject().value(note_str).toString());
            data.append(ed);
        }
        table.setData(data);
        tables.append(table);
    }
    return tables;
}

/**
 * @brief makeQDateFromEpoch - Get QDate from Java Date
 * @param msec Java Date timestamp
 * @return QDate
 */
QDate ImpoExpoJson::makeQDateFromEpoch(qint64 msec){
     QDateTime dt;
     dt.setMSecsSinceEpoch(msec);
     return dt.date();
}
/**
 * @brief makeMSecSinceEpoch Get java Date from QDate
 * @param date QDate value
 * @return Java Date timestamp (Time part is 0)
 */
qint64 ImpoExpoJson::makeMSecSinceEpoch(QDate date){
    QDateTime dt;
    dt.setDate(date);
    dt.setTime(QTime(0,0)); //Time part is 0
    return dt.toMSecsSinceEpoch(); //Java Date
}
/**
 * @brief makeQDateFromEpoch - Get QDateTime from Java Date
 * @param msec Java Date timestamp
 * @return QDateTime
 */
QDateTime ImpoExpoJson::makeQDateTimeFromEpoch(qint64 msec){
     QDateTime dt;
     dt.setMSecsSinceEpoch(msec);
     return dt;
}
/**
 * @brief makeMSecSinceEpoch Get java Date from QDateTime
 * @param date QDateTime value
 * @return Java Date timestamp
 */
qint64 ImpoExpoJson::makeMSecSinceEpochDT(QDateTime date){
    QDateTime dt;
    dt= date;
    return dt.toMSecsSinceEpoch(); //Java Date
}
