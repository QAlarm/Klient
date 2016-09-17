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
#include "Websocket.h"
#include "Steuerung.h"

#include <QtGui>
#include <QtWidgets>

Q_LOGGING_CATEGORY(qalarm_klientHaupt, "QAlarm Klient.Hauptdialog")
DlgHaupt::DlgHaupt(Steuerung *steuerung, Websocket *verbindung, QWidget *eltern) : QMainWindow(eltern)
{
	setupUi(this);
	intProtokoll->setValue(PROTOKOLLEBENE);
	K_Fehleingabe=false;
	K_Websocket=verbindung;
	K_Steuerung=steuerung;
}

void DlgHaupt::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
			retranslateUi(this);
			break;
		default:
			break;
	}
}

void DlgHaupt::on_sfEinstellungen_clicked()
{
	Stapel->setCurrentIndex(1);
}

void DlgHaupt::on_bbJaNein_accepted()
{
	static uint PW_Speichern=(cbPasswortSpeichern->checkState() == Qt::Checked ? 1 : 0 );
	if (!K_Fehleingabe)
	{
		K_Steuerung->ParameterSpeichern(KONFIG_SERVER,txtEndpunkt->text());
		K_Steuerung->ParameterSpeichern(KONFIG_PROTOKOLLEBENE,intProtokoll->value());
		if (K_Steuerung->PWSpeicher())
			K_Steuerung->ParameterSpeichern(KONFIG_PASSWORTSPEICHERN,PW_Speichern);
		K_Steuerung->ProtokollebeneSetzen(intProtokoll->value());
		Stapel->setCurrentIndex(0);
	}
}

void DlgHaupt::on_bbJaNein_rejected()
{
	QMainWindow::statusBar()->showMessage(QString());
	ParameterSetzen();
	K_Fehleingabe=false;
	Stapel->setCurrentIndex(0);
}

void DlgHaupt::on_txtEndpunkt_editingFinished()
{
	QUrl URL(txtEndpunkt->text(),QUrl::StrictMode);
	if (URL.scheme()=="wss")
		K_Endpunkt=URL;
	else
	{
		K_Fehleingabe=true;
		QMainWindow::statusBar()->showMessage(tr("Die Endpunkt URL ist ungültig."));
	}
}

void DlgHaupt::Fehler(const QString &meldung)
{
	//TODO muss noch geändert werden
	QMessageBox::information(this,"",meldung);
}

void DlgHaupt::ParameterSetzen()
{
	QString wss="wss://";
	txtEndpunkt->setText(K_Steuerung->ParameterLaden(KONFIG_SERVER,wss).toString());
	if (wss != txtEndpunkt->text())
		K_Endpunkt=txtEndpunkt->text();
	intProtokoll->setValue(K_Steuerung->ParameterLaden(KONFIG_PROTOKOLLEBENE,PROTOKOLLEBENE).toInt());
	txtName->setText(K_Steuerung->ParameterLaden(KONFIG_ANMELDENAME,QString()).toString());
	if (K_Steuerung->PWSpeicher())
	{
		Qt::CheckState PW_Speichern=(K_Steuerung->ParameterLaden(KONFIG_PASSWORTSPEICHERN,0).toUInt() == 0 ?  Qt::Unchecked : Qt::Checked);
		cbPasswortSpeichern->setEnabled(true);
		cbPasswortSpeichern->setCheckState(PW_Speichern);
		if(PW_Speichern == Qt::Checked)
			txtPasswort->setText(K_Steuerung->PasswortHolen());
		sfPasswortLoeschen->setEnabled(true);
		if(txtEndpunkt->text()!=wss)
			sfAnmelden->setEnabled(true);
	}
	else
		qCDebug(qalarm_klientHaupt)<<tr("Kein Passwortspeicher");
}

void DlgHaupt::on_txtName_editingFinished()
{
	static QString alterName;
	if((alterName.isEmpty()) || (alterName!=txtName->text()))
	{
		alterName=txtName->text();
		PasswortNamePruefen();
	}
}

void DlgHaupt::on_txtPasswort_editingFinished()
{
	//BUG QTBUG-56047
	static QString altesPasswort;
	if((altesPasswort.isEmpty()) || (altesPasswort!=txtPasswort->text()))
	{
		altesPasswort=txtPasswort->text();
		PasswortNamePruefen();
	}
}

void DlgHaupt::PasswortNamePruefen()
{
	//BUG QTBUG-56047
	if (txtName->text().isEmpty() || txtPasswort->text().isEmpty())
	{
		qCDebug(qalarm_klientHaupt)<<tr("Passwort oder Name nicht gesetzt.");
		return;
	}
	K_Steuerung->ParameterSpeichern(KONFIG_ANMELDENAME,txtName->text());
	if(cbPasswortSpeichern->checkState() == Qt::Checked)
		K_Steuerung->PasswortSpeichern(txtPasswort->text());
	if (!K_Endpunkt.isEmpty())
		sfAnmelden->setEnabled(true);
}

void DlgHaupt::on_sfPasswortLoeschen_clicked()
{
	K_Steuerung->PasswortLoeschen();
}

void DlgHaupt::on_sfAnmelden_clicked()
{
	K_Websocket->open(QUrl(txtEndpunkt->text(),QUrl::StrictMode));
}
