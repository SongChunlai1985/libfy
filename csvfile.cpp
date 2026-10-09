#include "csvfile.h"

csvfile::csvfile()
{

}

int csvfile::init(QString filename_)
{
    filename = filename_;
    file = new QFile(filename_);
    workflag = "init";
    codec = QTextCodec::codecForName("GBK");
    return 1;
}

int csvfile::readcsv()
{
    workflag = "reading";
    file->open(QIODevice::ReadOnly);

    qDebug()<<__FUNCTION__<<file->isOpen() << file->atEnd() << file->canReadLine();
    table.clear();

    while(!file->atEnd()){
        QByteArray readline = file->readLine();

        if(readline.right(1).data()[0] == 10)readline = readline.left(readline.length()-1);     //  去掉\n或\r或\r\n或\n\r 适应不同格式的csv文件
        if(readline.right(1).data()[0] == 13)readline = readline.left(readline.length()-1);
        if(readline.right(1).data()[0] == 10)readline = readline.left(readline.length()-1);

        QList<QByteArray> cells = readline.split(',');
        QVariantList row;
        foreach (QByteArray cell, cells) {
            row.push_back(codec->toUnicode(cell));
        }
        table.push_back(row);
        qDebug()<<__FUNCTION__<<row;
    }
    if (table.empty()) return 0;
    workflag = "read complate";
    file->close();
    return table.size();
}

int csvfile::maketable(QString schoolName, QString schoolId, QString schoolUid, QJsonArray classList, QJsonArray studentList)
{
    table.clear() ;
    int i = 0;
    foreach (QJsonValue classstudent, studentList) {
        QJsonArray Objclassstudent = classstudent.toArray();
        QVariantList row;
        QJsonObject Objclass = classList[i].toObject();
        i++;
        foreach (QJsonValue student, Objclassstudent) {
            row.push_back("");
            row.push_back(schoolName);
            row.push_back("");
            QJsonObject Objstudent = student.toObject();
            row.push_back(Objstudent["studentName"].toVariant());

            row.push_back("");
            row.push_back("身份证");
            row.push_back("");
            row.push_back(Objstudent["gender"].toVariant());
            row.push_back("");

            row.push_back("");
            row.push_back("");
            row.push_back(Objclass["grade"].toVariant());
            row.push_back(Objclass["className"].toVariant());
            row.push_back("");

            for (int j = 14; j < 72; ++j) {
                row.push_back("");
            }

            row.push_back(schoolId);
            row.push_back(schoolUid);
            row.push_back(Objclass["id"].toVariant());
            row.push_back(Objclass["uid"].toVariant());
            row.push_back(Objstudent["id"].toVariant());
            row.push_back(Objstudent["uid"].toVariant());
            row.push_back("");
            row.push_back("");
            row.push_back(Objstudent["birthday"].toVariant());

            table.push_back(row);
            row.clear();
        }
    }

    return 0;
}

QJsonObject csvfile::getJson(QStringList keys)
{
    QJsonObject tableJson;
    QJsonArray rows;
    foreach (QVariantList row, table) {
        for (int i = row.size(); i < keys.size(); i++) {
            row.push_back("");
        }
        QJsonObject ObjRow;
        int i = 0;
        foreach (QVariant key, keys) {
            ObjRow.insert(key.toString(), row[i++].toJsonValue());
        }
        rows.push_back(ObjRow);
    }
    tableJson.insert("length",rows.size());
    tableJson.insert("items",rows);
    return tableJson;
}

int csvfile::writecsv(QString Title, QVariantList ColNames)
{
    qDebug() <<"文件打开: "<< file->open(QIODevice::WriteOnly);
    workflag = "writing";

    if(!file->isOpen())
    {
        return -1;
    }

    QByteArray file_table;
    file_table.push_back(codec->fromUnicode(Title));
    for (int i = 1; i < ColNames.size(); i++)
    {
        file_table.push_back(",");
    }
    file_table.push_back('\n');
    for (int i = 1; i < ColNames.size(); i++)
    {
        file_table.push_back(codec->fromUnicode(ColNames[i].toString()));
        file_table.push_back(",");
    }
    file_table.push_back('\n');
    foreach (QVariantList row, table) {
        foreach (QVariant cell, row) {
            file_table.push_back(codec->fromUnicode(cell.toString()));
            file_table.push_back(",");
        }
        file_table.push_back('\n');
    }
    workflag = "write complate";
    qDebug() <<"写入字节数: "<< file->write(file_table) ;
    file->close();
    return 1 ;
}

void csvfile::putJson(QJsonObject DataJson , int DropRow){
    QJsonArray DataJsonArray = DataJson["items"].toArray();
    if(DataJsonArray.size() == 0) return ;
    table.clear() ;
    foreach (QJsonValue JsonRow, DataJsonArray) {
        QJsonObject ObjRow = JsonRow.toObject();
        QVariantList row ;
        int i = 0;
        foreach (QJsonValue Cell, ObjRow) {
            if(i++ != DropRow)row.push_back(Cell.toString());
        }
        table.push_back(row);
    }
}

QList<QVariantList> csvfile::tableGbk()
{
    QList<QVariantList> tableGBK;
    foreach (QVariantList row, table) {
        QVariantList rowGBK;
        foreach (QVariant cell, row) {
            rowGBK.push_back(codec->fromUnicode(cell.toString()));
        }
        tableGBK.push_back(rowGBK);
    }
    return tableGBK;
}

QString csvfile::conv10_26(int n10)
{
    QString str = "";
    while(n10 > 0){
        int m = n10 % 26;
        m = m == 0 ? 26 : m;
        str = char (m + 64) + str;
        n10 = (n10 - m) / 26;
    }
    return str;
}

QString csvfile::autoKey(int i)
{
    return "k__" + QString("%1").arg( i, 4, 10, QLatin1Char('0')) + "_" + conv10_26(i + 1);
}

QStringList csvfile::autoKeys(int total)
{
    QStringList keys;
    for (int i = 0; i < total; i++) {
        keys.push_back(autoKey(i));
    }
    return keys;
}
