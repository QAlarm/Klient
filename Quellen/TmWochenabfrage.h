#ifndef TMWOCHENABFRAGE_H
#define TMWOCHENABFRAGE_H

#include <QtCore>

#include "Meldungstag.h"

class TmWochenabfrage : public QAbstractTableModel
{
	Q_OBJECT
	public:
		TmWochenabfrage(QObject *eltern=Q_NULLPTR);
		int							rowCount(const QModelIndex &eltern=QModelIndex()) const Q_DECL_OVERRIDE {Q_UNUSED(eltern);return 7;}
		int							columnCount(const QModelIndex &eltern=QModelIndex()) const Q_DECL_OVERRIDE {Q_UNUSED(eltern);return 6;}
		QVariant					data(const QModelIndex &index, int rolle=Qt::DisplayRole) const Q_DECL_OVERRIDE;
		QVariant					headerData(int auswahl, Qt::Orientation richtung, int rolle=Qt::DisplayRole) const Q_DECL_OVERRIDE;
		Qt::ItemFlags				flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

	public Q_SLOTS:
		void						KWgeaendert(int kw);

	private:
		int K_KW;
		QHash<QDate,Meldungstag>	K_Bereitschaftsmeldungen;
		void						DatenInitialisieren();
};

#endif // TMWOCHENABFRAGE_H
