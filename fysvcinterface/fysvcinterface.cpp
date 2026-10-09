#include "fysvcinterface.h"

fySvcInterface::fySvcInterface()
{

}

QString fySvcInterface::loginFySVC(QString url, QString username, QString password)
{
    username = "test3";
    password = "123123";

    QUrl Url;
    QNetworkRequest Request;
    QNetworkAccessManager* pManager = new QNetworkAccessManager(this);

    QSslConfiguration conf = Request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1_2);
    Request.setSslConfiguration(conf);

    if(username == "" || password == "")return "";
    Url = QUrl(url);

    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QEventLoop loop;
    QByteArray BytePost;

    BytePost.append("account=").append(username).append("&");
    BytePost.append("password=").append(password).append("&");
    BytePost.append("type=").append("account");

    Request.setUrl(Url);

    QNetworkReply *pReply = pManager->post(Request, BytePost.data());

    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(pReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray Replydata = pReply->readAll();
    qDebug().noquote() << __FUNCTION__ << JsonObject2String(ByteArray2JsonObject(Replydata));

    QJsonObject ReplyJson = ByteArray2JsonObject(Replydata);
    TokenFySVC = ReplyJson["token"     ].toString();

    if(TokenFySVC.size())return "OK";
    return "no";
}

QString fySvcInterface::logoutFySVC(QString url)
{
    QUrl Url;
    QNetworkRequest Request;
    QNetworkAccessManager* pManager = new QNetworkAccessManager(this);

    QSslConfiguration conf = Request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1_2);
    Request.setSslConfiguration(conf);

    if(TokenFySVC == "")return "";
    Url = QUrl(url);

    Request.setRawHeader("Authorization", "Token " + TokenFySVC.toLocal8Bit());
    TokenFySVC = "";
    QEventLoop loop;

    Request.setUrl(Url);

    QNetworkReply *pReply = pManager->deleteResource(Request);

    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(pReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray Replydata = pReply->readAll();
    qDebug().noquote() << __FUNCTION__ << JsonObject2String(ByteArray2JsonObject(Replydata));

    QJsonObject ReplyJson = ByteArray2JsonObject(Replydata);
    TokenFySVC = ReplyJson["token"     ].toString();

    if(TokenFySVC.size())return "OK";
    return "no";
}

QString fySvcInterface::uploadFySVC(QString url, QString record_json)
{
    QUrl Url;
    QNetworkRequest Request;
    QNetworkAccessManager* pManager = new QNetworkAccessManager(this);

#if 0                      //https
    QSslConfiguration conf = Request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1_2);
    Request.setSslConfiguration(conf);
#endif

    if(TokenFySVC == "")return "";
    Url = QUrl(url);

    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //Request.setRawHeader("Authorization", "Token " + TokenFySVC.toLocal8Bit());

    Request.setUrl(Url);
    QByteArray BytePost = record_json.toUtf8();

    QNetworkReply *pReply = pManager->post(Request, BytePost.data());

    QEventLoop loop;
    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(pReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray Replydata = pReply->readAll();

    qDebug().noquote() << __FUNCTION__ << Replydata;
    qDebug().noquote() << __FUNCTION__ << JsonObject2String(ByteArray2JsonObject(Replydata));

    QJsonObject ReplyJson = ByteArray2JsonObject(Replydata);
    TokenFySVC = ReplyJson["message"     ].toString();

    if(TokenFySVC == "success")return "OK";
    return "no";
}
