#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T11:27:46
#
#-------------------------------------------------

QT       += core gui widgets

isEmpty(LOKAL) {
include(/usr/include/qalarm-lib/Gemeinsam.pri)
INCLUDEPATH += /usr/include/qalarm-lib
}
else {
include(../Lib/Gemeinsam.pri)
INCLUDEPATH += ../Lib/Quellen
LIBS	    += -L../Lib/bin
}

TARGET = qalarm-klient
TEMPLATE = app

LIBS += -lqalarm

SOURCES += Quellen/Start.cpp\
	Quellen/DlgHaupt.cpp \
    Quellen/Steuerung.cpp

HEADERS  += Quellen/DlgHaupt.h \
    Quellen/Parameter.h \
    Quellen/Steuerung.h

FORMS    += Dialoge/DlgHaupt.ui
