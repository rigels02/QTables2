#ifndef IEXPORTIMPORT_H
#define IEXPORTIMPORT_H

template <class E>
class IExportImport{
   public:
    virtual void exportData(QString filePath,QList<E> tables)=0; /*throws Exception;*/
    virtual QList<E> importData(QString filePath)=0; /* throws IOException, Exception;*/
};

#endif // IEXPORTIMPORT_H
