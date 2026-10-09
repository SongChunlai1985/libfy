#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore/QCoreApplication>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDateTime>

#include <QDebug>


#include <QJsonArray>
#include <QSqlRecord>

#include "sqlOderMaker.h"
#include <network/tcpwork.h>

struct TableInfo
{
    QString Name;
    QString PrimaryKeyName;
    QStringList Keys;
    QStringList Types;
};

struct DatabaseInfo
{
    QString DatabaseType;
    QString DatabaseName;
    QString HostName;
    QString UserName;
    QString PassWord;
    QList<TableInfo> TableInfos;

    DatabaseInfo();
    DatabaseInfo(    QString DatabaseType_,
                     QString DatabaseName_,
                     QString HostName_,
                     QString UserName_,
                     QString PassWord_, QList<TableInfo> TableInfos_ = {TableInfo() ,TableInfo()})
    {
        DatabaseType = DatabaseType_;
        DatabaseName = DatabaseName_;
        HostName = HostName_;
        UserName = UserName_;
        PassWord = PassWord_;
        TableInfos = TableInfos_;
    }
};


class  DataBaseCommander: public QObject{
    Q_OBJECT
public:
    explicit DataBaseCommander();

    QSqlDatabase QDatabase;                                         //一个数据库连接器
    SqlOderMaker sqlOderMaker;                                      //一个Sql语句制作器
    QSqlQuery query;

    int ConnectDatabase(DatabaseInfo databaseInfo);

    QJsonObject ExecuteSqlOder2JsonObject(QString sqlOder);
    QList<QMap<QString, QVariant> > ExecuteSqlOder2MapList(QString sqloder);

    QJsonObject CreatTableIfNotExits(TableInfo tableInfo);
    bool InsertNewRow(TableInfo Info, QVariantList InsertData);
    QList<QMap<QString, QVariant> > Querry(TableInfo Info,
                                           QString Columns = "*",
                                           QString Conditions = "",
                                           QString LIMIT = "");
    //    Q_INVOKABLE void DeleteRow(QString TableName, QString PrimaryKeyName, QString PrimaryKeyValue);
    QJsonObject UpdateRow(TableInfo Info, QVariant PrimaryKeyValue, QVariantList values);
    void SqlClose();
    QVariant GetTotalRows(TableInfo Info);
    QMap<QString, QVariant> GetRowValues(QString TableName, QString PrimaryKeyName, QVariant PrimaryKeyValue);
    QVariantList GetRowTemp(QString TableName, int rowNum);
    QJsonObject QuerryJ(TableInfo Info,
                        QString Columns = "*",
                        QString Conditions = "",
                        QString LIMIT = "");

    tcpwork debuger;
};

#endif // WORKTHREAD_H
