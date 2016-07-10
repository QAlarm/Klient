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
#ifndef DLGHAUPT_H
#define DLGHAUPT_H

#include "ui_DlgHaupt.h"
#include <QUrl>

class Steuerung;
class DlgHaupt : public QMainWindow, private Ui::DlgHaupt
{
	Q_OBJECT
	public:
		explicit DlgHaupt(QWidget *eltern = Q_NULLPTR);

	private Q_SLOTS:
		void		on_sfEinstellungen_clicked();
		void		on_bbJaNein_accepted();
		void		on_bbJaNein_rejected();
		void		on_txtEndpunkt_editingFinished();
		void		Fehler(const QString &meldung);
		void		ParameterSetzen();

	private:
		QUrl		K_Endpunkt;
		bool		K_Fehleingabe;
		Steuerung*	K_Steuerung;

	protected:
		void		changeEvent(QEvent *e);
};

#endif // DLGHAUPT_H
