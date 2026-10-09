#include "camerafilter.h"

CameraFilter::CameraFilter()
{

}

CameraFilter::~CameraFilter()
{

}

QVideoFilterRunnable *CameraFilter::createFilterRunnable()
{
    return new CameraFilterRunnable(this);
}

QString CameraFilter::getcvm()      //qDebug()<<__FUNCTION__<< qrimgstr;
{
    return qrimgstr;
}

CameraFilterRunnable::CameraFilterRunnable(CameraFilter* filter)
{
    m_filter = filter;
    scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
}

CameraFilterRunnable::~CameraFilterRunnable()
{

}

cv::Mat sbmat(cv::Mat &m,cv::Rect rt){
    int wd=rt.width/2,ht=rt.height/2,
            w=m.cols,h=m.rows;

    rt.width=rt.width>w?w:rt.width;
    rt.height=rt.height>h?h:rt.height;

    rt.x=rt.x>wd?rt.x:wd;
    rt.y=rt.y>ht?rt.y:ht;

    rt.x=rt.x>w-wd?w-wd:rt.x;
    rt.y=rt.y>h-ht?h-ht:rt.y;

    rt.x=rt.x-wd;rt.y=rt.y-wd;
#if 0
    printf("< %d,%d,%d,%d >",rt.x,rt.y,rt.width,rt.height);
#endif
    return cv::Mat(m,rt);
}

QVideoFrame CameraFilterRunnable::run(QVideoFrame *input,
                                      const QVideoSurfaceFormat &surfaceFormat,
                                      RunFlags flags)
{
    if(0)qDebug()<<__FUNCTION__<<surfaceFormat.frameRate()<<flags;
    tms++;
    cloneFrame = *input;
    if(!cloneFrame.map(QAbstractVideoBuffer::ReadOnly) /*|| tms%1!=0 降压防崩*/)
    {
        //emit m_filter->cameraFrameSignal(cloneFrame);
        return *input;
    }
    int ewd = cloneFrame.width(),eht = cloneFrame.height();
    cvm4 = cv::Mat(eht, ewd, CV_8UC4, cloneFrame.bits(), cloneFrame.bytesPerLine());

    if(cvm4.cols!=ewd || cvm4.rows != eht || cvm4.channels() != 4 || cvm4.empty())      //emit m_filter->cameraFrameSignal(cloneFrame);
    {
        qDebug()<<"return2";
        return *input;
    }

    cv::cvtColor(cvm4, cvm1, cv::COLOR_BGRA2GRAY);                                      //m_filter->qrimgstr = cvMat2dataimgae(cvm1);                           //cv::circle(cvm1,cv::Point(100,100),200,cv::Scalar(0),3);     //qDebug()<<"cvm1"<<cvm1.cols<<cvm1.rows<<cvm1.channels()<<cvm1.data<<tms;

    int newWidth = ewd > eht ? ewd * 0.6 : eht *0.6;
    if(newWidth > ewd)newWidth = ewd;
    if(newWidth > eht)newWidth = eht;
    cvm1 = sbmat(cvm1,cv::Rect(cv::Point(ewd / 2 ,eht / 2),cv::Size(newWidth , newWidth)));
    newWidth = m_filter->QrImgWidth;
    cv::resize(cvm1,cvm1,cv::Size(newWidth,newWidth));
    cv::flip(cvm1,cvm1,0);
    ulong datalong = ulong(newWidth * newWidth);                                        //cv::Mat cvm2=cvm1.clone();   //zbimg.set_data(cvm2.data,ulong(ewd*eht));
    zbar::Image zbimg=zbar::Image(uint(newWidth)/*uint 不能被忽略*/ , uint(newWidth)/*uint 不能被忽略*/,
                                  std::string("Y800"), cvm1.data, datalong);            //scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    if(scanner.scan(zbimg)){                                                            //必须判断 否则会发生闪退
        symbol=zbimg.symbol_begin();
        int n=0;
        for(;symbol != zbimg.symbol_end();++symbol){
            n++;
            qrc=QString::fromStdString(symbol->get_data());                             //emit m_filter->cameraFrameSignal(cloneFrame);
            emit m_filter->qrcode(qrc,"");
        }
    }                                                                                   //qDebug()<<"zbimg:"<<zbimg.get_width()<<zbimg.get_height()<<zbimg.get_data_length()<<tms;
    qrc="";
    return *input;
}
