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
#include "Passwortspeicher.h"
#ifdef GNOMEPWSPEICHER
#include "PasswortspeicherGnome.h"
#endif

Q_LOGGING_CATEGORY(qalarm_klientPasswortspeicher, "QAlarm Klient.Passwortspeicher")
Passwortspeicher::Passwortspeicher(QObject *eltern) : QObject(eltern)
{
#ifdef GNOMEPWSPEICHER
	K_PW =new PasswortspeicherGnome(this);
	K_PWSpeicher=true;
#else
	K_PW =Q_NULLPTR;
	K_PWSpeicher=false;
#endif
	K_KeinPasswort="";
}
void Passwortspeicher::PasswortSetzen(const QString &passwort)
{
	if(K_PW)
	{
		qCDebug(qalarm_klientPasswortspeicher)<<tr("Passwortspeicher: %1").arg(K_PW->metaObject()->className());
	}
}

const QString& Passwortspeicher::PasswortHolen() const
{
	if(K_PW)
	{
		qCDebug(qalarm_klientPasswortspeicher)<<tr("Passwortspeicher: %1").arg(K_PW->metaObject()->className());
		return K_KeinPasswort;
	}
	else
		qCDebug(qalarm_klientPasswortspeicher)<<tr("Kein Passwortspeicher verfügbar");
	return K_KeinPasswort;
}
