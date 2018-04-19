TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    ffmpeg.cpp \
    ffmpeglib/src/cmdutils.c \
    ffmpeglib/src/ffmpeg_c.c \
    ffmpeglib/src/ffmpeg_filter.c \
    ffmpeglib/src/ffmpeg_hw.c \
    ffmpeglib/src/ffmpeg_opt.c \
    fileinformation.cpp

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
    ffmpeg.h \
    ffmpeglib/include/cmdutils.h \
    ffmpeglib/include/ffmpeg_c.h \
    fileinformation.h
