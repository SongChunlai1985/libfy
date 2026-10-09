#include "httpserver.h"

httpserver::httpserver()
{

}
void httpserver::httpRequestArrive0(){httpRequestArrive(0);}
void httpserver::httpRequestArrive1(){httpRequestArrive(1);}
void httpserver::httpRequestArrive2(){httpRequestArrive(2);}
void httpserver::httpRequestArrive3(){httpRequestArrive(3);}
void httpserver::httpRequestArrive4(){httpRequestArrive(4);}
void httpserver::httpRequestArrive5(){httpRequestArrive(5);}
void httpserver::httpRequestArrive6(){httpRequestArrive(6);}
void httpserver::httpRequestArrive7(){httpRequestArrive(7);}
void httpserver::httpRequestArrive8(){httpRequestArrive(8);}
void httpserver::httpRequestArrive9(){httpRequestArrive(9);}

void httpserver::init()
{

#if(0)
    QProcess *process = new QProcess();
    process->start("nginx");
#else
    httpServer.listen(httpport);
#endif
    httpServer.tcpsvr->setMaxPendingConnections(1024);
    connect(httpServer.tcpsvr, &QTcpServer::newConnection, this, &httpserver::httpNewConnection);
    connect(httpServer.tcpsvr, &QTcpServer::acceptError, this, &httpserver::httpAcceptError);


    tcpw.name = "HttpServer";
    httpServer.init();
}

void httpserver::httpNewConnection()
{
    dbg(QString(" Http newConnection ") + QString::number(connections) + httpServer.tcpsvr->errorString());
    httpServer.tcpskts[connections] = httpServer.tcpsvr->nextPendingConnection();
    httpInitConnect();
    connections++;
    if(connections > 9)connections = 0;
}

void httpserver::httpInitConnect()
{
    for(int i = 0; i < 10; i++){
        connect(httpServer.tcpskts[i], &QTcpSocket::disconnected, this, &httpserver::httpdisconnected);
    }
    connect(httpServer.tcpskts[0], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive0);
    connect(httpServer.tcpskts[1], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive1);
    connect(httpServer.tcpskts[2], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive2);
    connect(httpServer.tcpskts[3], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive3);
    connect(httpServer.tcpskts[4], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive4);
    connect(httpServer.tcpskts[5], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive5);
    connect(httpServer.tcpskts[6], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive6);
    connect(httpServer.tcpskts[7], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive7);
    connect(httpServer.tcpskts[8], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive8);
    connect(httpServer.tcpskts[9], &QTcpSocket::readyRead, this, &httpserver::httpRequestArrive9);
}

void httpserver::dbg(QString msg)
{
    tcpw.dbg(msg);
}

void httpserver::httpAcceptError()
{
    dbg(__FUNCTION__ + httpServer.tcpsvr->errorString());
}

void httpserver::httpRequestArrive(int i)
{
    dbg("Bytes Receive: " + QString::number(httpServer.tcpskts[i]->bytesAvailable()));
    QByteArray receivemsg = httpServer.tcpskts[i]->readAll();
    dbg("Request Data: \r\n" + receivemsg);

    QList<QByteArray> RequestInfo = receivemsg.split(char(13));
    foreach(QByteArray Request, RequestInfo)
    {
        if(Request.left(4) == "GET ")
        {
            QList<QByteArray> Words = Request.split(' ');
            if(Words.size() > 2 && Words[1].left(1) == "/")
            {
                if(ResponseFile(i, Words[1]))
                {
                    return;
                }
                else
                {
                    QJsonObject JsonPakge;
                    QStringList conditionlist = QString(Words[1].mid(2)).split('&');
                    foreach(QString condition, conditionlist)
                    {
                        QStringList conditionpair = condition.split('=');
                        if(conditionpair.size() == 2 && conditionpair[1] != "")JsonPakge.insert(conditionpair[0],
                                QUrl::fromPercentEncoding(QString(conditionpair[1]).toLocal8Bit()));
                    }

                    emit httpquerry(i, JsonPakge);
                }
            }
        }
    }

    if(!receivemsg.size())
    {
        Response(i,
                 "HTTP/1.1 204 OK\r\n",
                 "text/html;charset=utf-8",
                 "Welcome!!");
    }
}

