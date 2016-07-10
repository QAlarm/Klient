/*
	Copyright (C) 2016 Frank Büttner qalarm@terrortux.de

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "DlgHaupt.h"
#include "Parameter.h"
#include "qalarmlib_global.h"

#include <QApplication>
#include <QtCore>

int main(int anzahlArgumente, char *argumente[])
{
	QApplication Anwendung(anzahlArgumente, argumente);

	QLoggingCategory::setFilterRules("*.critical=true\n.*.warning=true\n.*.info=true\n.*.debug=false");

	Anwendung.setApplicationName(PROGRAMMNAME);
	Anwendung.setApplicationVersion(VERSION);
	Anwendung.setOrganizationName(FIRMA);

	QTranslator QtUebersetzung;
	QTranslator AnwendungUeberstezung;
	QTranslator	BibliothekUebersetzung;

	QString Uebersetzungspfgad=QLibraryInfo::location(QLibraryInfo::TranslationsPath);

	QtUebersetzung.load(QString("qt_%1").arg(QLocale::system().name()),Uebersetzungspfgad);
	AnwendungUeberstezung.load(QString("%1_%2").arg(PROGRAMMNAME_KLEIN)
											   .arg(QLocale::system().name()),Uebersetzungspfgad);
	BibliothekUebersetzung.load(QString("%1_%2").arg(LIBNAME)
								.arg(QLocale::system().name()),Uebersetzungspfgad);

	Anwendung.installTranslator(&QtUebersetzung);
	Anwendung.installTranslator(&AnwendungUeberstezung);
	Anwendung.installTranslator(&BibliothekUebersetzung);

	DlgHaupt Hauptfenster;
	Hauptfenster.show();

	return Anwendung.exec();
}
