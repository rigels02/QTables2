#include "impexp.h"

static const QString cDefaultTable="0";
static const int  DefaultTable= 0 ;
static const int CustomTable= 1;

/**
 * SumColNum - sum column number for default table.
 *
 */
        QString sSumColNum="2";
/**
*
* MTableHeadRec is default table record.<br>
* RmsName= MTable, TableName= Izdevumi.<br>
* LCol area size= 3 ,see LCol<br>
* The cols 0,1,2 are displayed in the list by default.<br>
* Max. 6 columns might be displayed.<br>
* @see pack.MyMidl.LCol
*/

 QStringList MTableHeadRec=
     QStringList()<<"Izdevumi"<<cDefaultTable<<sSumColNum<<"4"<<"0"<<"1"<<"2"<<"3"<<""<<"";

const int tableTypePosition= 1;

static QStringList  BlankHeadRec= QStringList()<<""<<""<<""<<""<<""<<""<<""<<""<<""<<"";
static QStringList cDefTypes= QStringList()<<"date"<<"choice"<<"float"<<"text";
static QStringList Titles=QStringList()<<"Date"<<"Category"<<"Amount"<<"Notes";

ImpExp::ImpExp(QList<MTable> *tables)
{
    ErrTxt="";
    //ImpExp::OK=true;
    OK=true;
    m_inputTables = tables;
    DumpTxt="";
    Delim="|";

}

ImpExp::~ImpExp(){

}
QString ImpExp::errorTxt(){
QString err=ErrTxt;
ErrTxt="";
OK=true;
    return err;
}
void ImpExp::error(QString txt){
OK=false;
ErrTxt=txt;
}
void ImpExp::dumpHeader(QStringList *helm){
    int sz=helm->size();
    if(sz<BlankHeadRec.size()){
        error("Wrong HEader records length!");
    return;
    }
    DumpTxt+="\n";
    for(int i=0;i<sz;i++){
        DumpTxt+=helm->at(i);
        //if(i<sz-1)
            DumpTxt+=",";
    }

    DumpTxt+="\n";
}
void ImpExp::dumpData(){
    //if(mtable.isEmpty() ) return;
    QStringList elm;
    //this.DumpTxt+="\n"+TableTitle+"\n";
    DumpTxt+="{";
    for(int i=0;i<mtable.size();i++){
         elm=mtable.at(i);
            for(int j=0;j<Titles.size();j++){
                DumpTxt+=elm.at(j)+Delim;
            }
            DumpTxt+='\n';
        }
    DumpTxt+="}";
    if(mtable.size()==0) DumpTxt+="\n";
}
bool ImpExp::getMTable(int tableIdx){

    //if(mlist->tmgr->getTableCount()< 1) //no tables yet stored
    //       return false;

    //tableTitle= mlist->tmgr->getTableTitle();

    //get table type , column types and column names
    //tableType= tmgr->getTableType();
    //types= tmgr->getColTypes();
    //this->Titles= mlist->tmgr->getColTitles();
    //LCol=tmgr->getLCol();



  if( getTableDataByIdx(tableIdx)){
  return true;
  }
return false;
}

bool ImpExp::getTableData(QString tableStoreName){

 mtable.clear();
 for(int i=0; i<m_inputTables->size(); i++){
     if(m_inputTables->at(i).getName().compare(tableStoreName)==0){
            QList<TableData> data= m_inputTables->at(i).getData();
         for(int d=0; d< data.size(); d++){

         mtable.append(getDataRow(data.at(d)));
         }
         return true;
     }
 }
 return false;
}
QStringList ImpExp::getDataRow( TableData row){
    QStringList slst;
    slst<<row.getCdate().toString("dd/MM/yyyy");
    slst<<row.getCat();
    slst<<QString("%0").arg(row.getAmount());
    slst<<row.getNote();
    return slst;
}
bool ImpExp::getTableDataByIdx(int idx){

    mtable.clear();
    QList<TableData> data= m_inputTables->at(idx).getData();
    for(int d=0; d< data.size(); d++){

        mtable.append(getDataRow(data.at(d)));
    }


    return true;
}

