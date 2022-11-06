QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera/camera.cpp \
    color/color.cpp \
    file_utils/file_utils.cpp \
    light/light.cpp \
    main.cpp \
    gui/mainwindow.cpp \
    material/material.cpp \
    objects/model/model.cpp \
    objects/model/test_model.cpp \
    ray/ray.cpp \
    scene/scene.cpp \
    objects/sphere/sphere.cpp

HEADERS += \
    camera/camera.h \
    color/color.h \
    file_utils/file_utils.h \
    gui/mainwindow.h \
    intersection/intersection.h \
    light/light.h \
    material/material.h \
    objects/model/model.h \
    objects/model/test_model.h \
    objects/object.h \
    property/property.hpp \
    ray/ray.h \
    scene/scene.h \
    objects/sphere/sphere.h

INCLUDEPATH += \
    ray \
    camera \
    gui \
    material \
    intersection \
    scene \
    objects/sphere \
    color \
    objects \
    objects/model \
    property \
    light \
    file_utils

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
