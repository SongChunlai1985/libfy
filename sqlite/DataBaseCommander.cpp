#include "DataBaseCommander.h"
DataBaseCommander::DataBaseCommander()
{

}

QJsonObject DataBaseCommander::ExecuteSqlOder2JsonObject( QString sqlOder )
{
#ifdef FyTcpDebug
    debuger.dbg(sqlOder);
#endif
    QSqlQuery query = QDatabase.exec(sqlOder);                                                            //执行SQL
    bool error = query.lastError().type() != QSqlError::NoError;
    QJsonObject res;
    res.insert("error", error);
    if (error)
    {
        res.insert("errorStr", query.lastError().text());
#ifdef FyTcpDebug
        debuger.dbg("errorStr" + query.lastError().text() + "\r\n");
#endif
        return res;
    }

    if (query.isSelect())
    {
        QJsonArray rows;
        int size = 0;
        int fields = query.record().count();
        while (query.next())
        {
            QJsonObject value;
            for (int i = 0; i < fields; ++i)
                value.insert(query.record().fieldName(i), query.value(i).toJsonValue());
            rows.append(value);
            ++size;
        }
        res.insert("length", size);
        res.insert("items", rows);
#ifdef FyTcpDebug
        debuger.dbg( "查询结果: <<" + JsonObject2ByteArray(res));
#endif
        return res;
    }

    res.insert("rowsAffected", query.numRowsAffected());
    res.insert("insertId", query.lastInsertId().toString());
#ifdef FyTcpDebug
    debuger.dbg( "执行结果: <<" + JsonObject2ByteArray(res));
#endif
    return res;
}

QList<QMap<QString, QVariant>> DataBaseCommander::ExecuteSqlOder2MapList(QString sqloder )
{
#ifdef FyTcpDebug
    debuger.dbg("ExecuteSqlOder2MapList: " + sqloder);
#endif

    QSqlQuery query = QDatabase.exec(sqloder);
    QList<QMap<QString, QVariant>> Valuess;
    int fields = query.record().count();
#ifdef FyTcpDebug
    QJsonArray rows;
#endif
    while (query.next())
    {
        QMap<QString, QVariant> values;
#ifdef FyTcpDebug
        QJsonObject valuesJ;
#endif
        for (int i = 0; i < fields; ++i)
        {
            values.insert(query.record().fieldName(i), query.value(i));
#ifdef FyTcpDebug
            valuesJ.insert(query.record().fieldName(i), query.value(i).toJsonValue());
#endif
        }
        Valuess.push_back(values);
#ifdef FyTcpDebug
        rows.push_back(valuesJ);
#endif
    }
#ifdef FyTcpDebug
    QJsonObject rowsJ;
    rowsJ.insert("items",rows);
    debuger.dbg(JsonObject2ByteArray(rowsJ));
#endif
    return Valuess;
}

int DataBaseCommander::ConnectDatabase(DatabaseInfo databaseInfo)
{
    QDatabase = QSqlDatabase::addDatabase(databaseInfo.DatabaseType);                                                        //"QSQLITE", "QMYSQL", "QMYSQL3", "QODBC", "QODBC3", "QPSQL", "QPSQL7"
    QDatabase.setDatabaseName(databaseInfo.DatabaseName);
    QDatabase.setHostName(databaseInfo.HostName);
    QDatabase.setUserName(databaseInfo.UserName);
    QDatabase.setPassword(databaseInfo.PassWord);
    QDatabase.open();

    qDebug()<<__FUNCTION__<<" sql::connectdb(): QSqlDataBaseCommander::drivers()"
           << QSqlDatabase::drivers()<< (QDatabase.isOpen() ? "open" : "close");

    return QDatabase.isOpen();
}

QJsonObject DataBaseCommander::CreatTableIfNotExits(TableInfo tableInfo)
{
    QString sqlOder = sqlOderMaker.CreatTableIfNotExits(tableInfo.Name,
                                                        tableInfo.PrimaryKeyName,
                                                        tableInfo.Keys,
                                                        tableInfo.Types);
    return ExecuteSqlOder2JsonObject(sqlOder);
}

bool DataBaseCommander::InsertNewRow(TableInfo Info, QVariantList RowValues_)
{
    QString sqlOder = sqlOderMaker.InsertNewRow(Info.Name, Info.Keys, RowValues_);
    return ExecuteSqlOder2JsonObject(sqlOder)["error"].toBool();
}

QVariant DataBaseCommander::GetTotalRows(TableInfo Info)
{
    QList<QMap<QString, QVariant>> res = Querry(Info, "COUNT(*)");;
    if(res.empty()) return int(0);
    return  res[0]["COUNT(*)"].toInt();
}

QList<QMap<QString, QVariant>> DataBaseCommander::Querry(TableInfo Info, QString Columns, QString Conditions, QString LIMIT)
{
    QString sqlOder = sqlOderMaker.QuerryData(Info.Name, Columns, Conditions, LIMIT);
    return ExecuteSqlOder2MapList(sqlOder);
}

QJsonObject DataBaseCommander::QuerryJ(TableInfo Info, QString Columns, QString Conditions, QString LIMIT)
{
    QString sqlOder = sqlOderMaker.QuerryData(Info.Name, Columns, Conditions, LIMIT);
    return ExecuteSqlOder2JsonObject(sqlOder);
}

QMap<QString, QVariant> DataBaseCommander::GetRowValues(QString TableName,
                                                               QString PrimaryKeyName,
                                                               QVariant PrimaryKeyValue)
{

    QString sqlOder = sqlOderMaker.QuerryData(TableName, "*", " `" + PrimaryKeyName + "` = " + Variant2String(PrimaryKeyValue) + " ");
    QList<QMap<QString, QVariant>> row = ExecuteSqlOder2MapList(sqlOder);
    if(row.empty())
    {
        return  QMap<QString, QVariant>();
    }
    return row.first();
}

QJsonObject DataBaseCommander::UpdateRow(TableInfo Info, QVariant PrimaryKeyValue, QVariantList RowValues)
{
    QString sqlOder = sqlOderMaker.UpdateCurrentRow(Info.Name, Info.PrimaryKeyName, PrimaryKeyValue, Info.Keys, RowValues);
    return ExecuteSqlOder2JsonObject(sqlOder);
}

void DataBaseCommander::SqlClose()
{
    QDatabase.close();
}

//void DataBaseCommander::DeleteRow(QString TableName, QString PrimaryKeyName, QString PrimaryKeyValue)
//{
//    QString sqlOder = sqlOderMaker.DeleteCurrentRow(TableName, PrimaryKeyName, PrimaryKeyValue);
//#ifdef FyTcpDebug
//    debuger.dbg(sqlOder);
//#endif
//    return ;
//}