QStringList ImpExp::makeHeader(int idx){
    TableInfo ti = m_inputTables->at(idx);
    QStringList slst= MTableHeadRec;
    slst[0]= ti.getName();
    return slst;

}
bool ImpExp::makeOldExport(){

DumpTxt="";
QString filename;
QStringList helm;
if(m_inputTables->size()>0 ){
    for(int i=0;i< m_inputTables->size();i++){

        if(!getMTable(i)) return false;
        helm= makeHeader(i);
        dumpHeader(&helm);
        dumpData();
    }
return true;
}
return true;
}
QString ImpExp::exportData(){
    //ttt();
    if(makeOldExport())
        return DumpTxt;
    else
        return QString();
}

/**
Get substring from str starting from index startidx (min=0) and ending
by index lastidx (not included).
*/
QString ImpExp::substring(QString str, int startidx, int lastidx){
    QString res="";
    for(int i=startidx;i<lastidx;i++)
        res+=str.at(i);
    return res;
}
void ImpExp::ttt(){
    QString st="a,b,c,d,v";
    QString res=substring(st,2,3);
    qDebug()<< QString("----> %0").arg(res);
    QString res1=st.mid(2,3-2);
    qDebug()<< QString("---->> %0").arg(res1);
}
//-------import part --------//

/**
 * Get data to be imported: header and table data.
 * In 1st pass store=false, because data must be checked.
 * In 2nd pass store=true, we may save given data.
 * @param store - true - if to be stored, false - not to be stored
 * @return - false if any error
 */
bool ImpExp::get2Import(bool store){
    //main loop


    while(idx1<idx2){

    if(!readHeader()) return false;
    tType=getTableType();
    if(tType == CustomTable){
    //custable= new CustomTable();
        QString tn= htable.at(htable.size()-1).at(0);
        error(QString("Custom Table Not supported!\nTable name is: %1").arg(tn));
        return false;
        //if(!getColumns()) return false;
    } else {
        //default table, set default columns
        colnames=Titles;
        coltypes=cDefTypes;
    }
    if(!getData()) return false;

    //DebugDump(); //for debug
    //add new  mtable record to list m_tables
    if(store) {
        if(!htable.isEmpty())
                  addMTable();
    }


    //after store reset mtable
    mtable.clear();
    }//while

    return true;
}

bool ImpExp::execImport(QString imptxt){
    htable.clear();
    mtable.clear();
    mtable.clear();
    m_tables.clear();
    //htable= new QVector<QStringList>();
    helmidx=-1;
    //mtable=new QVector<QStringList>();
    //melmidx=-1;

    if(imptxt==0|| imptxt.trimmed().length()==0) {
        error("Nothing to import!\n");
        return false;
    }
    impTxt=imptxt;
    idx1=0;idx2=impTxt.length()-1;
    //idxn=impTxt.indexOf('\n');
    if(idx1==idx2 ) return true;

    //QWidget * busy= Helper::getBusyBox("Importing data...");


    //pass 1, do not store data
    if(!get2Import(false)) goto FAULT;
    //reset header and indexes to make pass2 with storing
    helmidx=-1;
    htable.clear();
    idx1=0;idx2=impTxt.length()-1;


    if(!get2Import(true)){

       goto FAULT;
    }

//SUCCESS
    //close and delete busy !
    //busy->close();
    //delete busy;
    return true;

FAULT:
    //busy->close();
    //delete busy;
    return false;
}

QList<MTable> ImpExp::getImportedTables() const
{
    return m_tables;
}

void ImpExp::exportData(QString filePath, QList<MTable> tables)
{
    m_inputTables= &tables;
    QString sexpo = exportData();
    QFile fi(filePath);
    if(fi.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream tos(&fi);
        tos.setCodec("UTF-8");
        tos<<sexpo;
        fi.close();
    }
}

