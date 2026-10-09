#include "tcpwork.h"
#include <QTextCodec>
#include <QEventLoop>

tcpwork::tcpwork()
{
    connect(tcpdbg, &QTcpSocket::connected, this, &tcpwork::Connected);
    connect(tcpdbg, &QTcpSocket::disconnected, this, &tcpwork::Disconnected);
    connect(tcpdbg, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &tcpwork::error);
}

void tcpwork::listen(ushort tcpport)
{
    tcpsvr->listen(QHostAddress::Any,tcpport);
}

void tcpwork::init()
{
    for(int i = 0;i < 10; i++){
        QTcpSocket *tcpskt=new QTcpSocket(this);
        tcpskts.push_back(tcpskt);
    }

}

void tcpwork::tsend(QByteArray msg)
{
    qint64 writebyte = tcpsender->write(msg+'\0');
    qDebug().noquote()<<__FUNCTION__<< msg << writebyte;
}

void tcpwork::tssend(QByteArray msg)
{
    tcpskt->write(msg+'\0');
}

void tcpwork::Connected()
{
    connected = TcpConnected;
    qDebug()<< name << ": 调试器已经连接";
}

void tcpwork::Disconnected()
{
    connected = TcpNotConnect;
    qDebug()<< name << ": 调试器已经断开";
}

void tcpwork::error(QAbstractSocket::SocketError)
{
    connected = TcpNotConnect;
    qDebug()<< name << ": 调试器连接错误";
}


void tcpwork::dbg(QString msg)                                  //socat tcp4-listen:12348 -
{
#ifdef FyTcpDebug
    if(Debug)
    {
        if(msg=="")return;

        msg = QDateTime::currentDateTime().toString("hh:mm:ss.zzz") + " (" + QString::number(messageNumber++) + ")>> " + msg;
        QByteArray msgb = msg.toLatin1();
        QByteArray mynameb= name.toLatin1();

#ifdef FyTcpDebugGBK
        msgb.replace("\n","\r\n");
        QTextCodec *codec;
        codec = QTextCodec::codecForName("GB2312");
        msgb = codec->fromUnicode(msg) + "\r\n";                //从Unicode转成GB2312 供SSCOM显示
        mynameb = codec->fromUnicode(name);
#endif
        QByteArray message = mynameb +  ": " + msgb + "\r\n";
        if(connected == TcpConnected)
        {
            tcpdbg->write(messageUnsend + message);
            messageUnsend = "";
            return;
        }
        messageUnsend += message;
        if(messageUnsend.size() > 20000)
        {
            messageUnsend = "";
        }
        if(connected == TcpNotConnect)
        {
            tcpdbg->connectToHost(QHostAddress("192.168.11.16"), TcpDbgPort);
            qDebug()<< name <<": 发起调试器连接";
            connected = TcpConnectting;
        }
    }
#endif
}

