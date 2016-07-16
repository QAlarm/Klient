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
#include "PasswortspeicherGnome.h"
#include "Parameter.h"

Q_LOGGING_CATEGORY(qalarm_klientPasswortspeicherGnome, "QAlarm Klient.Passwortspeicher.Gnome")
PasswortspeicherGnome::PasswortspeicherGnome(QObject *eltern) : QObject(eltern)
{
	K_Tabelle=g_hash_table_new(g_str_hash, g_str_equal);
	K_Schema=secret_schema_newv("qalarm.klient",SECRET_SCHEMA_NONE,K_Tabelle);
}
PasswortspeicherGnome::~PasswortspeicherGnome()
{
	K_Passwort.fill('X');
	secret_schema_unref(K_Schema);
	g_hash_table_destroy(K_Tabelle);
}

const QString& PasswortspeicherGnome::PasswortHolen()
{
	GError* Fehler=Q_NULLPTR;
	gchar *Passwort=secret_password_lookup_sync(K_Schema,NULL,&Fehler,NULL);
	if(Passwort==NULL)
	{
		qCInfo(qalarm_klientPasswortspeicherGnome)<<tr("Kein Passwort gefunden.");
		if(Fehler)
		{
			qCWarning(qalarm_klientPasswortspeicherGnome)<<Fehler->message;
			g_error_free(Fehler);
		}
	}
	else
	{
		K_Passwort=QString::fromUtf8(Passwort);
		secret_password_free(Passwort);
		qCDebug(qalarm_klientPasswortspeicherGnome)<<tr("Passwort geladen");
	}
	return K_Passwort;
}

void PasswortspeicherGnome::PasswortSpeichern(const QString &passwort)
{
	GError* Fehler=Q_NULLPTR;
	bool ok=secret_password_store_sync(K_Schema,NULL,PROGRAMMNAME,passwort.toUtf8().constData(),NULL,&Fehler,NULL);
	if (!ok)
	{
		qCWarning(qalarm_klientPasswortspeicherGnome)<<tr("Konnte das Passwort nich speichern.");
		if(Fehler)
		{
			qCWarning(qalarm_klientPasswortspeicherGnome)<<Fehler->message;
			g_error_free(Fehler);
		}
	}
	else
		qCDebug(qalarm_klientPasswortspeicherGnome)<<tr("Passwort gespeichert");
	K_Passwort=passwort;
}
