#include "sqlOderMaker.h"

SqlOderMaker::SqlOderMaker()
{

}

QString Variant2String(QVariant value)
{
    QString Value = "NULL";
    if(value.type() == QVariant::String) Value = "'" + value.toString() + "'";
    if(value.type() == QVariant::Int) Value = QString::number(value.toInt());
    if(value.type() == QVariant::Double) Value = QString::number(value.toDouble());
    return Value;
}

QString SqlOderMaker::CreatTableIfNotExits(QString TableName, QString PrimaryKeyName, QStringList Keys, QStringList DataTypes)
{
    QString sqlOder = "CREATE TABLE IF NOT EXISTS `" + TableName + "` ( ";
    int i = 0;
    for (i = 0; i < Keys.length() ; i++) {
        sqlOder += "`" + Keys[i] + "` " + DataTypes[i] + " , ";
    }
    sqlOder += " PRIMARY KEY (`" + PrimaryKeyName + "`))" ;
#ifdef SOM_TcpDebug
    debuger.dbg(sqlOder);
#endif
    return sqlOder;
}

QString SqlOderMaker::InsertNewRow(QString TableName, QStringList Keys, QVariantList Values)
{
    QString sqlOder = "INSERT INTO `" + TableName + "` (";
    int col = 0;
    for (col = 0; col < Keys.length() -1; col++)
    {
        sqlOder += " `" + Keys[col] + "`,";
    }
    sqlOder += " `" + Keys[col] + "`)" +
            " VALUES (" ;
    QString Value = "NULL";
    for (col = 0; col < Keys.length() -1; col++)
    {
        Value = Variant2String(Values[col]);
        sqlOder += Value + ", ";
    }
    sqlOder += Value;
    sqlOder += " );" ;
#ifdef SOM_TcpDebug
    debuger.dbg(sqlOder);
#endif
    return sqlOder;
}

QString SqlOderMaker::UpdateCurrentRow(QString TableName, QString PrimaryKeyName, QVariant PrimaryKeyValue,
                                       QStringList Keys, QVariantList Values)
{
    QString sqlOder = " UPDATE `" + TableName + "` SET ";
    int col = 0;
    QString Value = "NULL";
    for (col = 0; col < Keys.length() -1; col++) {
        if(Keys[col] != PrimaryKeyName)
        {
            Value = Variant2String(Values[col]);
            sqlOder += " `" + Keys[col] + "` = " + Value + ", " ;
        }
    }
    QString primaryKeyValue = Variant2String(PrimaryKeyValue);
    sqlOder += " `" + Keys[col] + "` = " + Value + " " +                 //可能需要去掉单引号
            " WHERE (`" + PrimaryKeyName + "` = " + primaryKeyValue + " ); ";
#ifdef SOM_TcpDebug
    debuger.dbg(sqlOder);
#endif
    return sqlOder ;
}

QString SqlOderMaker::QuerryData(QString TableName, QString Columns, QString Conditions, QString LIMIT)
{
    QString sqlOder;
    if(Conditions == ""){
        sqlOder =
                "SELECT " + Columns + " FROM " + TableName + " " + LIMIT + " ;"
                ;
        return sqlOder;
    }
    sqlOder =
            "SELECT " + Columns + " FROM " + TableName + " WHERE ( " + Conditions + " ) " + LIMIT + ";"
            ;
#ifdef SOM_TcpDebug
    debuger.dbg(sqlOder);
#endif
    return sqlOder;
}

QString SqlOderMaker::DeleteCurrentRow(QString TableName, QString Key, QString Value)
{
    QString sqlOder =
            "DELETE FROM " + TableName + " WHERE (`" + Key + "` = '" + Value +"' );"
            ;
#ifdef SOM_TcpDebug
    debuger.dbg(sqlOder);
#endif
    return sqlOder;
}
