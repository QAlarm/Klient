#include "TmWochenabfrage.h"

/*
 * Dienstbereit|Datum|ganztags|Von|Bis|Verdienstausfall
 * Wenn kein Dientsbereit dann ist der Rest egal
 * Wenn gaztags, dann kein Von/Bis
 */

TmWochenabfrage::TmWochenabfrage(QObject *eltern) : QAbstractTableModel (eltern)
{

}

QVariant TmWochenabfrage::data(const QModelIndex &index, int rolle) const
{
	return QVariant();
}

QVariant TmWochenabfrage::headerData(int auswahl, Qt::Orientation richtung, int rolle) const
{
	QVariant Rueckgabe;
	if (richtung==Qt::Vertical)
		return QAbstractTableModel::headerData(auswahl,richtung,rolle);
	if ((richtung==Qt::Horizontal) && (rolle!=Qt::DisplayRole))
		return QAbstractTableModel::headerData(auswahl,richtung,rolle);
	switch (auswahl)
	{
		case 0:
			Rueckgabe=tr("Dienstbereit");
			break;
		case 1:
			Rueckgabe=tr("Datum");
			break;
		case 2:
			Rueckgabe=tr("ganztags");
			break;
		case 3:
			Rueckgabe=tr("Von");
			break;
		case 4:
			Rueckgabe=tr("Bis");
			break;
		case 5:
			Rueckgabe=tr("Verdienstausfall");
			break;
		default:
			break;
	}
	return Rueckgabe;
}
