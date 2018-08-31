#ifndef IDATASTREAM_H
#define IDATASTREAM_H

#include <QDataStream>

class IDataStream {

   public:
    virtual void writeData(QDataStream &ds) const =0;
    virtual void readData(QDataStream &ds) = 0;

};

#endif // IDATASTREAM_H
