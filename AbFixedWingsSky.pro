QT -= gui
QT += network \
    widgets
QT += multimedia multimediawidgets
#QT       += serialport

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    pt.cpp \
    receiverthr.cpp \
    udpreceiver.cpp

TRANSLATIONS += \
    AbFixedWingsSky_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lwiringPi
LIBS += -lopencv_highgui
LIBS += -lopencv_core
LIBS += -lopencv_video
LIBS += -lopencv_videoio
LIBS += -lopencv_imgproc

HEADERS += \
    pt.h \
    receiverthr.h \
    udpreceiver.h


