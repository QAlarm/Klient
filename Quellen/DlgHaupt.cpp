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
#include "Steuerung.h"
#include "Parameter.h"

#include <QtGui>
#include <QtWidgets>

DlgHaupt::DlgHaupt(QWidget *eltern) : QMainWindow(eltern)
{
	setupUi(this);
	K_Fehleingabe=false;
	K_Steuerung=new Steuerung(this);
	connect(K_Steuerung,&Steuerung::Fehler,this,&DlgHaupt::Fehler);
	connect(K_Steuerung,&Steuerung::Geladen,this,&DlgHaupt::ParameterSetzen);
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
	if (!K_Fehleingabe)
		Stapel->setCurrentIndex(0);
}

void DlgHaupt::on_bbJaNein_rejected()
{
	QMainWindow::statusBar()->showMessage(QString());
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
	//muss noch geändert werden
	QMessageBox::information(this,"",meldung);
}

void DlgHaupt::ParameterSetzen()
{
	QMessageBox::information(this,"","geladen");
	txtName->setText(K_Steuerung->ParameterLaden(ANMELDENAME).toString());
}
