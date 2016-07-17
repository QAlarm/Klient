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
#include "PasswortspeicherKDE.h"
#include "Parameter.h"
#include <QApplication>
#include <QWidget>
#include <KWallet>


using namespace  KWallet;
Q_LOGGING_CATEGORY(qalarm_klientPasswortspeicherKDE, "QAlarm Klient.Passwortspeicher.KDE")
PasswortspeicherKDE::PasswortspeicherKDE(QObject *eltern) : QObject(eltern)
{
	K_KeinPW="";
	K_gueltig=true;
	K_PWSpeicher=Wallet::openWallet(Wallet::NetworkWallet(),0);
	if(K_PWSpeicher ==0)
	{
		qCWarning(qalarm_klientPasswortspeicherKDE)<<tr("Konnte den Passwortspeicher nicht laden");
		K_gueltig=false;
	}
}

void PasswortspeicherKDE::PasswortLoeschen()
{
	if(!K_gueltig)
	{
		qCDebug(qalarm_klientPasswortspeicherKDE)<<tr("Kein Passwortspeicher offen. Löschen nicht möglich.");
		return;
	}
	if(K_PWSpeicher->removeEntry(PROGRAMMNAME)!=0)
		qCWarning(qalarm_klientPasswortspeicherKDE)<<tr("Das Passwort konnte nicht gelöscht werden.");
}

void PasswortspeicherKDE::PasswortSpeichern(const QString &passwort)
{
	if(!K_gueltig)
	{
		qCDebug(qalarm_klientPasswortspeicherKDE)<<tr("Kein Passwortspeicher offen. Speichern nicht möglich.");
		return;
	}
	if (K_PWSpeicher->writePassword(PROGRAMMNAME,passwort)!=0)
		qCWarning(qalarm_klientPasswortspeicherKDE)<<tr("Das Passwort konnte nicht gespeichert werden.");
}

const QString& PasswortspeicherKDE::PasswortHolen()
{
	if(!K_gueltig)
	{
		qCDebug(qalarm_klientPasswortspeicherKDE)<<tr("Kein Passwortspeicher offen. Laden nicht möglich.");
		return K_KeinPW;
	}
	QString PW;
	if(K_PWSpeicher->readPassword(PROGRAMMNAME,PW)!=0)
	{
		qCWarning(qalarm_klientPasswortspeicherKDE)<<tr("Das Passwort konnte nicht gelesen werden.");
		return K_KeinPW;
	}
	K_KeinPW=PW;
	return K_KeinPW;
}
