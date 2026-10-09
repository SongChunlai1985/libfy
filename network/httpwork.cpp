#include "httpwork.h"

httpwork::httpwork()
{

}

QString httpwork::getkey(){
    QByteArray array(mkjson());
    QNetworkRequest request(QUrl("http://113.31.119.15:5000/api/tokens"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    QByteArray br=QString("Bearer "+QByteArray(QString("song:AcFb3U").toUtf8()).toBase64()).toUtf8();
    request.setRawHeader("Authorization",br);               //服务器要求的数据头部
    qDebug()<<__FUNCTION__<<"Authoriz "<<br;
    QNetworkAccessManager oNetAccessManager;
    QNetworkReply* oNetReply = nullptr;
    oNetReply = oNetAccessManager.post(request, array);

    QEventLoop loop;
    connect(oNetReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QNetworkReply::NetworkError e = oNetReply->error();
    qDebug()<<__FUNCTION__<<"e:"<<e;
    QString reply=oNetReply->readAll();
    qDebug()<<__FUNCTION__<<"reply:"<<reply;
    qDebug()<<__FUNCTION__<<"errorString:"<<oNetReply->errorString();
    QJsonObject auth=String2JsonObject(reply);
    QString token;
    if (auth.contains("token")) {
        QJsonValue value = auth.value("token");
        if (value.isString()) {
            token = value.toString();
            qDebug()<<__FUNCTION__<<"token:" << token;
        }
    }
    return token;
}

int httpwork::SendAndGetText(QString strUrl, int thod, QString strInput, QString &strMessage,
                             QString &strResult ,QString pkey){
    QUrl url(strUrl);
    QByteArray array(strInput.toUtf8());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("Authorization",QString("Bearer "+pkey).toUtf8());               //服务器要求的数据头部

    QNetworkAccessManager oNetAccessManager;
    QNetworkReply* oNetReply = nullptr;
    if (thod == PUT ) oNetReply = oNetAccessManager.put(request, array);
    if (thod == POST) oNetReply = oNetAccessManager.post(request, array);
    if (thod == GET ) oNetReply = oNetAccessManager.get(request);

    //dbg("enter loop");
    QEventLoop loop;
    connect(oNetReply, SIGNAL(finished()), &loop, SLOT(quit()));
    //dbg("loop");
    loop.exec();
    //dbg("exit loop");

    int httpsCode = oNetReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    QNetworkReply::NetworkError e = oNetReply->error();
    strResult = oNetReply->readAll();
    if (e){
        strMessage = oNetReply->errorString();
        return 0;
    }else{
        qDebug()<<__FUNCTION__+QString("httpCode:")+QString::number(httpsCode);
        return 1;
    }
}
