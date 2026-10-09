#include "DatabaseController.h"
DatabaseController::DatabaseController()
{

}

void DatabaseController::Init(QString UserName, QString PassWord)
{
    Students_tblvisionrecord_TotalColumns = tblvisionrecord_table_model_horHeader.size();

    users.UserName = UserName;
    users.PassWord = PassWord;

    student.UserName = UserName;
    student.PassWord = PassWord;

    QStringList Students_tblvisionrecord_Keys;
    Students_tblvisionrecord_Keys = Csv.autoKeys(Students_tblvisionrecord_TotalColumns);
    Students_tblvisionrecord_Keys.insert(0, "k00_PrimaryKey");
    student.TableInfos[tblstudentmaster].Keys = Students_tblvisionrecord_Keys;

    dataBaseCommander[DB_users].ConnectDatabase(users);
    dataBaseCommander[DB_users].CreatTableIfNotExits(users.TableInfos[tbluser]);
    dataBaseCommander[DB_users].CreatTableIfNotExits(users.TableInfos[tblstudentmaster]);

    dataBaseCommander[DB_student].ConnectDatabase(student);
    dataBaseCommander[DB_student].CreatTableIfNotExits(student.TableInfos[tblstudent]);
    dataBaseCommander[DB_student].CreatTableIfNotExits(student.TableInfos[tblvisionrecord]);
}

QJsonObject DatabaseController::Students_tblstudent_QuerryJ(QString Columns,
                                                            QString Conditions,
                                                            QString LIMIT)
{
    return dataBaseCommander[DB_student].QuerryJ(student.TableInfos[tblstudent], Columns, Conditions, LIMIT);
}

void DatabaseController::Students_tblstudent_Insert(QVariantList student_Info)
{
    if(dataBaseCommander[DB_student].GetRowValues(student.TableInfos[tblstudent].Name,
                                                  student.TableInfos[tblstudent].PrimaryKeyName,
                                                  student_Info[0]).empty())
    {
        dataBaseCommander[DB_student].InsertNewRow(student.TableInfos[tblstudent], student_Info);
    }
    else
    {
        dataBaseCommander[DB_student].UpdateRow(student.TableInfos[tblstudent],
                                                student_Info[0],
                                                student_Info);
    }
}

//QList<QMap<QString, QVariant>> DatabaseController::Students_tblvisionrecord_Querry(QString Columns,
//                                                                                   QString Conditions ,
//                                                                                   QString LIMIT)
//{
//    return dataBaseCommander[DB_student].Querry(student.TableInfos[tblvisionrecord], Columns, Conditions, LIMIT);
//}

QJsonObject DatabaseController::Students_tblvisionrecord_QuerryJ(QString Columns,
                                                                 QString Conditions ,
                                                                 QString LIMIT)
{
    return dataBaseCommander[DB_student].QuerryJ(student.TableInfos[tblvisionrecord], Columns, Conditions, LIMIT);
}

/*插入到表的最后一行 k00_PrimaryKey_Value的值刚好是最后一行行号*/
void DatabaseController::Students_tblvisionrecord_Insert(QVariantList values)
{
    QVariant total = dataBaseCommander[DB_student].GetTotalRows(student.TableInfos[tblvisionrecord]);
    student_tblvisionrecord_k00_PrimaryKey_Value = QString::number(total.toInt());
    values.insert(0, student_tblvisionrecord_k00_PrimaryKey_Value);
    dataBaseCommander[DB_student].InsertNewRow(student.TableInfos[tblvisionrecord], values);                                                                      //增
}

QJsonObject DatabaseController::Students_tblvisionrecord_Update(QVariantList values)
{
    return dataBaseCommander[DB_student].UpdateRow(student.TableInfos[tblvisionrecord],
                                                   student_tblvisionrecord_k00_PrimaryKey_Value,
                                                   values);
}

QMap<QString, QVariant> DatabaseController::Students_tblvisionrecord_GetRowValues()
{
    return dataBaseCommander[DB_student].GetRowValues(student.TableInfos[tblvisionrecord].Name,
                                                      student.TableInfos[tblvisionrecord].PrimaryKeyName,
                                                      student_tblvisionrecord_k00_PrimaryKey_Value);
}

void DatabaseController::Disconnection()
{
    QStringList databaseOpened = QSqlDatabase::connectionNames();
    foreach(QString database, databaseOpened)
    {
        QSqlDatabase::removeDatabase(database);
    }
}
