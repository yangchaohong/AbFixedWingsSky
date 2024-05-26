#include "udpreceiver.h"
//#include <wiringSerial.h>
#include <bits/stdc++.h>
#include<sstream>
using namespace std;

UdpReceiver::UdpReceiver(QObject *parent) : QObject(parent)
{

}

void UdpReceiver::readyData()
{
    if(!coned)
        return;
    QByteArray arr;
    arr.resize(UdpServer->bytesAvailable());
    UdpServer->readDatagram(arr.data(),arr.size(),&targetaddr,&targetport);
    //cout<<arr.toStdString()<<endl<<targetaddr.toString().toStdString()<<':'<<targetport<<endl;
    if(arr=="Hello")
    {
        connected=1;
    }
    if(arr[0]=='P')
    {
        pitchNeed=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(pitch_old!=pitchNeed)
    {
        //serialPrintf(fd,"P%f\n",pitchNeed),
        ostringstream oss;
        oss<<(int)pitchNeed;
        string ss(oss.str());
        ss="P"+ss+'\n';
        uart_send(fd,(char *)ss.c_str(),ss.size());
        cout<<'P'<<pitch_old<<' '<<pitchNeed<<endl;
        pitch_old=pitchNeed;
    }
    if(arr[0]=='R')
    {
        rollNeed=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(roll_old!=rollNeed)
    {
        //serialPrintf(fd,"R%f\n",rollNeed),
        ostringstream oss;
        oss<<(int)rollNeed;
        string ss(oss.str());
        ss="R"+ss+'\n';
        uart_send(fd,(char *)ss.c_str(),ss.size());
        cout<<'R'<<roll_old<<' '<<rollNeed<<endl;
                roll_old=rollNeed;
    }
    float yaw=0;
    if(arr[0]=='Y')
    {
        yaw=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(yaw_old!=yaw)
    {
        //serialPrintf(fd,"Y%f\n",yaw),
        ostringstream oss;
        oss<<yaw;
        string ss(oss.str());
        ss="Y"+ss+'\n';
        uart_send(fd,(char *)ss.c_str(),ss.size());
        cout<<'Y'<<yaw,yaw_old=yaw;
    }
    if(arr[0]=='T')
    {

        throttle=stoi(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(arr[0]=='F')
    {

        flap=stoi(arr.toStdString().substr(1,arr.toStdString().size()-1));
    }
    if(flap_old!=flap)
    {
        //serialPrintf(fd,"F%d\n",flap),
        ostringstream oss;
        oss<<flap;
        string ss(oss.str());
        ss="F"+ss+'\n';
        uart_send(fd,(char *)ss.c_str(),ss.size());
        cout<<'F'<<flap<<endl;
                flap_old=flap;
    }
    if(throttle_old!=throttle)
    {
        //serialPrintf(fd,"T%d\n",throttle),
        ostringstream oss;
        oss<<throttle;
        string ss(oss.str());
        ss="T"+ss+'\n';
        uart_send(fd,(char *)ss.c_str(),ss.size());
        cout<<'T'<<throttle_old<<' '<<throttle<<endl,
                throttle_old=throttle;
    }
}

int UdpReceiver::init()
{
    UdpServer=new QUdpSocket;
    UdpServer->bind(QHostAddress::Any, port);
}
