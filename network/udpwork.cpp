#include "udpwork.h"

udpwork::udpwork()
{
    udpprrcv->bind(udpprport);
}

void udpwork::send(QByteArray msg,QHostAddress pIP,u_short Port){
    udpsnd->writeDatagram(msg,pIP,Port);
}

void udpwork::send(QByteArray msg){
    send(msg,QHostAddress(UIp),PORT);
}

void udpwork::dbg(QString msg){      //socat - udp4-listen:12345
    if(msg=="")return;
    QByteArray msgb = msg.toLatin1();
    QByteArray mynameb= myname.toLatin1();
#ifdef FyTcpDebug
#ifdef FyTcpDebugGBK
    msgb.replace("\n","\r\n");
    QTextCodec *codec;
    codec = QTextCodec::codecForName("GB2312");
    msgb = codec->fromUnicode(msg) + "\r\n";                //从Unicode转成GB2312 供SSCOM显示
    mynameb = codec->fromUnicode(myname);
#endif
    if(Debug)send( mynameb +  ": " + msgb,
                  QHostAddress("192.168.11.61"), udpdbgport);
#else
    qDebug().noquote()<<__FUNCTION__<<msg;
#endif
}
