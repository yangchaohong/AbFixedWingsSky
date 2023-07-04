#ifndef RECEIVERTHR_H
#define RECEIVERTHR_H

#include <QThread>
#include "udpreceiver.h"

class receiverthr : public QThread
{
    Q_OBJECT
public:
    receiverthr();
    UdpReceiver *receiver;
protected:
    virtual void run() Q_DECL_OVERRIDE;
};

#endif // RECEIVERTHR_H
