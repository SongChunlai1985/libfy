#include "base.h"

bool in(double a,double min,double max){
    return a >= min && a <= max;
}
#ifndef HaveFy3d
int rnd(int max,int real){
#ifdef Q_OS_ANDROID
    real=0;
    return std::rand()%max;
#else
#ifdef WIN32
    return rand()%max;
#else
    std::uniform_int_distribution<int> ds(0,max);
    std::random_device rd1;                     // uses RDRND or /dev/urandom
    std::random_device rd2("/dev/random");      // much slower on Linux
    if(real){
        return ds(rd1);
    }else{
        return ds(rd2);
    }
#endif
#endif
}
#endif
#ifndef HaveFy3d
double Tan (double a){
    double pi  = 180, agl = pi/3.14159265358979323846;
    return tan (a/agl);
}
#endif

double fyDiv(int a, int b)
{
    if(b == 0)return INT_MAX;
    return a/b;
}

QByteArray int2byte(int a){
    QByteArray b;
    b.resize(4);
    b[0]=byte((0x000000ff & a)      );
    b[1]=byte((0x0000ff00 & a) >> 8 );
    b[2]=byte((0x00ff0000 & a) >> 16);
    b[3]=byte((0xff000000 & a) >> 24);
    return b;
}

int byte2int(QByteArray d){
    int a;
    a  = ((d[0]    ) & 0x000000ff);
    a |= ((d[1]<< 8) & 0x0000ff00);
    a |= ((d[2]<<16) & 0x00ff0000);
    a |= ((d[3]<<24) & 0xff000000);
    return a;
}

#ifndef HaveFy3d
std::vector<std::string> getMyIp(){
    std::vector<std::string> ips;
    QList<QHostAddress> list= QNetworkInterface::allAddresses();
    foreach (QHostAddress ads, list) {
        if(ads.protocol()==QAbstractSocket::IPv4Protocol)
            ips.push_back(ads.toString().toStdString());
    }
    return ips;
}
#endif

double getScreenDPI()
{
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    double devicePixelRatio = QGuiApplication::primaryScreen()->devicePixelRatio();//设备无关像素值与像素的单位比值

    double screenW = screenRect.width();                                           //设备无关像素值宽度。
    double screenH = screenRect.height();                                          //设备无关像素值高度
    double screenResolutionWidth = screenW*devicePixelRatio;                      //手机屏幕真正的像素分辨率宽度
    double screenResolutionheigh = screenH*devicePixelRatio;
    QSizeF physicalSize = QGuiApplication::primaryScreen()->physicalSize();        //手机屏幕物理尺寸，单位:毫米
    double physicalScreenWidthmm= physicalSize.width();                            //手机屏幕英寸宽度
    double dpmm =  screenResolutionWidth / physicalScreenWidthmm;                    //像素宽度除以英寸宽度=像素密度

    qDebug()<<"sW:"+QString::number(screenW)+" "+
              "sH:"+QString::number(screenH)+" "+
              "PR:"+QString::number(devicePixelRatio)+" "+
              "rW:"+QString::number(screenResolutionWidth)+" "+
              "rH:"+QString::number(screenResolutionheigh)+" "+
              "pW:"+QString::number(physicalSize. width())+" "+
              "pH:"+QString::number(physicalSize.height())+" "+
              "dpmm:"+QString::number(dpmm)
              ;
    return dpmm;
}

bool checkPermission(const QString &permission)
{
#ifdef Q_OS_ANDROID
    QtAndroid::PermissionResult r = QtAndroid::checkPermission(permission);
    if(r != QtAndroid::PermissionResult::Granted)
    {
        QtAndroid::requestPermissionsSync( QStringList() << permission );
        r = QtAndroid::checkPermission(permission);
        if(r == QtAndroid::PermissionResult::Denied)
        {
            return false;
        }
    }
#endif
    return true;
}

QString GetCurrentTime(QString format)
{
    return QDateTime::currentDateTime().toString(format);
}

qint64 getCurrentMSecsSinceEpoch()
{
    return QDateTime::currentDateTime().currentMSecsSinceEpoch();
}

QDateTime toQDateTime(QString DateString){
    QDateTime Datetime;
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日hh:mm:ss.zzz");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日hh:mm:ss");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日hh:mm");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日hh");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日 hh:mm:ss");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日 hh:mm");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日 hh");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月dd日");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年MM月");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy年");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy");

    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy.MM.dd hh:mm:ss.zzz");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy.MM.dd hh:mm:ss");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy.MM.dd hh:mm");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy.MM.dd hh");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy.MM.dd");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy.MM");

    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy-MM-dd hh:mm:ss.zzz");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy-MM-dd hh:mm:ss");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy-MM-dd hh:mm");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy-MM-dd hh");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy-MM-dd");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy-MM");

    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy/MM/dd hh:mm:ss.zzz");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy/MM/dd hh:mm:ss");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy/MM/dd hh:mm");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy/MM/dd hh");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy/MM/dd");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyy/MM");

    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyyMMdd hh:mm:ss.zzz");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyyMMdd hh:mm:ss");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyyMMdd hh:mm");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyyMMdd hh");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyyMMdd");
    if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"yyyyMM");

    if(DateString.left(2).toInt() <= 12){
        Datetime = QDateTime::fromString("");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日hh:mm:ss.zzz");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日hh:mm:ss");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日hh:mm");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日hh");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日 hh:mm:ss");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日 hh:mm");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日 hh");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月dd日");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM月");

        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM.dd hh:mm:ss.zzz");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM.dd hh:mm:ss");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM.dd hh:mm");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM.dd hh");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM.dd");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM");

        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM-dd hh:mm:ss.zzz");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM-dd hh:mm:ss");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM-dd hh:mm");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM-dd hh");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM-dd");

        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM/dd hh:mm:ss.zzz");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM/dd hh:mm:ss");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM/dd hh:mm");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM/dd hh");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MM/dd");

        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MMdd hh:mm:ss.zzz");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MMdd hh:mm:ss");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MMdd hh:mm");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MMdd hh");
        if(Datetime.toString("yyyy-MM-dd hh:mm:ss") == "")Datetime = QDateTime::fromString(DateString,"MMdd");

        Datetime = QDateTime::fromString(QDateTime::currentDateTime().toString("yyyy") + Datetime.toString("yyyyMMdd hh:mm:ss.zzz").mid(4),"yyyyMMdd hh:mm:ss.zzz");

    }
    return Datetime;
}


