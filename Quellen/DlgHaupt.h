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

class DlgHaupt : public QMainWindow, private Ui::DlgHaupt
{
		Q_OBJECT

	public:
		explicit DlgHaupt(QWidget *eltern = 0);

	protected:
		void changeEvent(QEvent *e);
};

#endif // DLGHAUPT_H
