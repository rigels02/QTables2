#ifndef TABLESFILTER_H
#define TABLESFILTER_H
#include <QStringList>
#include "../model/tableinfo.h"


/**
 * @brief The TablesFilter class
 * TODO Implement filter for tables selection by name
 * Takes TableInfo list and prepare list of tables with names containing given words
 */
class TablesFilter
{
public:
    static QList<TableInfo> doFilter(const QList<TableInfo> &list, const QString words);
    static QList<TableInfo> doFilter(const QList<TableInfo> &list, const QStringList words);
    static QStringList prepareWords(QString words);

    static int wordPos(const QString inputString, QString words);
};

#endif // TABLESFILTER_H
