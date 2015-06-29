#-------------------------------------------------
#
# Project created by QtCreator 2015-06-17T12:04:56
#
#-------------------------------------------------

QT += core
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
    img_datamodel.cpp \
    cuda_algo.cu

SOURCES -= cuda_algo.cu

HEADERS += \
    img_provider.h \
    make_unique.h \
    img_representation.h \
    img_algorithm.h \
    img_reader.h \
    imgtestgui.h \
    img_includs.h \
    img_datamodel.h \
    cuda_algo.h

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
#LIBS += -lopencv_gpu
LIBS += -ltiff

FORMS += \
    imgtestgui.ui

#cuda
CUDA_SOURCES += cuda_algo.cu

# Path to cuda toolkit install
CUDA_DIR      = /usr/local/cuda-7.0
# Path to header and libs files
INCLUDEPATH  += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib64     # Note I'm using a 64 bits Operating system
# libs used in your code
LIBS += -lcudart -lcuda
# GPU architecture
CUDA_ARCH     = sm_20                # Yeah! I've a new device. Adjust with your compute capability
# Here are some NVCC flags I've always used by default.
NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v

# Prepare the extra compiler configuration (taken from the nvidia forum - i'm not an expert in this part)
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')

cu.commands = $$CUDA_DIR/bin/nvcc -m64 --std=c++11 -arch=$$CUDA_ARCH -c $$NVCCFLAGS \
                $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT} \
                2>&1 | sed -r \"s/\\(([0-9]+)\\)/:\\1/g\" 1>&2
# nvcc error printout format ever so slightly different from gcc
# http://forums.nvidia.com/index.php?showtopic=171651

cu.dependency_type = TYPE_C # there was a typo here. Thanks workmate!
cu.depend_command = $$CUDA_DIR/bin/nvcc --std=c++11 -M $$CUDA_INC $$NVCCFLAGS   ${QMAKE_FILE_NAME}

cu.input = CUDA_SOURCES
cu.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cu.o
# Tell Qt that we want add more stuff to the Makefile
QMAKE_EXTRA_COMPILERS += cu
