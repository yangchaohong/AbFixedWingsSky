# AbFixedWingsSky
AbFixedWings For Raspberry Pi

构建：使用Qt 5.15构建

How to compile-on Orange Pi Zero 2W:

1.Install necessary packages by apt

  sudo apt install git build-essential libopencv-dev qtbase5-dev qtmultimedia5-dev

  wget https://github.com/WiringPi/WiringPi/releases/download/2.61-1/wiringpi-2.61-1-arm64.deb

  sudo dpkg -i wiringpi-2.61-1-arm64.deb

2.Pull codes from Github

  git clone https://github.com/yangchaohong/AbFixedWingsSky

3.Edit codes to support your platform

  main.cpp line 72:    
  
                          if ((rthr.receiver->fd = serialOpen ("/dev/ttyUSB0", 115200)) < 0)
  
                                                                      ↑
                                                                      
                                                          Change it to your UART Port

  pt.cpp line 33~39: 
  
                     int deviceID = 0; //相机设备号

                     videoCap.open(deviceID); //打开相机
    
                     videoCap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
    
                     videoCap.set(cv::CAP_PROP_FRAME_WIDTH, 800); //图像的宽，需要相机支持此宽
    
                     videoCap.set(cv::CAP_PROP_FRAME_HEIGHT, 600); //图像的高，需要相机支持此高
    
                     videoCap.set(cv::CAP_PROP_FPS, 30);

                                           ↑

                  Change resolution and frame rate to suit the camera

4.Compile it!

  mkdir build && cd build

  qmake ..
  
  make -j2

5.Create port.txt

  add your ports of data trans and picture trans ports to port.txt like this:

  1354

  1145

6.Run it by "sudo ./AbFixedWingsSky"
