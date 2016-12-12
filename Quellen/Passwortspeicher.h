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
#ifndef PASSWORTSPEICHER_H
#define PASSWORTSPEICHER_H

#include <QtCore>

Q_DECLARE_LOGGING_CATEGORY(qalarm_klientPasswortspeicher)
class Passwortspeicher : public QObject
{
	Q_OBJECT
	public:
		explicit		Passwortspeicher(QObject *eltern = Q_NULLPTR);
		void			PasswortSetzen(const QString &passwort);
		void			PasswortLoeschen();
		const QString&	PasswortHolen() const;
		const bool&		PWSpeicher()const{return K_PWSpeicher;}

	private:
		Q_DISABLE_COPY(Passwortspeicher)
		QObject*		K_PW;
		QString			K_KeinPasswort;
		bool			K_PWSpeicher;


};

#endif // PASSWORTSPEICHER_H
