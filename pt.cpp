#include "pt.h"
#include <sys/time.h>

using namespace cv;

PT::PT()
{

}

std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height) {
    return
            " libcamerasrc ! video/x-raw, "
            " width=(int)" + std::to_string(capture_width) + ","
            " height=(int)" + std::to_string(capture_height) + ","
            " framerate=(fraction)" + std::to_string(framerate) +"/1 !"
            " videoconvert ! videoscale !"
            " video/x-raw,"
            " width=(int)" + std::to_string(display_width) + ","
            " height=(int)" + std::to_string(display_height) + " ! appsink";
}//From https://github.com/Qengineering/Libcamera-OpenCV-RPi-Bullseye-32OS/blob/main/main.cpp

void PT::run()
{
    int capture_width = 320 ;//1280 ;
    int capture_height = 240; //720 ;
    int framerate = 15 ;
    int display_width = 160; //1280 ;
    int display_height = 120; //720 ;
    Mat srcImage;
    std::string pipeline = gstreamer_pipeline(capture_width, capture_height, framerate,display_width, display_height);
    VideoCapture videoCap(pipeline, cv::CAP_GSTREAMER);;
    if (!videoCap.isOpened())
    {
        std::cerr << "ERROR! Unable to open camera.\n";
    }
    std::cout << "Camera opened." << std::endl;
    QTcpServer server;
    QTcpSocket *socket;
    std::ifstream portf("port.txt");
    int a,port;
    portf>>a>>port;
    server.listen(QHostAddress::Any,port);
    tcp:
    server.waitForNewConnection(10000000);
    std::cout<<"New Connection Established!"<<std::endl;
    socket = server.nextPendingConnection();
    socket->socketOption(QAbstractSocket::SendBufferSizeSocketOption)=1048576;
    while(socket->state()==QAbstractSocket::ConnectedState)
    {
        //socket->waitForReadyRead(1000);
        //std::cout<<socket->readAll().toStdString()<<std::endl;
        timeval start,end;
        gettimeofday(&start,NULL);
        videoCap.read(srcImage);
        if(srcImage.empty())
            std::cerr<<"ERROR CAM!\n";
        cvtColor(srcImage,srcImage,COLOR_BGR2RGB);
        QImage qsrcImage=QImage((const unsigned char*)(srcImage.data),srcImage.cols,srcImage.rows,srcImage.step,QImage::Format_RGB888);
        QByteArray baim,img="end\n",st="start\n",el="\n";
        QBuffer buffer(&baim);
        buffer.open(QIODevice::ReadWrite);
        qsrcImage.save(&buffer, "PNG");
        baim=qCompress(baim,6);
        baim=baim.toBase64();

        socket->write(st);
        socket->waitForBytesWritten();
        socket->write(baim,baim.size());
        socket->waitForBytesWritten();
        socket->write(el);
        socket->waitForBytesWritten();
        socket->write(img);
        socket->waitForBytesWritten();
        gettimeofday(&end,NULL);
        double timeuse =( end.tv_sec - start.tv_sec ) + (double)((double)end.tv_usec - (double)start.tv_usec)/1000000;
        //std::cout<<"Send Picture "<<(float)timeuse<<std::endl;
    }
    std::cout<<"Connection Lost!\n";
    goto tcp;
}
