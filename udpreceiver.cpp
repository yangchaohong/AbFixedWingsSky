#include "udpreceiver.h"
#include <wiringSerial.h>
#include <bits/stdc++.h>
using namespace std;

UdpReceiver::UdpReceiver(QObject *parent) : QObject(parent)
{

}

void UdpReceiver::readyData()
{
    QByteArray arr;
    arr.resize(UdpServer->bytesAvailable());
    UdpServer->readDatagram(arr.data(),arr.size(),&targetaddr,&targetport);
    //cout<<arr.toStdString()<<endl<<targetaddr.toString().toStdString()<<':'<<targetport<<endl;
    if(arr=="Hello")
    {
        connected=1;
	//cout<<targetaddr.toString().toStdString()<<':'<<targetport<<endl;
    }
    if(arr[0]=='P')
    {
        pitchNeed=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(pitch_old!=pitchNeed)
        serialPrintf(fd,"P%f\n",pitchNeed),
                cout<<'P'<<pitch_old<<' '<<pitchNeed<<endl,
                pitch_old=pitchNeed;
    if(arr[0]=='R')
    {
        rollNeed=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(roll_old!=rollNeed)
        serialPrintf(fd,"R%f\n",rollNeed),
                cout<<'R'<<roll_old<<' '<<rollNeed<<endl,
                roll_old=rollNeed;
    if(arr[0]=='Y')
    {
        float yaw=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));
        serialPrintf(fd,"Y%f\n",yaw),cout<<'Y'<<yaw;
    }
    if(arr[0]=='T')
    {

        throttle=stoi(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(throttle_old!=throttle)
        serialPrintf(fd,"T%d\n",throttle),
                cout<<'T'<<throttle_old<<' '<<throttle<<endl,
                throttle_old=throttle;
}

int UdpReceiver::init()
{
    UdpServer=new QUdpSocket;
    UdpServer->bind(QHostAddress::Any, port);
}
