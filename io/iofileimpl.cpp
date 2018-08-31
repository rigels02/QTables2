#include "iofileimpl.h"


const QString IOFileImpl::idxFile = "qindex.idx";

const QString IOFileImpl::dataFile="data";
const QString IOFileImpl::dataExt=".dat";
const QString IOFileImpl::magicSign="11Aug2017@@#$%";

IOFileImpl::IOFileImpl()
{

 QFile fidx(idxFile);
 if(!fidx.exists()){
     createIdxFile(fidx);

 }
 fidx.close();
 readIdxFile();
}

void IOFileImpl::saveAll(QList<MTable> data)
{
    readIdxFile();
    //clean index and data files
    foreach (TableInfo ti, tablesInfo) {
        QFile fi(composeFileName(ti.getId()));
        if(fi.exists()){
            fi.remove();
            fi.close();
        }
    }
    tablesInfo.clear();
   for(int i=0; i<data.size(); i++){
     TableInfo& ti = data[i];
     ti.setId(getNewIndex());
     /**
       If TableInfo date is null, then setup current dateTime,
       otherwise keep existing one
       **/
     if(data[i].getDate().isNull())
            ti.setDate(QDateTime().currentDateTime());
     tablesInfo.append(ti);
     //---//
     try {
     _saveData(ti.getId(),data[i].getData());
     }catch(const char* msg){

         throw msg;
     }

   }
   writeIdxFile();
}

/**
 * @brief IOFileImpl::loadAll
 * throws char* exception
 * @return
 */
QList<MTable> IOFileImpl::loadAll()
{
  readIdxFile();
  QList<MTable> tables;
  foreach (TableInfo ti, tablesInfo) {
        MTable table(ti);
        QList<TableData> data;
        try{
            data = loadData(ti.getId());
        }catch(const char* msg){
            throw msg;
        }
        table.setData(data);
        tables.append(table);
  }
  return tables;
}

TableInfo IOFileImpl::createTable(QString name)
{

    int idx = getNewIndex();
    TableInfo ti(idx,name,QDateTime().currentDateTime());
    tablesInfo.append(ti);

    writeIdxFile();
    return ti;
}

const TableInfo* IOFileImpl::renameTable(int id, QString name)
{
    TableInfo* ti = getInfo(id);
    if(ti==0)
        return 0;
    ti->setName(name);
    ti->setDate(QDateTime().currentDateTime());
    writeIdxFile();
    return ti;
}

bool IOFileImpl::deleteTable(int id)
{
   int idx= getTableInfoIndex(id);
    if(idx< 0)
        return false;
    deleteDataFile(composeFileName(id));

    tablesInfo.removeAt(idx);
    writeIdxFile();
    return true;
}

bool IOFileImpl::deleteAll()
{
    foreach (TableInfo ti, tablesInfo) {
        QFile fi(composeFileName(ti.getId()));
        if(fi.exists()){
            if(!fi.remove()){
                fi.close();
                return false;
            }
           }
        fi.close();
    }
    tablesInfo.clear();
    writeIdxFile();
    return true;
}



int IOFileImpl::getNewIndex(){
  int idx =1;
  foreach (TableInfo ti, tablesInfo) {
      if(ti.getId()!=idx)
          break;
      idx++;
  }
  return idx;
}
void IOFileImpl::createIdxFile(QFile &fi){
 fi.open(QFile::WriteOnly|QFile::Truncate);
 QDataStream ds(&fi);
 ds<<magicSign;
 ds<<tablesInfo.size();
 foreach (TableInfo ti, tablesInfo) {

     ti.writeData(ds);
 }
 fi.flush();

}

/**
 * Throws exception
 * @brief IOFileImpl::readIdxFile
 * @return
 */
void IOFileImpl::readIdxFile()
{
    QFile fi(idxFile);
    fi.open(QFile::ReadOnly);
    QDataStream ds(&fi);
    QString head;
    ds>> head;
    if(head.compare(magicSign)!=0)
        throw "Bad Idx file header!";
    tablesInfo.clear();
    int sz;
    ds>> sz;
    for(int i=0; i< sz; i++){
        TableInfo ti;
        ti.readData(ds);
        tablesInfo.append(ti);
    }
    fi.close();

}

void IOFileImpl::writeIdxFile(){
    QFile fi(idxFile);
    fi.open(QFile::WriteOnly|QFile::Truncate);
    QDataStream ds(&fi);
    writeHeader(ds);
    ds<< tablesInfo.size();
    foreach (TableInfo ti, tablesInfo) {
        ti.writeData(ds);
    }
    fi.close();
}



