#include "appsettings.h"

AppSettings::AppSettings(QString fileName)
{
  this->fileName = fileName;

}
void AppSettings::saveTableIdx(int idx){
    QFile fi(this->fileName);
    if(!fi.exists()){
        fi.open(QFile::WriteOnly);
    }else{
        fi.open(QFile::WriteOnly|QFile::Truncate);
    }
    QDataStream ds(&fi);
    ds<< idx;
    fi.close();
}

int AppSettings::readTableIdx(){
    QFile fi(this->fileName);
    if(!fi.exists()) return -1;
    fi.open(QFile::ReadOnly);
    QDataStream ds(&fi);
    int idx= -1;
    ds>> idx;
    fi.close();
    return idx;
}
