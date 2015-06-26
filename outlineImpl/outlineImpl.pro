#-------------------------------------------------
#
# Project created by QtCreator 2015-06-17T12:04:56
#
#-------------------------------------------------

QT       += core
QT += gui
QT += widgets

TARGET = outlineImpl
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
TEMPLATE = app

#PRECOMPILED_HEADER = img_includs.h

SOURCES += main.cpp \
    img_provider.cpp \
    img_representation.cpp \
    img_algorithm.cpp \
    img_reader.cpp \
    imgtestgui.cpp \
    img_datamodel.cpp

HEADERS += \
    img_provider.h \
    make_unique.h \
    img_representation.h \
    img_algorithm.h \
    img_reader.h \
    imgtestgui.h \
    img_includs.h \
    img_datamodel.h

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
LIBS += -ltiff

FORMS += \
    imgtestgui.ui
