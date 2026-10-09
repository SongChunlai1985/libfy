#ifndef FCV_H
#define FCV_H

#include <opencv.hpp>
#include <QDebug>
#include <base64/base64.h>
#include <base/base.h>
#include <QPixmap>
#ifdef WIN32
#include "qrencode/qrencode.h"
#else
#include </home/song/android/android-ndk-r14b/platforms/android-19/arch-arm/usr/include/qrencode.h>   //不这么写会报安卓版本符号方面的错误
#endif
typedef cv::Point2d p2d;

class fcv : public QObject
{
    Q_OBJECT
private:

    int cl=0;
public:
    fcv();
    ~fcv();

    cv::Mat m = cv::Mat(300, 300, CV_8UC4, cv::Scalar(255,255,255));
    QImage m7;                                                     //不能直接使用cv::Mat 可能是硬件资源有限
    QImage m70;
    QImage m71;
    QImage m72;
    QImage m73;
    QImage m74;
    QImage m75;
    QImage m76;

    QImage tm7;
    QImage tm70;
    QImage tm71;
    QImage tm72;
    QImage tm73;
    QImage tm74;
    QImage tm75;
    QImage tm76;

    void FillRectangle(std::vector<cv::Point> p);
    void drawE0(int x, int y, int s, int d, int cl_=0);
    QString drawE2(double GirdSize, int Direction, int totalsymbol = 4);
    QString drawE1(double gsize, int &np);

    const QString cvMat2dataimage(cv::Mat &m);
    cv::Mat cvtcolor(cv::Mat t,int code);
    QString QmlLoadimage(QString imgpath);
    int makeqr(QString qr, QString &qrimg);
    QImage Loadimage(QString imgpath);
    void init();
};
#endif // FCV_H
