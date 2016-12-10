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

contains (GNOME,true) {
contains(KDE,true) {
error(KDE und GNOME kann nicht gleichzeitig benutzt werden.)
}
DEFINES += GNOMEPWSPEICHER
SOURCES += Quellen/PasswortspeicherGnome.cpp
HEADERS += Quellen/PasswortspeicherGnome.h
PKGCONFIG += libsecret-1
CONFIG += link_pkgconfig no_keywords
}

contains (KDE,true) {
contains(GNOME,true) {
error(KDE und GNOME kann nicht gleichzeitig benutzt werden.)
}
QT	+= KWallet
DEFINES += KDEPWSPEICHER
SOURCES	+= Quellen/PasswortspeicherKDE.cpp
HEADERS	+= Quellen/PasswortspeicherKDE.h
}

TARGET = qalarm-klient
TEMPLATE = app

LIBS += -lqalarm

SOURCES += Quellen/Start.cpp\
	   Quellen/DlgHaupt.cpp \
	   Quellen/Steuerung.cpp \
	   Quellen/Passwortspeicher.cpp \
    Quellen/TmWochenabfrage.cpp



HEADERS  += Quellen/DlgHaupt.h \
	    Quellen/Parameter.h \
	    Quellen/Steuerung.h \
	    Quellen/Passwortspeicher.h \
    Quellen/TmWochenabfrage.h



FORMS    += Dialoge/DlgHaupt.ui
