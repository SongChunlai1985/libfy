#ifndef MSXLSX_H
#define MSXLSX_H

#include "xlsxio_read.h"
#include "xlsxio_write.h"
#include <QList>
#include <QString>
#include <QDebug>
class msxlsx
{
public:
    msxlsx();
    QList<QVariantList> read(QString xlsxFileName);
    QVariantList sheetList(QString xlsxFileName);
    void write(QString xlsxFileName , QList<QVariantList> table);
};

#endif // MSXLSX_H
