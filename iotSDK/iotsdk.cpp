#include "iotsdk.h"

iotSDK::iotSDK()
{

}

void iotSDK::init(QByteArray deviceSN,
                  QByteArray productSN,
                  QByteArray projectId,
                  QByteArray publicKey,
                  QByteArray region,
                  QByteArray key,
                  QByteArray url)

{
    DeviceSN  = deviceSN;
    ProductSN = productSN;
    ProjectId = projectId;
    PublicKey = publicKey;
    Region    = region;
    Key       = key;
    Url       = QUrl(url);

    QSslConfiguration conf = Request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1_2);
    Request.setSslConfiguration(conf);
    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

QByteArray iotSDK::Action(QByteArray action,
                       QByteArray Property,
                       QByteArray MessageContent,
                       QByteArray TopicFullName,
                       QByteArray deviceSN,
                       QByteArray productSN)
{

    if(deviceSN .size())DeviceSN  = deviceSN;
    if(productSN.size())ProductSN = productSN;

    Signature = "Action" + action +
            "DeviceSN" + DeviceSN +
            (MessageContent.size() ? "MessageContent" + MessageContent : "") +
            "ProductSN" + ProductSN +
            "ProjectId" + ProjectId +
            (Property.size() ? "Property" + Property : "") +
            "PublicKey" + PublicKey +
            "Region" + Region +
            (TopicFullName.size() ? "TopicFullName" + TopicFullName : "") +
            Key;

    //qDebug()<<__FUNCTION__<<"Signature"<<Signature;
    QByteArray SignatureSha =  QCryptographicHash::hash(Signature, QCryptographicHash::Sha1);
    //qDebug()<<__FUNCTION__<<"SignatureSha"<<SignatureSha.toHex();
    //qDebug()<<__FUNCTION__<<"Device supports OpenSSL: "<<QSslSocket::supportsSsl();

    QJsonObject ActionJson;
    ActionJson.insert("Action"   , QString(action));
    ActionJson.insert("Signature", QString(SignatureSha.toHex()));
    ActionJson.insert("ProjectId", QString(ProjectId));
    ActionJson.insert("PublicKey", QString(PublicKey));                //公共参数

    ActionJson.insert("Region"   , QString(Region));
    ActionJson.insert("ProductSN", QString(ProductSN));
    ActionJson.insert("DeviceSN" , QString(DeviceSN));
    if(MessageContent.size())ActionJson.insert("MessageContent" , QString(MessageContent));
    if(TopicFullName.size())ActionJson.insert("TopicFullName" , QString(TopicFullName));

    if(Property.size())ActionJson.insert("Property"   , QString(Property));


    QByteArray BytePost = JsonObject2ByteArray(ActionJson);
    QEventLoop loop;
#if 1
    Request.setUrl(Url);                                               //https
    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *pReply = pManager->post(Request, BytePost.data());
    //qDebug()<<__FUNCTION__<<BytePost;
    //qDebug()<<__FUNCTION__<<QString(BytePost).toUtf8();
    //qDebug().noquote()<<__FUNCTION__<<BytePost;

    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(pReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &loop, &QEventLoop::quit);
    loop.exec();
#else
    Iot->abort();                                                      //http
    Iot->connectToHost(Url.host(), u_short(80));

    qDebug()<<__FUNCTION__<<"Url.host"<<Url.host();

    connect(Iot, &QTcpSocket::connected, &loop, &QEventLoop::quit) ;
    loop.exec();

    QString request =
            QString(QString() +
                    "POST " + Url.path() + "?" + Url.query() + " HTTP/1.1\r\n" +
                    "Host: " + Url.host() + "\r\n" +
                    "Connection: keep-alive\r\n" +
                    "User-Agent: Mozilla/5.0\r\n" +
                    "Accept: application/json\r\n" +
                    "Accept-Encoding: identity\r\n" +
                    "Accept-Language: zh-CN,zh;q=0.9\r\n\r\n" +
                    JsonObject2String(ActionJson)
                    );
    Iot->write(request.toUtf8());

    qDebug()<<__FUNCTION__<<"Signature"<<request;

    connect(Iot, &QTcpSocket::readyRead, &loop, &QEventLoop::quit) ;
    loop.exec();

    return httpPageReady();
#endif
    QByteArray Replydata = pReply->readAll();
    //qDebug()<<__FUNCTION__<<Replydata;
    return Replydata;
}


QString iotSDK::httpPageReady()
{
    QByteArray receivemsg = Iot->readAll();
    qDebug().noquote()<<__FUNCTION__<<receivemsg;
    QString rcvmsg(receivemsg);
    QString char13101310  = "\r\n\r\n";
    int startpoint = rcvmsg.indexOf(char13101310) + 4 ;
    QString data = rcvmsg.mid(startpoint);
    return data;
}
