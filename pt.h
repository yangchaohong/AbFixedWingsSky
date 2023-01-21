#ifndef PT_H
#define PT_H

#include <QThread>
#include <QObject>
#include <QWidget>
#include <bits/stdc++.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <QBuffer>
#include <QFile>
#include <unistd.h>
class PT : public QThread
{
    Q_OBJECT
public:
    PT();
    bool isRuning;
protected:
    virtual void run() Q_DECL_OVERRIDE;
};

#endif // PT_H