bool httpserver::ResponseFile(int i, QString filepath)
{

    if(filepath == "/")
    {
        return false;
    }
    QByteArray File;
    QByteArray response;
    QString ContentType;

    QFile *file = new QFile("assets:" + filepath);
    if(file->exists())
    {
        file->open(QIODevice::ReadOnly);
        File = file->readAll();
        file->close();
        if(File.size())
        {
            response = File;
            ContentType = "image/x-icon;";
            dbg(response);
        }
        Response(i, "HTTP/1.1 200 OK\r\n", ContentType, response);
        return true;
    }
    return false;
}

void httpserver::Response(int i, QString http, QString ContentType, QByteArray response)
{
    http += "Server: nginx\r\n";
    http += "Content-Type: " + ContentType + "\r\n";
    http += "Connection: keep-alive\r\n";
    http += QString("Content-Length: %1\r\n\r\n").arg(QString::number(response.size()));

    dbg("response:\r\n" + http + response);
    httpServer.tcpskts[i]->write(http.toUtf8() + response);
    httpServer.tcpskts[i]->flush();
    httpServer.tcpskts[i]->waitForBytesWritten(http.size() + response.size());
    //httpServer.tcpskts[i]->close();
}

void httpserver::httpdisconnected()
{
    dbg("HTTP Disconnected");
}

QString httpserver::JsonObjectTable2HtmlTable(QJsonObject JsonTable,
                                              QStringList colsTitles )
{
    QJsonArray DataJsonArray = JsonTable["items"].toArray();

    QString HtmlTable =
            "<center> \r\n"
            "<table id=mytable cellspacing=0 summary='Gird'> \r\n"
            "<caption> </caption> \r\n";
    HtmlTable +=
            "  <tr> \r\n";
    foreach(QString colsTitle, colsTitles) {
        HtmlTable +=
                "    <th scope=col>"+colsTitle+"</th> \r\n";
    }
    HtmlTable +=
            "  </tr> \r\n";

    foreach(QJsonValue JsonRow, DataJsonArray)
    {
        QJsonObject ObjRow = JsonRow.toObject();
        HtmlTable +=
                "  <tr> \r\n";
        foreach(QJsonValue Cell, ObjRow)
        {
            HtmlTable +=
                    "    <td class=alt>"+Cell.toString()+"</td> \r\n";
        }
        HtmlTable +=
                "  </tr> \r\n";
    }
    HtmlTable +=
            "</table> \r\n"
            "</center> \r\n";
    return HtmlTable;
}

void httpserver::NewConnection()
{
    dbg(QString(" newConnection ") + httpServer.tcpsvr->errorString());
    httpServer.tcpskt = httpServer.tcpsvr->nextPendingConnection();
    dbg(QString(" newConnection ") + httpServer.tcpskt->peerAddress().toString() + " " + httpServer.tcpskt->localAddress().toString());
    connect(httpServer.tcpskt, &QTcpSocket::readyRead, this, &httpserver::KeyPressArrive);
    connect(httpServer.tcpskt, &QTcpSocket::disconnected, this, &httpserver::disconnected);
    httpServer.tssend(" welcome ");
}

void httpserver::AcceptError()
{
    dbg(__FUNCTION__ + httpServer.tcpsvr->errorString());
}


void httpserver::KeyPressArrive()
{
    dbg(__FUNCTION__ + httpServer.tcpsvr->errorString());
}


void httpserver::disconnected()
{
    dbg(__FUNCTION__ + httpServer.tcpsvr->errorString());
}
