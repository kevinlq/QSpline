QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DESTDIR = $$PWD/bin


include($$PWD/3rdparty/spline.pri)
INCLUDEPATH +=$$PWD/3rdparty

SOURCES += \
    CurveModel.cpp \
    CurveView.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    CurveModel.h \
    CurveView.h \
    Widget.h
