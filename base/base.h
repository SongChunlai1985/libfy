#ifndef BASE_H
#define BASE_H
//#include <opencv.hpp>
#include <QString>
#include <QHostAddress>
#include <QNetworkInterface>
#include <iostream>
#include <math.h>

#ifdef ANDROID
#include <QtAndroid>
#endif

#include <QDateTime>
#include <QGuiApplication>
#include <QRect>
#include <QScreen>
#include <QDir>

typedef unsigned char byte;

bool in(double a,double min,double max);
#ifndef HaveFy3d
int rnd(int max,int real=0);
double Tan (double a);
std::vector<std::string> getMyIp();
#endif
double fyDiv(int a, int b);
QByteArray int2byte(int a);

double getScreenDPI();
int byte2int(QByteArray d);
bool checkPermission(const QString &permission);
QString GetCurrentTime(QString format = "yyyy.MM.dd hh:mm:ss ddd" /*"yyyy.MM.dd hh:mm:ss.zzz ddd"*/);
QDateTime toQDateTime(QString DateString);   //不适用于1200年及以前
qint64 getCurrentMSecsSinceEpoch();
#endif // BASE_H
