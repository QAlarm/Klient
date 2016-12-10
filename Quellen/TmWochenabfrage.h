#ifndef TMWOCHENABFRAGE_H
#define TMWOCHENABFRAGE_H

#include <QtCore>

class TmWochenabfrage : public QAbstractTableModel
{
	public:
		TmWochenabfrage(QObject *eltern=Q_NULLPTR);
		int rowCount(const QModelIndex &eltern=QModelIndex()) const Q_DECL_OVERRIDE {return 7;}
		int columnCount(const QModelIndex &eltern=QModelIndex()) const Q_DECL_OVERRIDE {return 6;}
		QVariant data(const QModelIndex &index, int rolle=Qt::DisplayRole) const Q_DECL_OVERRIDE;
		QVariant headerData(int auswahl, Qt::Orientation richtung, int rolle=Qt::DisplayRole) const Q_DECL_OVERRIDE;
};

#endif // TMWOCHENABFRAGE_H
