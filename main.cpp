#include <QCoreApplication>
#include <QObject>
#include <QtCore>
#include <QUdpSocket>
#include <bits/stdc++.h>
#include "pt.h"
#include <QTcpServer>
//#include <QSerialPortInfo>
#include <QTcpSocket>
//#include <QSerialPort>
#include "udpreceiver.h"
#include <wiringSerial.h>
#include "receiverthr.h"
#include <unistd.h>
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

    cout<<"AbFixedWing 0.0\n";
    ifstream portf("port.txt");

    receiverthr rthr;
    rthr.receiver=new UdpReceiver;
    portf>>rthr.receiver->port;

    rthr.start();
    float pitch,roll;
    PT pt;
    pt.isRuning=1;
    pt.start();
    /*————————————————
    版权声明：本文为CSDN博主「-- 好名字 --」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/weixin_37789780/article/details/122468637*/

    /*————————————————
    版权声明：本文为CSDN博主「hu5566798」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/hu5566798/article/details/80777121*/
    QString str,rem;
    bool first;



    if ((rthr.receiver->fd = serialOpen ("/dev/ttyACM0", 9600)) < 0)
    {
        fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    }

    while(1)
    {

        QByteArray buf;
        if(serialDataAvail(rthr.receiver->fd)>0)
            buf=readline(rthr.receiver->fd).c_str();
        //buf+='\n';
        //cout<<buf.toStdString();
        if(!buf.isEmpty())
        {
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
            cout<<"HAHAHA:"<<roll<<' '<<pitch<<endl;
        }
        if(rthr.receiver->connected=1)
        {
            //QString da="Nice to meet you\n";
            QByteArray dataGram;
            //rthr.receiver->UdpServer->writeDatagram(dataGram,rthr.receiver->targetaddr,rthr.receiver->targetport);
            //rthr.receiver->UdpServer->waitForBytesWritten(1000);
            dataGram="R"+QString::fromLocal8Bit(to_string(roll).c_str()).toUtf8();
            rthr.receiver->UdpServer->writeDatagram(dataGram.data(),dataGram.size(),rthr.receiver->targetaddr,rthr.receiver->targetport);
            rthr.receiver->UdpServer->waitForBytesWritten(1000);
            dataGram="P"+QString::fromLocal8Bit(to_string(pitch).c_str()).toUtf8();
            rthr.receiver->UdpServer->writeDatagram(dataGram.data(),dataGram.size(),rthr.receiver->targetaddr,rthr.receiver->targetport);
            rthr.receiver->UdpServer->waitForBytesWritten(1000);
            usleep(5000);
        }
    }
    return 0;
}
