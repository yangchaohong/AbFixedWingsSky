#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include "uart.h"

class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    explicit UdpReceiver(QObject *parent = nullptr);
    QUdpSocket *UdpServer;
    int port,throttle=0,throttle_old=0;
    QHostAddress targetaddr;//ip
    quint16 targetport;
    bool connected=0;
    float pitchNeed=0,pitch_old=0,rollNeed=0,roll_old=0,yaw_old=0,t_old=0,flap_old=0;
    int fd,flap;
    int init();
    bool coned=0;
public slots:
    void readyData();
};

#endif // UDPRECEIVER_H
