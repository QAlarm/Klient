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
#ifndef PASSWORTSPEICHERGNOME_H
#define PASSWORTSPEICHERGNOME_H

#include <QtCore>
#include <libsecret/secret.h>

Q_DECLARE_LOGGING_CATEGORY(qalarm_klientPasswortspeicherGnome)
class PasswortspeicherGnome : public QObject
{
	Q_OBJECT
	public:
		explicit		PasswortspeicherGnome(QObject *eltern = Q_NULLPTR);
						~PasswortspeicherGnome();

		const QString&	PasswortHolen();
		void			PasswortSpeichern(const QString &passwort);
		void			PasswortLoeschen();

	private:
		QString				K_Passwort;
		SecretSchema*		K_Schema;
		GHashTable*			K_Tabelle;
};

#endif // PASSWORTSPEICHERGNOME_H
