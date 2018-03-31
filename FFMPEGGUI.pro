TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    ffmpeg.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

QMAKE_CXXFLAGS += -D__STDC_CONSTANT_MACROS
LIBS += -L$$PWD/ffmpeglib/lib -llibavcodec -llibavformat -llibavutil -llibswscale -llibswscale -llibswresample -llibavdevice -llibavfilter

INCLUDEPATH += $$PWD/ffmpeglib/include
DEPENDPATH += $$PWD/ffmpeglib/include

HEADERS += \
    ffmpeg.h
