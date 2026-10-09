#ifndef IOTSDK_H
#define IOTSDK_H

#include <QObject>
#include <QCryptographicHash>
#include <network/tcpwork.h>
#include <fjson/fjson.h>
#include <QEventLoop>
#include <QUrl>
#include <QNetworkReply>
#include <QSslSocket>
class iotSDK: public QObject
{
    Q_OBJECT
public:
    iotSDK();
    QTcpSocket *Iot=new QTcpSocket(this);
    void init(QByteArray deviceSN,
              QByteArray productSN,
              QByteArray projectId,
              QByteArray publicKey,
              QByteArray region,
              QByteArray key, QByteArray url);

    QByteArray DeviceSN;
    QByteArray ProductSN;
    QByteArray ProjectId;
    QByteArray PublicKey;
    QByteArray Region;
    QByteArray Key;
    QByteArray Signature;

    QByteArray Action(QByteArray action,
                   QByteArray Property = "",
                   QByteArray MessageContent = "",
                   QByteArray TopicFullName = "",
                   QByteArray deviceSN = "",
                   QByteArray productSN = "");


    QString httpPageReady();
    QUrl Url;
    QNetworkAccessManager* pManager = new QNetworkAccessManager(this);
    QNetworkRequest Request;
};

#endif // IOTSDK_H
