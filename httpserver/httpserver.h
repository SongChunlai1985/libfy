#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <network/httpwork.h>
#include <network/tcpwork.h>
#include <network/udpwork.h>
#include <QFile>
class httpserver: public QObject{
    Q_OBJECT

signals:
    void httpquerry(int i, QJsonObject JsonPakge);

private:
    void httpRequestArrive(int i);
    void httpRequestArrive0();
    void httpRequestArrive1();
    void httpRequestArrive2();
    void httpRequestArrive3();
    void httpRequestArrive4();
    void httpRequestArrive5();
    void httpRequestArrive6();
    void httpRequestArrive7();
    void httpRequestArrive8();
    void httpRequestArrive9();

public:
    httpserver();
    tcpwork httpServer;
    void httpInitConnect();
    void httpdisconnected();
    u_short httpport = 8080;
    void init();

    void httpAcceptError();

    tcpwork tcpw;

    void httpNewConnection();

    void dbg(QString msg);

    int connections = 0;
    QString JsonObjectTable2HtmlTable(QJsonObject JsonTable, QStringList colsTitles);
    void NewConnection();
    void AcceptError();
    void KeyPressArrive();
    void disconnected();
    void Response(int i, QString http, QString ContentType, QByteArray response);
    bool ResponseFile(int i, QString filepath);
};

#endif // HTTPSERVER_H
