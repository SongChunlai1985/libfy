#ifndef MW_H
#define MW_H
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>
#include <QObject>
class mw : public QObject
{
    Q_OBJECT
public:
    QUdpSocket *rcv =new QUdpSocket();
    mw();
    void frcv();
};

#endif // MW_H
