QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        dashboard.cpp \
        main.cpp \
        tcpclient.cpp \
        tcpclientwrapper.cpp \
        tcpserver.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /root/$${TARGET}
else: unix:!android: target.path = /root/$${TARGET}
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dashboard.h \
    tcpclient.h \
    tcpclientwrapper.h \
    tcpserver.h
