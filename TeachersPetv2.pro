#-------------------------------------------------
#
# Project created by QtCreator 2018-02-25T20:39:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeachersPetv2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ui/mainwindow.cpp \
    main.cpp \
    ui/addstudent.cpp \
    ui/addstudentdialog.cpp \
    data/student.cpp \
    data/dataadapter.cpp \
    data/resetter.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/addstudent.h \
    ui/addstudentdialog.h \
    data/student.h \
    data/dataadapter.h \
    data/resetter.h

FORMS += \
    ui/mainwindow.ui

SUBDIRS += \
    TeachersPetv2.pro
