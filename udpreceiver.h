#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

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
    float pitchNeed=0,pitch_old=0,rollNeed=0,roll_old=0;
    int fd ;
    int init();
public slots:
    void readyData();
};

#endif // UDPRECEIVER_H
