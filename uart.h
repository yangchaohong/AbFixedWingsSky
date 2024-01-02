#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

int dataAvail(int fd);

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);

int uart_send(int fd,char buf[], int len);

/*————————————————
版权声明：本文为CSDN博主「leumber」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/leumber/article/details/80105295*/

int readSerialByte(int fd, int timeout);
#endif // UART_H
