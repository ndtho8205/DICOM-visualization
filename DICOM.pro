QT       += core gui charts opengl
#QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DICOM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# ----------------------------------------------------------------------------
include(3rdparty/libqxt/libqxt.pri)

INCLUDEPATH += src/core \
            src/gui \
            src/utils \
            3rdparty/imebra/include

SOURCES += src/main.cpp \
        src/core/DicomReader.cpp \
        src/core/DicomVolumeRenderer.cpp \
        src/gui/DicomMainWindow.cpp \
        src/gui/DicomGLWidget.cpp \
        src/utils/DicomTexture.cpp \
        src/utils/DicomCameraController.cpp \
        src/core/DicomVolume.cpp \
        src/gui/DicomHistogramWidget.cpp \
        src/gui/DicomHistogramSpanSlider.cpp \
    src/utils/DicomLogicClass.cpp


HEADERS  += \
        src/core/DicomReader.h \
        src/core/DicomStructs.h \
        src/core/DicomVolumeRenderer.h \
        src/gui/DicomMainWindow.h \
        src/gui/DicomGLWidget.h \
        src/utils/Vector2.h \
        src/utils/Vector3.h \
        src/utils/Vector4.h \
        src/utils/Plane3.h \
        src/utils/DicomTexture.h \
        src/utils/DicomCameraController.h \
        src/core/DicomVolume.h \
        src/gui/DicomHistogramWidget.h \
        src/gui/DicomHistogramSpanSlider.h \
    src/utils/DicomLogicClass.h

FORMS    += src/gui/DicomMainWindow.ui

# ----------------------------------------------------------------------------

win32:LIBS += -lOpengl32 -lGlu32
else:unix:LIBS += -lGL -lGLU

unix: LIBS += -L3rdparty/imebra/lib/ -limebra
