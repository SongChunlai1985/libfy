#ifndef CAMERAFILTER_H
#define CAMERAFILTER_H
/*如果使用Qzxing请不要挂载此库 会使Qzxing起不来 可能是符号重名导致冲突*/
#include <QVideoFilterRunnable>
#include <QDebug>
#include <opencv.hpp>
#include <zbar.h>
#include <QThread>
#include <base64/base64.h>
#include <unistd.h>

class CameraFilter : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    CameraFilter();
    ~CameraFilter();
    QVideoFilterRunnable *createFilterRunnable();
    Q_INVOKABLE QString getcvm();
    QString qrimgstr;
    int QrImgWidth = 256;                    //决定扫描精度和速度

private:

signals:
    void finished(QObject *result);
    void cameraFrameSignal(QVideoFrame);
    void qrcode(QString qr,QString cvm4);

public slots:

};

class CameraFilterRunnable : public QVideoFilterRunnable
{
public:
    CameraFilterRunnable(CameraFilter* filter = nullptr);
    ~CameraFilterRunnable();
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);

    CameraFilter *m_filter;

private:

    QVideoFrame cloneFrame;
    QString qrc;
    long tms;

    cv::Mat cvm4,cvm1;
    zbar::ImageScanner scanner;
    zbar::Image::SymbolIterator symbol;
};

#endif // CAMERAFILTER_H
