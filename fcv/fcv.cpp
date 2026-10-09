#include "fcv.h"

fcv::fcv(){

}

fcv::~fcv(){

}

void fcv::init()
{
#ifdef WIN32
    m70 = Loadimage("C:/code/fyvisioncheck/android/assets/0.png");
    m71 = Loadimage("C:/code/fyvisioncheck/android/assets/1.png");
    m72 = Loadimage("C:/code/fyvisioncheck/android/assets/2.png");
    m73 = Loadimage("C:/code/fyvisioncheck/android/assets/3.png");
    m74 = Loadimage("C:/code/fyvisioncheck/android/assets/4.png");
    m75 = Loadimage("C:/code/fyvisioncheck/android/assets/5.png");
    m76 = Loadimage("C:/code/fyvisioncheck/android/assets/6.png");

    tm70 = Loadimage("C:/code/fyvisioncheck/android/assets/t0.png");
    tm71 = Loadimage("C:/code/fyvisioncheck/android/assets/t1.png");
    tm72 = Loadimage("C:/code/fyvisioncheck/android/assets/t2.png");
    tm73 = Loadimage("C:/code/fyvisioncheck/android/assets/t3.png");
    tm74 = Loadimage("C:/code/fyvisioncheck/android/assets/t4.png");
    tm75 = Loadimage("C:/code/fyvisioncheck/android/assets/t5.png");
    tm76 = Loadimage("C:/code/fyvisioncheck/android/assets/t6.png");
#else
    m70 = Loadimage("assets:/0.png");
    m71 = Loadimage("assets:/1.png");
    m72 = Loadimage("assets:/2.png");
    m73 = Loadimage("assets:/3.png");
    m74 = Loadimage("assets:/4.png");
    m75 = Loadimage("assets:/5.png");
    m76 = Loadimage("assets:/6.png");

    tm70 = Loadimage("assets:/t0.png");
    tm71 = Loadimage("assets:/t1.png");
    tm72 = Loadimage("assets:/t2.png");
    tm73 = Loadimage("assets:/t3.png");
    tm74 = Loadimage("assets:/t4.png");
    tm75 = Loadimage("assets:/t5.png");
    tm76 = Loadimage("assets:/t6.png");
#endif
}

void fcv::FillRectangle(std::vector<cv::Point> p)
{
    if(!(in(p[0].x, 0, m.cols) && in(p[0].y, 0, m.rows) &&
         in(p[1].x, 0, m.cols) && in(p[1].y, 0, m.rows)))return;
    for(int u = p[0].x; u < p[1].x; u++)
    {
        for(int v = p[0].y; v<p[1].y; v++)
        {
            m.at<cv::Vec4b>(p2d(u, v)) = cv::Vec4b(uchar(cl), uchar(cl), uchar(cl), 255);
        }
    }
}

void fcv::drawE0(int x, int y, int s_, int d, int cl_)
{
    int g = s_/5;
    cl = cl_;
    m.setTo(cv::Scalar(255,255,255));
    cv::Point   o(x,y),
            s(g,g),
            lu(o+-s*2.5);
    std::vector<cv::Point>p;
    if(d==0 || d==1){
        p.clear();
        p.push_back(lu+cv::Point(  0,  0));
        p.push_back(lu+cv::Point(5*g,  g));
        FillRectangle(p);

        p.clear();
        p.push_back(lu+cv::Point(  0,2*g));
        p.push_back(lu+cv::Point(5*g,3*g));
        FillRectangle(p);

        p.clear();
        p.push_back(lu+cv::Point(  0,4*g));
        p.push_back(lu+cv::Point(5*g,5*g));
        FillRectangle(p);
    }

    if(d==0){
        p.clear();
        p.push_back(lu+cv::Point(4*g,  0));
        p.push_back(lu+cv::Point(5*g,5*g));
        FillRectangle(p);
    }

    if(d==1){
        p.clear();
        p.push_back(lu+cv::Point(0*g,  0));
        p.push_back(lu+cv::Point(1*g,5*g));
        FillRectangle(p);
    }

    if(d==2 || d==3){

        p.clear();
        p.push_back(lu+cv::Point(0*g,  0));
        p.push_back(lu+cv::Point(1*g,5*g));
        FillRectangle(p);

        p.clear();
        p.push_back(lu+cv::Point(2*g,  0));
        p.push_back(lu+cv::Point(3*g,5*g));
        FillRectangle(p);

        p.clear();
        p.push_back(lu+cv::Point(4*g,  0));
        p.push_back(lu+cv::Point(5*g,5*g));
        FillRectangle(p);
    }

    if(d==2){
        p.clear();
        p.push_back(lu+cv::Point(  0,4*g));
        p.push_back(lu+cv::Point(5*g,5*g));
        FillRectangle(p);
    }

    if(d==3){
        p.clear();
        p.push_back(lu+cv::Point(  0,  0));
        p.push_back(lu+cv::Point(5*g,  g));
        FillRectangle(p);
    }
}

