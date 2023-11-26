# AbFixedWingsSky
AbFixedWings For Raspberry Pi

构建：使用Qt 5.15构建

How to compile-on Raspberry Pi Zero 2W:

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

  pt.cpp line 25~29: 
  
                     int capture_width = 800 ;//1280 ;
  
                     int capture_height = 600; //720 ;
                     
                     int framerate = 15 ;
                     
                     int display_width = 800; //1280 ;
                     
                     int display_height = 600; //720 ;

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