/**
 * @brief IOFileImpl::getInfo
 * Returns tables Info by its index tid
 * @param tid
 * @return 0 if table not exists
 */
TableInfo* IOFileImpl::getInfo(int tid){
    for(int i=0; i<tablesInfo.size();i++){
        if(tablesInfo[i].getId()==tid){
            return &tablesInfo[i];
        }
    }
    return 0;
}

/**
 *
 * @brief IOFileImpl::getTableInfoIndex
 * Return TablesInfo index in TablesInfo list by its file index
 * @param tid file index
 * @return index or -1 if not exists
 */
int IOFileImpl::getTableInfoIndex(int tid){
    for(int i=0; i<tablesInfo.size();i++){
        if(tablesInfo[i].getId()==tid){
            return i;
        }
    }
    return -1;
}

void IOFileImpl::_saveData(int tid, QList<TableData> data){

    QFile fi(composeFileName(tid));
    try {
    openDataFileForWrite(fi);
      }catch(const char* msg){
          throw msg;
      }
    QDataStream ds(&fi);
    ds<<data.size();
    foreach (TableData td, data) {
        td.writeData(ds);
    }
    fi.close();

}

/**
 * Throw Exceptions
 * @brief IOFileImpl::saveData for table with id tid
 * @param tid table id
 * @param data data to save
 */
void IOFileImpl::saveData(int tid, QList<TableData> data)
{
    readIdxFile();
    TableInfo* tif= getInfo(tid);
    if(tif==0)
         throw "saveData():Wrong argument tid";
    tif->setDate(QDateTime().currentDateTime());

    try {
       _saveData(tid,data);
    }catch(const char* msg){
        throw msg;
    }
    writeIdxFile();

}

QList<TableData> IOFileImpl::loadData(int tid)
{
    readIdxFile();
    TableInfo* tif= getInfo(tid);
    if(tif==0)
         throw "loadData():Wrong argument tid";

    QFile fi(composeFileName(tid));
    try {
    openDataFileForRead(fi);
      }catch(const char* msg){
          throw msg;
      }
    QList<TableData> data;
    QDataStream ds(&fi);
    int sz;
    ds>> sz;
    for(int i=0; i< sz;i++) {
        TableData td;
        td.readData(ds);
        data.append(td);
    }
    fi.close();
    writeIdxFile();
    return data;
}

QList<TableInfo> IOFileImpl::getTablesInfo() const
{
   return tablesInfo;
}


void IOFileImpl::createDataFile(QFile &fi)
{

 if(!fi.open(QFile::WriteOnly|QFile::Truncate)){
     //QMessageBox::critical(0,"Error","Can not create Index file",QMessageBox::Abort);
     throw "Can not create Data file!";
 }
 QDataStream ds(&fi);
 writeHeader(ds);
 fi.close();
}

void IOFileImpl::openDataFileForRead(QFile &fi)
{
    if(!fi.exists()){
        createDataFile(fi);
    }
    if(!fi.open(QFile::ReadOnly)){
        //QMessageBox::critical(0,"Error","Can not create Index file",QMessageBox::Abort);
        throw "Can not open Data file!";
      }

  QDataStream ds(&fi);
  readHeader(ds);

}

void IOFileImpl::openDataFileForWrite(QFile &fi)
{
    if(!fi.exists()){
        createDataFile(fi);
    }
    if(!fi.open(QFile::WriteOnly|QFile::Truncate)){
        //QMessageBox::critical(0,"Error","Can not create Index file",QMessageBox::Abort);
        throw "Can not open Data file!";
      }

  QDataStream ds(&fi);
  writeHeader(ds);
}

bool IOFileImpl::deleteDataFile(QString fn){
  QFile fi(fn);
  if(fi.exists()){
      fi.remove();
      fi.close();
      return true;
  }
  return false;
}

void IOFileImpl::writeHeader(QDataStream &ds)
{
    ds<<magicSign;
}

void IOFileImpl::readHeader(QDataStream &ds)
{
    QString head;
    ds>>head;
    if(head.compare(magicSign)!=0)
        throw "Bad data file header";

}

QString IOFileImpl::composeFileName(int tid){
    QString filename = QString("%0%1%2").arg(dataFile).arg(tid).arg(dataExt);
    return    filename;
}
