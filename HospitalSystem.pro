QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doctoreditview.cpp \
    drugeditview.cpp \
    idatabase.cpp \
    main.cpp \
    loginview.cpp \
    mainview.cpp \
    patienteditview.cpp \
    registerview.cpp \
    treatrecordeditview.cpp

HEADERS += \
    doctoreditview.h \
    drugeditview.h \
    idatabase.h \
    loginview.h \
    mainview.h \
    patienteditview.h \
    registerview.h \
    treatrecordeditview.h

FORMS += \
    doctoreditview.ui \
    drugeditview.ui \
    loginview.ui \
    mainview.ui \
    patienteditview.ui \
    registerview.ui \
    treatrecordeditview.ui

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./QXlsx/         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./QXlsx/source/  # current QXlsx source path is ./source/
include(./QXlsx/QXlsx.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
