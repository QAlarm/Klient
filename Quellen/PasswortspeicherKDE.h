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
#ifndef PASSWORTSPEICHERKDE_H
#define PASSWORTSPEICHERKDE_H

#include <QtCore>


Q_DECLARE_LOGGING_CATEGORY(qalarm_klientPasswortspeicherKDE)
namespace KWallet
{
	class Wallet;
}
class PasswortspeicherKDE : public QObject
{
	Q_OBJECT
	public:
		explicit			PasswortspeicherKDE(QObject *eltern = Q_NULLPTR);
							~PasswortspeicherKDE();

		const QString&		PasswortHolen();
		void				PasswortSpeichern(const QString &passwort);
		void				PasswortLoeschen();

	private:
		Q_DISABLE_COPY(PasswortspeicherKDE)
		KWallet::Wallet*	K_PWSpeicher;
		bool				K_gueltig;
		QString				K_KeinPW;
};

#endif // PASSWORTSPEICHERKDE_H
