#include "receiverthr.h"
#include <iostream>

receiverthr::receiverthr()
{

}

void receiverthr::run()
{
    std::cout<<"receiverthr!\n";
    receiver->init();
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    QObject::connect(receiver->UdpServer, &QUdpSocket::readyRead, receiver, &UdpReceiver::readyData,Qt::DirectConnection);
    exec();
}
