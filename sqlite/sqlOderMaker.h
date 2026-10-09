#ifndef SQLTABLE_H
#define SQLTABLE_H
#include <QStringList>
#include <QDebug>

#include <network/tcpwork.h>

#define SOM_TcpDebug         //需要调试此模块请取消注释

QString Variant2String(QVariant value);

class SqlOderMaker
{
public:
    explicit SqlOderMaker();

    QString CreatTableIfNotExits(QString TableName, QString PrimaryKeyName, QStringList Keys, QStringList Table_Types);
    QString InsertNewRow(QString TableName, QStringList Keys, QVariantList Values);

    QString UpdateCurrentRow(QString TableName,
                             QString PrimaryKeyName,
                             QVariant PrimaryKeyValue,
                             QStringList Keys,
                             QVariantList Values);

    QString QuerryData(QString TableName = "", QString Columns = "*", QString Conditions = "" , QString LIMIT = "");
    QString DeleteCurrentRow(QString TableName, QString Key, QString Value);
#ifdef SOM_TcpDebug
    tcpwork debuger;
#endif
} ;

#endif // SQLTABLE_H
