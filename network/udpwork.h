#ifndef UDPWORK_H
#define UDPWORK_H

#include <QtNetwork/QUdpSocket>
#include <sys/types.h>
#include <QObject>
#include <QTextCodec>

enum FyUdpDebugType
{
    DebugOff,
    DebugON
};

class udpwork : public QObject
{
    Q_OBJECT
public:
    udpwork();
    void send(QByteArray msg,QHostAddress pIP,u_short Port);
    void send(QByteArray msg);
    void dbg(QString msg);
    u_short PORT=12345;
    u_short udpdbgport=12346;
    u_short udpprport=12347;
    QString UIp,myname;
    QUdpSocket *udpsnd =new QUdpSocket(this);
    QUdpSocket *udpprrcv =new QUdpSocket(this);
    QUdpSocket *udprcv =new QUdpSocket(this);
    int Debug = DebugON;

private:

};

#endif // UDPWORK_H
