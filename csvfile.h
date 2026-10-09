#ifndef CSVFILE_H
#define CSVFILE_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>

class csvfile : public QObject
{
    Q_OBJECT
public:
    csvfile();
    QString filename;
    QFile *file;
    QList<QVariantList> table;

    QString workflag;
    QTextCodec *codec;

    int init(QString filename_);
    int readcsv();

    int writecsv(QString Title, QVariantList ColName);

    QJsonObject getJson(QStringList keys);

    void putJson(QJsonObject DataJson, int DropRow = -1);
    QList<QVariantList> tableGbk();
    QStringList autoKeys(int total);
    QString conv10_26(int n10);
    QString autoKey(int i);
    int maketable(QString schoolName, QString schoolId, QString schoolUid, QJsonArray classList, QJsonArray studentList);
};

#endif // CSVFILE_H
