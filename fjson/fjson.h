#ifndef FJSON_H
#define FJSON_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

QByteArray JsonObject2ByteArray(const QJsonObject& jsonObject);

QJsonObject ByteArray2JsonObject(QByteArray json);

QJsonObject String2JsonObject(const QString jsonString);

QString JsonObject2String(const QJsonObject& jsonObject);

QByteArray mkjson(QString arg1 = "empty", QJsonValue vl1 = "empty", QString arg2 = "", QJsonValue vl2 = "", QString arg3 = "", QJsonValue vl3 = "",
                  QString arg4 = "", QJsonValue vl4 = "", QString arg5 = "", QJsonValue vl5 = "", QString arg6 = "", QJsonValue vl6 = "",
                  QString arg7 = "", QJsonValue vl7 = "", QString arg8 = "", QJsonValue vl8 = "", QString arg9 = "", QJsonValue vl9 = "",
                  QString arg10 = "", QJsonValue vl10 = "", QString arg11 = "", QJsonValue vl11 = "", QString arg12 = "", QJsonValue vl12 = "",
                  QString arg13 = "", QJsonValue vl13 = "", QString arg14 = "", QJsonValue vl14 = "", QString arg15 = "", QJsonValue vl15 = "",
                  QString arg16 = "", QJsonValue vl16 = "", QString arg17 = "", QJsonValue vl17 = "", QString arg18 = "", QJsonValue vl18 = "",
                  QString arg19 = "", QJsonValue vl19 = "", QString arg20 = "", QJsonValue vl20 = "", QString arg21 = "", QJsonValue vl21 = "");

QJsonObject mkjsonJ(QString arg1 = "empty", QJsonValue vl1 = "empty", QString arg2 = "", QJsonValue vl2 = "", QString arg3 = "", QJsonValue vl3 = "",
                  QString arg4 = "", QJsonValue vl4 = "", QString arg5 = "", QJsonValue vl5 = "", QString arg6 = "", QJsonValue vl6 = "",
                  QString arg7 = "", QJsonValue vl7 = "", QString arg8 = "", QJsonValue vl8 = "", QString arg9 = "", QJsonValue vl9 = "",
                  QString arg10 = "", QJsonValue vl10 = "", QString arg11 = "", QJsonValue vl11 = "", QString arg12 = "", QJsonValue vl12 = "",
                  QString arg13 = "", QJsonValue vl13 = "", QString arg14 = "", QJsonValue vl14 = "", QString arg15 = "", QJsonValue vl15 = "",
                  QString arg16 = "", QJsonValue vl16 = "", QString arg17 = "", QJsonValue vl17 = "", QString arg18 = "", QJsonValue vl18 = "",
                  QString arg19 = "", QJsonValue vl19 = "", QString arg20 = "", QJsonValue vl20 = "", QString arg21 = "", QJsonValue vl21 = "");

QByteArray shortJson(QByteArray JsonByteArray);
#endif // FJSON_H
