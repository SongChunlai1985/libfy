#ifndef TCPWORK_H
#define TCPWORK_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <sys/types.h>
#include <QObject>
#include <QThread>
#include <QJsonObject>
#include <fjson/fjson.h>
#include <QDateTime>

enum FyTcpDebugType
{
    DebugUseTcpOff,
    DebugUseTcpON
};
enum FyConnectionState
{
    TcpNotConnect,
    TcpConnectting,
    TcpConnected
};
class tcpwork : public QObject
{
    Q_OBJECT
public:
    QList<QTcpSocket*> tcpskts;
    QTcpSocket *tcpsender = new QTcpSocket(this);             //TcpClientSocket
    QTcpSocket *tcpskt = new QTcpSocket(this);                //TcpServerSocket
    QTcpServer *tcpsvr = new QTcpServer(this);                //TcpServer
    QTcpSocket *tcpdbg = new QTcpSocket(this);                //TcpServerSocket
    tcpwork();
    void tsend(QByteArray msg);               //TcpClient
    void tssend(QByteArray msg);              //TcpServer
    void listen(ushort tcpport);
    void init();
    QString name;
    ushort TcpDbgPort=12348;
    void dbg(QString msg);
    int Debug = DebugUseTcpON;
    void Connected();
    int connected = TcpNotConnect;
    int messageNumber = 0;

    QByteArray messageUnsend;
    void Disconnected();
    void error(QAbstractSocket::SocketError);
};

#endif // TCPWORK_H
