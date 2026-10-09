#include "fjson.h"


QByteArray JsonObject2ByteArray(const QJsonObject& jsonObject){
    return QJsonDocument(jsonObject).toJson();
}

QJsonObject ByteArray2JsonObject(QByteArray json){
    return QJsonDocument::fromJson(json.data()).object();
}

QJsonObject String2JsonObject(const QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

QString JsonObject2String(const QJsonObject& jsonObject){
    return QString(QJsonDocument(jsonObject).toJson());
}

QByteArray mkjson(QString arg1, QJsonValue vl1, QString arg2, QJsonValue vl2, QString arg3, QJsonValue vl3,
                  QString arg4, QJsonValue vl4, QString arg5, QJsonValue vl5, QString arg6, QJsonValue vl6,
                  QString arg7, QJsonValue vl7, QString arg8, QJsonValue vl8, QString arg9, QJsonValue vl9,
                  QString arg10, QJsonValue vl10, QString arg11, QJsonValue vl11, QString arg12, QJsonValue vl12,
                  QString arg13, QJsonValue vl13, QString arg14, QJsonValue vl14, QString arg15, QJsonValue vl15,
                  QString arg16, QJsonValue vl16, QString arg17, QJsonValue vl17, QString arg18, QJsonValue vl18,
                  QString arg19, QJsonValue vl19, QString arg20, QJsonValue vl20, QString arg21, QJsonValue vl21)
{
    QJsonObject oSendObject;
    oSendObject.insert(arg1, vl1); oSendObject.insert(arg2, vl2); oSendObject.insert(arg3, vl3);
    oSendObject.insert(arg4, vl4); oSendObject.insert(arg5, vl5); oSendObject.insert(arg6, vl6);
    oSendObject.insert(arg7, vl7); oSendObject.insert(arg8, vl8); oSendObject.insert(arg9, vl9);
    oSendObject.insert(arg10, vl10); oSendObject.insert(arg11, vl11); oSendObject.insert(arg12, vl12);
    oSendObject.insert(arg13, vl13); oSendObject.insert(arg14, vl14); oSendObject.insert(arg15, vl15);
    oSendObject.insert(arg16, vl16); oSendObject.insert(arg17, vl17); oSendObject.insert(arg18, vl18);
    oSendObject.insert(arg19, vl19); oSendObject.insert(arg20, vl20); oSendObject.insert(arg21, vl21);

    oSendObject.remove("");
    return  JsonObject2ByteArray(oSendObject);
}

QJsonObject mkjsonJ(QString arg1, QJsonValue vl1, QString arg2, QJsonValue vl2, QString arg3, QJsonValue vl3,
                  QString arg4, QJsonValue vl4, QString arg5, QJsonValue vl5, QString arg6, QJsonValue vl6,
                  QString arg7, QJsonValue vl7, QString arg8, QJsonValue vl8, QString arg9, QJsonValue vl9,
                  QString arg10, QJsonValue vl10, QString arg11, QJsonValue vl11, QString arg12, QJsonValue vl12,
                  QString arg13, QJsonValue vl13, QString arg14, QJsonValue vl14, QString arg15, QJsonValue vl15,
                  QString arg16, QJsonValue vl16, QString arg17, QJsonValue vl17, QString arg18, QJsonValue vl18,
                  QString arg19, QJsonValue vl19, QString arg20, QJsonValue vl20, QString arg21, QJsonValue vl21)
{
    QJsonObject oSendObject;
    oSendObject.insert(arg1,vl1); oSendObject.insert(arg2,vl2); oSendObject.insert(arg3,vl3);
    oSendObject.insert(arg4,vl4); oSendObject.insert(arg5,vl5); oSendObject.insert(arg6,vl6);
    oSendObject.insert(arg7,vl7); oSendObject.insert(arg8,vl8); oSendObject.insert(arg9,vl9);
    oSendObject.insert(arg10,vl10); oSendObject.insert(arg11,vl11); oSendObject.insert(arg12,vl12);
    oSendObject.insert(arg13,vl13); oSendObject.insert(arg14,vl14); oSendObject.insert(arg15,vl15);
    oSendObject.insert(arg16,vl16); oSendObject.insert(arg17,vl17); oSendObject.insert(arg18,vl18);
    oSendObject.insert(arg19,vl19); oSendObject.insert(arg20,vl20); oSendObject.insert(arg21,vl21);

    oSendObject.remove("");
    return oSendObject;
}

QByteArray shortJson(QByteArray JsonByteArray)
{
    JsonByteArray.replace(char(32),"");
    JsonByteArray.replace(char(13),"");
    JsonByteArray.replace(char(10),"");
    return JsonByteArray;
}

