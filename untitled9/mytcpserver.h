#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection(); //функция подключения клиента
    void slotClientDisconnected(); //функция отключения клиента
    //error  
    void slotClientDisconnected();   
    void slotServerRead(); // функция чтения сообщения, которое пришло от клиента
private:
    QTcpServer * mTcpServer;
    int server_status;
    //error
    int server;
    QMap<int,QTcpSocket *> SClients;
};
#endif // MYTCPSERVER_H







