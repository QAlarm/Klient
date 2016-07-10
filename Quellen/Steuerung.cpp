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
#include "Steuerung.h"
#include "Konfiguration.h"

Q_LOGGING_CATEGORY(qalarm_klientSteuerung, "QAlarm Klient.Steuerung")
Steuerung::Steuerung(QObject *eltern) : QObject(eltern)
{
	K_Konfiguration=new Konfiguration(this);
	connect(K_Konfiguration,&Konfiguration::Geladen,this,&Steuerung::KonfigGeladen);
	qCDebug(qalarm_klientSteuerung)<<tr("Steuerung geladen");
}

void Steuerung::KonfigGeladen()
{
	Q_EMIT Geladen();
}

QVariant Steuerung::ParameterLaden(const QString &welchen)const
{
	if (!K_Konfiguration)
		return QVariant();
	return K_Konfiguration->WertHolen(welchen);
}
