#include "uart.h"

int dataAvail(int fd)
{
    int bytes;
    ioctl(fd, TIOCINQ, &bytes);
    return bytes;
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    /*获取原有串口配置*/
    if  ( tcgetattr( fd,&oldtio)  !=  0) {
        perror("SetupSerial 1");
        return -1;
    }
    memset( &newtio, 0, sizeof(newtio) );
    /*CREAD 开启串行数据接收，CLOCAL并打开本地连接模式*/
    newtio.c_cflag  |=  CLOCAL | CREAD;

    /*设置数据位*/
    newtio.c_cflag &= ~CSIZE;
    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }
    /* 设置奇偶校验位 */
    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }
    /* 设置波特率 */
    switch( nSpeed )
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }
    /*设置停止位*/
    if( nStop == 1 )/*设置停止位；若停止位为1，则清除CSTOPB，若停止位为2，则激活CSTOPB*/
        newtio.c_cflag &=  ~CSTOPB;/*默认为一位停止位； */
    else if ( nStop == 2 )
        newtio.c_cflag |=  CSTOPB;
    /*设置最少字符和等待时间，对于接收字符和等待时间没有特别的要求时*/
    newtio.c_cc[VTIME]  = 0;/*非规范模式读取时的超时时间；*/
    newtio.c_cc[VMIN] = 0;/*非规范模式读取时的最小字符数*/
    /*tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */
    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }
    //  printf("set done!\n\r");
    return 0;
}

int uart_send(int fd,char buf[], int len)
{
    int ret = 0;
    int count = 0;

    tcflush(fd, TCIFLUSH);

    while (len > 0)
    {

        ret = write(fd, (char*)buf + count, len);
        if (ret < 1)
        {
            break;
        }
        count += ret;
        len = len - ret;
    }

    return count;
}

int readSerialByte(int fd, int timeout) {
    // 设置超时时间
    struct timeval tv;
    tv.tv_sec = timeout / 1000;  // 秒
    tv.tv_usec = (timeout % 1000) * 1000;  // 微秒

    // 设置文件描述符集合
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    // 使用select函数检测串口是否有数据可读
    int result = select(fd + 1, &fds, NULL, NULL, &tv);
    if (result == -1) {
        perror("Failed to select");
        return -1;
    } else if (result == 0) {
        printf("Timeout occurred\n");
        return -1;
    }

    // 读取串口数据
    unsigned char data;
    ssize_t bytesRead = read(fd, &data, 1);
    if (bytesRead == -1) {
        perror("Failed to read from serial port");
        return -1;
    } else if (bytesRead == 0) {
        printf("No data available\n");
        return -1;
    }

    return data;
}
