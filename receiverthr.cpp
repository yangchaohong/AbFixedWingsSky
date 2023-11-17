#include "receiverthr.h"
#include <iostream>

receiverthr::receiverthr()
{

}

void receiverthr::run()
{
    std::cout<<"receiverthr!\n";
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    std::cout<<"receiverthr123!\n";
    receiver->UdpServer=new QUdpSocket;
    std::cout<<"receiverthr789!\n";
    receiver->UdpServer->bind(QHostAddress::Any, receiver->port);
    QObject::connect(receiver->UdpServer, &QUdpSocket::readyRead, receiver, &UdpReceiver::readyData,Qt::DirectConnection);
    std::cout<<"receiverthr456!\n";
    exec();
}
