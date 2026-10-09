#include "mw.h"

mw::mw()
{
    connect(rcv,&QUdpSocket::readyRead,this,&mw::frcv);
    quint16 pt=12346;
    rcv->bind(pt);
}

void mw::frcv(){
    QByteArray dg;
    QHostAddress sdr;
    quint16 sdrpt;
    dg.resize(int(rcv->pendingDatagramSize()));
    rcv->readDatagram(dg.data(),dg.size(),&sdr,&sdrpt);
    qDebug()<<sdr.toString()<<":"<<sdrpt<<" "<<dg.data();
}
