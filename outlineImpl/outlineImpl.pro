#-------------------------------------------------
#
# Project created by QtCreator 2015-06-17T12:04:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = outlineImpl
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
TEMPLATE = app


SOURCES += main.cpp \
    img_provider.cpp \
    img_representation.cpp

HEADERS += \
    img_provider.h \
    make_unique.h \
    img_representation.h

LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_gpu
