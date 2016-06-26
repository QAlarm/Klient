#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T11:27:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = klient
TEMPLATE = app
DESTDIR = bin
UI_DIR= tmp/ui
MOC_DIR= tmp/moc
OBJECTS_DIR= tmp/obj
RCC_DIR= tmp/rcc

QMAKE_LFLAGS += -fuse-ld=gold

SOURCES += Quellen/Start.cpp\
	Quellen/DlgHaupt.cpp

HEADERS  += Quellen/DlgHaupt.h

FORMS    += Dialoge/DlgHaupt.ui