QList<MTable> ImpExp::importData(QString filePath)
{
    //QList<MTable> tables;
    QString simpo;
    QFile fi(filePath);
    if(fi.open(QIODevice::ReadOnly)){
        QTextStream tis(&fi);
        tis.setCodec("UTF-8");
        simpo = tis.readAll();
        fi.close();
    }
    if(!execImport(simpo)){
    throw errorTxt();

    }
    return getImportedTables();

}

void ImpExp::addTableRecord(QStringList sheader){
    /*
     *Exported table in Old format does not contain
     * Table modify dateTime. Set it to null.
     * During of saving in file/DB the Table's modify
     * dateTime will be assigned.
     **/
    TableInfo ti(0,sheader.at(0),QDateTime());
    MTable table(ti);
    QList<TableData> data;
    for(int i=0; i<mtable.size();i++){
        TableData td;
        td.setId(0);
        td.setCdate(QDate().fromString(mtable.at(i).at(0),"dd/MM/yyyy"));
        td.setCat(mtable.at(i).at(1));
        bool ok=true;
        td.setAmount(mtable.at(i).at(2).toDouble(&ok));
        td.setNote(mtable.at(i).at(3));
        data.append(td);
        }
        table.setData(data);
        m_tables.append(table);

}
void ImpExp::addMTable(){
    //mlist->tmgr->Modified=true;
    if(tType== DefaultTable){
        addTableRecord(htable.at(helmidx));


    } /***else if(stType==mlist->tmgr->CustomTable){

        mlist->tmgr->addCustomHeaderRecord(
                htable.at(helmidx)
                                );

    }
    ****/
}

int ImpExp::rowsnumber(QString rows){
    int count=0,fromIndex=0;
    int idx=0;
    while(idx != -1){
    idx=rows.indexOf('\n', fromIndex);
    if(idx!= -1) count++;
    fromIndex=idx+1;
    }
    return count;
}
int ImpExp::colsnumber(QString row){
    int count=0,fromIndex=0;
    int idx=0;
    while(idx != -1){
    idx=row.indexOf(Delim, fromIndex);
    if(idx!= -1) count++;
    fromIndex=idx+1;
    }
    return count;
}
int ImpExp::hcolsnumber(QString row){
    int count=0,fromIndex=0;
    int idx=0;
    while(idx != -1){
    idx=row.indexOf(',', fromIndex);
    if(idx!= -1) count++;
    fromIndex=idx+1;
    }
    return count;
}
QStringList ImpExp::getHCols(QString row){
    //QStringList *Cols= new QStringList();
    QStringList Cols;
    int fromIndex=0,idx=0;

    for(int i=0;i<hcolsnumber(row);i++){
    idx=row.indexOf(',', fromIndex);
    Cols.append(row.mid(fromIndex, idx-fromIndex).trimmed());
    fromIndex=idx+1;
    }
    return Cols;
}
bool ImpExp::getCols(QString row){

    QStringList Cols;
    int fromIndex=0,idx=0;

    for(int i=0;i<colsnumber(row);i++){
    idx=row.indexOf(Delim, fromIndex);
    Cols.append(row.mid(fromIndex, idx-fromIndex).trimmed());
    fromIndex=idx+1;
    }
    //check types
    if(Utils::isValidRow(coltypes, Cols)){

        mtable.append(Cols);
        return true;
    }else {
        error(QString("Wrong column type!\nrow: %1\n").arg(row)+
                    Utils::ErrorDetails());
    }
    return false;
}
bool ImpExp::getColType(QString row){
    int fromIndex=0,idx=0;

    idx=row.indexOf(',', fromIndex);
    if(idx== -1) return false;
    colnames.append(row.mid(fromIndex, idx-fromIndex).trimmed());
    fromIndex=idx+1;
    //idx=row.indexOf('\n', fromIndex);
    //if(idx== -1) return false;
    coltypes.append(row.mid(fromIndex).trimmed());

    return true;
}
bool ImpExp::getData(){
    QString rows= getBlock();
    if(rows.isNull()) return false;
    if(rows.isEmpty()) return true; //no data, empty table
    int endIndex=rows.indexOf('\n', 0);
    int beginIndex=0;
    QString row;
    int rowcount=rowsnumber(rows);
    for(int i=0;i<rowcount;i++){

        row=rows.mid(beginIndex, endIndex-beginIndex);
        //check row
        if(colsnumber(row)!= colnames.length()) {
            error(QString("Wrong columns number!\nCheck delimiters.\nrow:%1").arg(row));
            return false;
        }
        if(!getCols(row)) return false;
        //next
        beginIndex=endIndex+1;
        endIndex=rows.indexOf('\n', beginIndex);
    }

    return true;
}
static QString BlkOpen="{";
static QString BlkClose="}";

