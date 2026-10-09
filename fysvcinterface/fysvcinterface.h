#ifndef FYSVCINTERFACE_H
#define FYSVCINTERFACE_H
#include <QString>
#include <fjson/fjson.h>
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>

class fySvcInterface: public QObject{
    Q_OBJECT
public:
    fySvcInterface();
    QString TokenFySVC;
    QString loginFySVC(QString url, QString username, QString password);
    QString logined = "未登录";
    QString logoutFySVC(QString url);
    QString uploadFySVC(QString url, QString record_json);

};

#endif // FYSVCINTERFACE_H
