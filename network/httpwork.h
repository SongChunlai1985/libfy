#ifndef HTTPWORK_H
#define HTTPWORK_H
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <fjson/fjson.h>

class httpwork : public QObject
{
    Q_OBJECT
public:
    int POST=0, GET =1, PUT =2;
    httpwork();
    QString getkey();
    int SendAndGetText(QString strUrl, int thod, QString strInput,
                       QString &strMessage,QString &strResult,QString pkey);

};

#endif // HTTPWORK_H