QString ImpExp::getBlock(){
    //find '{' and '}' positions
    idx1=impTxt.indexOf(BlkOpen, idx1);
    if(idx1== -1) return QString();
    idx1++;
    int idx_1=idx1;//startpoint
    int idx_2;
    idx_2=impTxt.indexOf(BlkClose, idx_1);
    idxn=impTxt.indexOf('\n', idx_1);
    if(idx_2== -1) return QString();
    idx1=idx_2+1; //next block startpoint
    //idx_2--; //end point
    //get col rows block
    QString rows= impTxt.mid(idx_1, idx_2-idx_1);
    return rows;
}
bool ImpExp::getColumns(){
    QString rows= getBlock();
    if(rows.isNull()) return false;
    int endIndex=rows.indexOf('\n', 0);
    int beginIndex=0;
    QString row;
    int rowcount=rowsnumber(rows);
    //create fields
    colnames=QStringList();
    coltypes=QStringList();

    for(int i=0;i<rowcount;i++){

        row=rows.mid(beginIndex, endIndex-beginIndex);

        if(!getColType(row)) return false;
        //next
        beginIndex=endIndex+1;
        endIndex=rows.indexOf('\n', beginIndex);
    }
    //get next '\n' position
    //idx1=idx_2+1;

    return true;
}
int ImpExp::getTableType(){
    QStringList elm= htable.at(helmidx);
    return elm.at(tableTypePosition).toInt();
}

bool ImpExp::readHeader(){
    //get header row
    idxn=impTxt.indexOf('\n', idx1);
    if(idxn==-1){
        error("Bad header!\n");
        return false;
    }
    QString sh= impTxt.mid(idx1, idxn-idx1);
    while(sh.trimmed().length()==0){
    //skip spaces and \n
        idx1=idxn+1;
    //get next '\n' position
    idxn=impTxt.indexOf('\n', idx1);
    if(idxn== -1) return false;
    sh= impTxt.mid(idx1, idxn-idx1);
    }
    //unpack header

    QStringList header=getHCols(sh);
    QStringList Header=QStringList();
    //for import is used header without resource storage name ,
    //so, check gotten header size
    if(header.length()!= MTableHeadRec.size()) {
        error("Wrong header size!");
        return false;
    }
    //copy new header

    for(int i=0;i<header.length();i++){
        //Header[k]=header[i];
        Header.insert(i,header.at(i));
    }
    if(isDuplicateTableName(header.at(0))){
        error(QString("Duplicate or Empty Table name not allowed!: %1").arg(header.at(0)));
        return false;
    }
    if(header.at(0).trimmed().isEmpty()){
        error("Empty Table name not allowed!");
        return false;
    }
    htable.append(Header);
    helmidx++;
    return true;
}

/**
Avoid dublicated table name in case of import new tables into existing now.
*/
bool ImpExp::isDuplicateTableName(QString title){
    //find in imported array
    for(int i=0;i< htable.size();i++)
        //if(htable.at(i).at(mlist->tmgr->getTableTitlePos()-1).compare(title)==0)
        if(htable.at(i).at(0).compare(title)==0)
        //if(title.equals(((String[])htable.elementAt(i))[MTableManager.cTableTitle]))
            return true;//Duplicated !
    return false;
}
