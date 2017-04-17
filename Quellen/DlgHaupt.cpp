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
#include "TmWochenabfrage.h"

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
	K_TmWochenabfrage=new TmWochenabfrage(this);
	connect(K_Websocket,&Websocket::Fehler,this,&DlgHaupt::Socketfehler);
	connect(K_Websocket,&Websocket::connected,this,&DlgHaupt::MitServerVerbunden);
	connect(sb_KW,SIGNAL(valueChanged(int)),K_TmWochenabfrage,SLOT(KWgeaendert(int)));
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
		K_Steuerung->ParameterSpeichern(KONFIG_BMELD_EMPFAENGER,txtBereitschaftsmeldungEmpfaenger->text().split(','));
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
	K_LetzteSeite=Stapel->currentWidget();
	txtFehler->append(meldung);
	Stapel->setCurrentIndex(3);

}

void DlgHaupt::Socketfehler(const QString &meldung)
{
	Fehler(meldung);
	sfAnmelden->setEnabled(true);
}

void DlgHaupt::ParameterSetzen()
{
	static QString wss="wss://";
	txtEndpunkt->setText(K_Steuerung->ParameterLaden(KONFIG_SERVER,wss).toString());
	if (wss != txtEndpunkt->text())
		K_Endpunkt=txtEndpunkt->text();
	intProtokoll->setValue(K_Steuerung->ParameterLaden(KONFIG_PROTOKOLLEBENE,PROTOKOLLEBENE).toInt());
	txtName->setText(K_Steuerung->ParameterLaden(KONFIG_ANMELDENAME,QString()).toString());
	txtBereitschaftsmeldungEmpfaenger->setText(K_Steuerung->ParameterLaden(KONFIG_BMELD_EMPFAENGER,QStringList()).toStringList().join(','));
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
	//FIXME Zum Testen
	Stapel->setCurrentIndex(2);
	return;

	sfAnmelden->setEnabled(false);
	K_Websocket->open(QUrl(txtEndpunkt->text(),QUrl::StrictMode));
}

void DlgHaupt::on_bbFehlerOK_accepted()
{
	Stapel->setCurrentWidget(K_LetzteSeite);
}

void DlgHaupt::MitServerVerbunden()
{
	qCDebug(qalarm_klientHaupt)<<tr("Verbindung hergestellt");
}

void DlgHaupt::on_Stapel_currentChanged(int index)
{
	if (index==2)
	{
		//BUG Wenn man in der letzten KW vom Jahr ist, kann man die Nächste nicht ausfüllen.
		//QDate Datum=QDate::currentDate();
		QDate Datum=QDate(2016,12,26);
		sb_KW->setRange(Datum.weekNumber(),K_TmWochenabfrage->Wochen().size());
		sb_KW->setValue(Datum.weekNumber());
		tv_Wochenabfrage->setModel(K_TmWochenabfrage);
	}
}

void DlgHaupt::on_sfWochenabfrageSenden_clicked()
{
	QJsonObject Meldung;
	Meldung["recipient"]=QJsonArray::fromStringList(txtBereitschaftsmeldungEmpfaenger->text().split(','));
	Meldung["data"]=K_TmWochenabfrage->Meldungen();
	//FIXME zum Testen
	qCDebug(qalarm_klientHaupt)<<Meldung;

}