QString fcv::drawE2(double GirdSize, int Direction, int totalsymbol)
{
    cv::Mat m2, m3, m4;
    int szg = int(GirdSize * 5.0);
    cv::Size sz(szg, szg);
    if(totalsymbol == 4)
    {
        cv::resize(m, m2, sz, 150, 150, cv::INTER_NEAREST);
        if(Direction == 0)
        {
            m4 = m2;
        }
        if(Direction == 1)
        {
            cv::flip(m2, m4, 1);
        }
        if(Direction == 2)
        {
            cv::transpose(m2, m4);
        }
        if(Direction == 3)
        {
            cv::flip(m2, m3, 1);
            cv::transpose(m3, m4);
        }
    }

    if(totalsymbol == 7)
    {
        if(cl == 0)
        {
            if(Direction == 0)
            {
                m2 = cv::Mat(tm70.height(), m70.width(), CV_8UC4, tm70.bits(), size_t(tm70.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 1)
            {
                m2 = cv::Mat(tm71.height(), tm71.width(), CV_8UC4, tm71.bits(), size_t(tm71.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 2)
            {
                m2 = cv::Mat(tm72.height(), tm72.width(), CV_8UC4, tm72.bits(), size_t(tm72.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 3)
            {
                m2 = cv::Mat(tm73.height(), tm73.width(), CV_8UC4, tm73.bits(), size_t(tm73.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 4)
            {
                m2 = cv::Mat(tm74.height(), tm74.width(), CV_8UC4, tm74.bits(), size_t(tm74.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 5)
            {
                m2 = cv::Mat(tm75.height(), tm75.width(), CV_8UC4, tm75.bits(), size_t(tm75.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 6)
            {
                m2 = cv::Mat(tm76.height(), tm76.width(), CV_8UC4, tm76.bits(), size_t(tm76.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
        }
        else
        {
            if(Direction == 0)
            {
                m2 = cv::Mat(m70.height(), m70.width(), CV_8UC4, m70.bits(), size_t(m70.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 1)
            {
                m2 = cv::Mat(m71.height(), m71.width(), CV_8UC4, m71.bits(), size_t(m71.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 2)
            {
                m2 = cv::Mat(m72.height(), m72.width(), CV_8UC4, m72.bits(), size_t(m72.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 3)
            {
                m2 = cv::Mat(m73.height(), m73.width(), CV_8UC4, m73.bits(), size_t(m73.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 4)
            {
                m2 = cv::Mat(m74.height(), m74.width(), CV_8UC4, m74.bits(), size_t(m74.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 5)
            {
                m2 = cv::Mat(m75.height(), m75.width(), CV_8UC4, m75.bits(), size_t(m75.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
            if(Direction == 6)
            {
                m2 = cv::Mat(m76.height(), m76.width(), CV_8UC4, m76.bits(), size_t(m76.bytesPerLine()));
                cv::resize(m2, m4, sz, 150, 150, cv::INTER_LINEAR_EXACT);
            }
        }

    }

    if(!m4.empty())
    {
        return cvMat2dataimage(m4);
    }
    else
    {
        return "";
    }
}

QString fcv::drawE1(double gsize,int &np)
{
    int npn = rnd(4);
    if(npn == np){
        if(npn == 0)npn = 3;
        else if(npn == 1)npn = 2;
        else if(npn == 2)npn = 1;
        else if(npn == 3)npn = 0;
    }
    np = npn;
    return drawE2(gsize, np);
}

const QString fcv::cvMat2dataimage(cv::Mat &m)
{
    std::string encoded_png;
    std::vector<uchar> buf;
    cv::imencode(".tiff", m, buf);                               //qDebug()<<__FUNCTION__<<m.cols<<" "<<m.rows;
    const byte* base64_png = reinterpret_cast<const unsigned char*>(buf.data());
    encoded_png = "data:image/tiff;base64," + base64_encode(base64_png, buf.size());
    return QString::fromStdString(encoded_png);
}

cv::Mat fcv::cvtcolor(cv::Mat t,int code)
{
    cv::Mat m1;
    cv::cvtColor(t,m1,code);
    return m1;
}

QString fcv::QmlLoadimage(QString imgpath)
{
    QPixmap mxp;
    mxp.load(imgpath);
    QImage mxi= mxp.toImage();
    cv::Mat mxm = cv::Mat(mxi.height(), mxi.width(),
                          CV_8UC4, mxi.bits(), size_t(mxi.bytesPerLine()));
    return cvMat2dataimage(mxm);
}

QImage fcv::Loadimage(QString imgpath){
    QPixmap mxp;
    mxp.load(imgpath);
    QImage mxi = mxp.toImage();
    qDebug()<<__FUNCTION__<<mxi;
    return mxi;
}


int fcv::makeqr(QString qr,QString &qrimg){
    QRcode *qrcode;
    QByteArray qra;
    qra.append(qr);
    qrcode = QRcode_encodeString(qra.data(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
    qDebug()<<__FUNCTION__<<" version:"<<qrcode->version<<" width:"<< qrcode->width <<" size:"<<sizeof(qrcode);
    uchar *dt0 = qrcode->data,
            wd = uchar(qrcode->width);
    QByteArray bts;
    for(uint i=0;i<wd;i++){
        QByteArray btss;
        for(uint i=0;i<wd;i++){
            btss.push_back(!(*dt0 & 1)*255);
            dt0++;
        }
        //qDebug()<<__FUNCTION__<<btss;
        bts.push_back(btss);
    }
    //qDebug()<<__FUNCTION__<<bts;
    cv::Mat m1(wd,wd,CV_8UC1,bts.data());
    cv::Mat m2;
    cv::cvtColor(m1,m2,cv::COLOR_GRAY2BGR);
    cv::resize(m2,m1,cv::Size(220,220),0,0,cv::INTER_NEAREST);
    qrimg=cvMat2dataimage(m1);
    return 1;
}

