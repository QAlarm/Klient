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
#include "Protokollierung.h"
#include "Parameter.h"
#include "Passwortspeicher.h"

Q_LOGGING_CATEGORY(qalarm_klientSteuerung, "QAlarm Klient.Steuerung")
Steuerung::Steuerung(QObject *eltern) : QObject(eltern)
{
	K_Konfiguration=new Konfiguration(this);
	K_Passwortspeicher=new Passwortspeicher(this);
	K_KeinPasswort="";
	K_KeinPWSpeicher=false;
	connect(K_Konfiguration,&Konfiguration::Geladen,this,&Steuerung::KonfigGeladen);
	qCDebug(qalarm_klientSteuerung)<<tr("Steuerung geladen");
}

void Steuerung::KonfigGeladen()
{
	ProtokollebeneSetzen(K_Konfiguration->WertHolen(KONFIG_PROTOKOLLEBENE,PROTOKOLLEBENE).toInt());
	Q_EMIT Geladen();
}

QVariant Steuerung::ParameterLaden(const QString &welchen)const
{
	return ParameterLaden(welchen,QVariant());
}

QVariant Steuerung::ParameterLaden(const QString &welchen, const QVariant &vorgabe) const
{
	if (!K_Konfiguration)
		return QVariant();
	return K_Konfiguration->WertHolen(welchen,vorgabe);
}

void Steuerung::ParameterSpeichern(const QString &welchen,const QVariant &wert)
{
	if (!K_Konfiguration)
		return;
	K_Konfiguration->WertSetzen(welchen,wert);
}

void Steuerung::ProtokollebeneSetzen(const int &ebene)
{
	Protokollierung* Protollebene=new Protokollierung(ebene,this);
	Q_UNUSED(Protollebene);
}
void Steuerung::PasswortSpeichern(const QString &passwort)
{
	if(K_Passwortspeicher)
		K_Passwortspeicher->PasswortSetzen(passwort);
}

const QString& Steuerung::PasswortHolen() const
{
	if(K_Passwortspeicher)
		return K_Passwortspeicher->PasswortHolen();
	return K_KeinPasswort;
}

const bool& Steuerung::PWSpeicher()const
{
	if (!K_Passwortspeicher)
		return K_KeinPWSpeicher;
	return K_Passwortspeicher->PWSpeicher();
}
