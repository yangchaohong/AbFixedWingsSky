#include <QCoreApplication>
#include <QUdpSocket>
#include <bits/stdc++.h>
#include "pt.h"
#include <QTcpServer>
#include <QSerialPortInfo>
#include <QTcpSocket>
#include <QSerialPort>
#include <wiringSerial.h>
using namespace std;
using namespace cv;
string readline(int fd)
{
    string s="";
    char c=0;
    while(c!='\n')
    {
        c=serialGetchar(fd);
        s+=c;
    }
    return s;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSerialPort serial;
    cout<<"AbFixedWing 0.0\n";
    ifstream portf("port.txt");
    QHostAddress targetaddr;//ip
    quint16 targetport;
    int port;
    portf>>port;
    QUdpSocket UdpServer;
    bool connected=0;
    UdpServer.bind(QHostAddress::Any, port);
    float pitch,roll,pitchNeed,rollNeed;
    PT pt;
    pt.isRuning=1;
    pt.start();
    /*————————————————
    版权声明：本文为CSDN博主「-- 好名字 --」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/weixin_37789780/article/details/122468637*/
    int fd ;

    if ((fd = serialOpen ("/dev/serial0", 9600)) < 0)
    {
        fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
        return 1 ;
    }
    /*————————————————
    版权声明：本文为CSDN博主「hu5566798」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/hu5566798/article/details/80777121*/
    QString str,rem;
    bool first;
    while(1)
    {
        QByteArray arr;
        arr.resize(UdpServer.bytesAvailable());
        UdpServer.readDatagram(arr.data(),arr.size(),&targetaddr,&targetport);
        cout<<arr.toStdString()<<endl<<targetaddr.toString().toStdString()<<':'<<targetport<<endl;
        if(!arr.isEmpty())
        {
            if(arr=="Hello")
            {
                QString da="Nice to meet you";
                QByteArray dataGram=da.toUtf8();
                UdpServer.writeDatagram(dataGram,targetaddr,targetport);
                connected=1;
            }

        }
        if(arr[0]=='P')
        {
            pitchNeed=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));

        }
        serialPrintf(fd,"P%f\n",pitchNeed);
        if(arr[0]=='R')
        {
            rollNeed=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));

        }
        serialPrintf(fd,"R%f\n",rollNeed);
        if(arr[0]=='Y')
        {
            float yaw=stof(arr.toStdString().substr(1,arr.toStdString().size()-1));
            serialPrintf(fd,"Y%f\n",yaw);
        }
        QByteArray buf;
        if(serialDataAvail(fd)>0)
            buf=readline(fd).c_str();
        cout<<buf.toStdString();
        if(!buf.isEmpty())
        {
            if(buf[buf.size()-1]!='\n')
            {
                rem+=buf;
                continue;
            }
            if(!first)
            {
                if(buf[0]!='A')
                    continue;
                else
                    first=1;
            }
            QString e[10];
            str=rem+buf;
            rem="";
            string s=str.toStdString();
            int j=0,F=0;
            /*if(s[s.size()-1]!='\n')
                {
                    rem=str;
                    return;
                }*/
            //cout<< str.toStdString()<<endl;
            for(int i=0;i<s.size();i++)
            {
                string s1;
                for(;s[i]!='F'&&i<s.size();i++)
                    s1+=s[i];
                if(s1=="A_CYCLE")
                    continue;
                e[j++]=QString::fromLocal8Bit(s1.c_str());
                if(j>7)
                    break;
            }
            roll=e[6].toFloat();
            pitch=e[7].toFloat();
        }
        if(1)
        {
            QByteArray dataGram="R"+QString::fromLocal8Bit(to_string(roll).c_str()).toUtf8();
            UdpServer.writeDatagram(dataGram.data(),dataGram.size(),targetaddr,targetport);
            dataGram="P"+QString::fromLocal8Bit(to_string(pitch).c_str()).toUtf8();
            UdpServer.writeDatagram(dataGram.data(),dataGram.size(),targetaddr,targetport);
        }
    }
    return 0;
}
