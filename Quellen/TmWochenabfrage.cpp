#include "TmWochenabfrage.h"

/*
 * Datum|Dienstbereit|ganztags|Von|Bis|Verdienstausfall
 * Wenn kein Dientsbereit dann ist der Rest egal
 * Wenn gaztags, dann kein Von/Bis
 */

TmWochenabfrage::TmWochenabfrage(QObject *eltern) : QAbstractTableModel (eltern)
{

}

QVariant TmWochenabfrage::data(const QModelIndex &index, int rolle) const
{
	QVariant Rueckgabe;
	switch(rolle)
	{
		case Qt::DisplayRole:
			switch (index.column())
			{
				case 0:
					//Datum Spalte
					Rueckgabe= QDate::currentDate().addDays(index.row()).toString("dd.MM.yyyy");
					break;
					//Von Spalte
				case 3:
					Rueckgabe=QTime::currentTime().toString("HH:mm");
					break;
					//Bis Spalte
				case 4:
					Rueckgabe=QTime::currentTime().toString("HH:mm");
					break;
			}
			break;
		case Qt::CheckStateRole:
			if((index.column()==1) || (index.column()==2) || (index.column()==5))
			{
				switch (index.column())
				{
					//Dienstbereit
					case 1:
						//FIXME zum testen
						if(index.row()%2)
							Rueckgabe=Qt::Checked;
						else
							Rueckgabe=Qt::Unchecked;
						break;
					//Ganztags
					case 2:
						//FIXME zum testen
						if(index.row()%2)
							Rueckgabe=Qt::Unchecked;
						else
							Rueckgabe=Qt::Checked;
						break;
					default:
						Rueckgabe=Qt::Checked;
						break;
				}
			}
			break;
		default:
			Rueckgabe=QVariant();
			break;
	}
	return Rueckgabe;
}

QVariant TmWochenabfrage::headerData(int auswahl, Qt::Orientation richtung, int rolle) const
{
	QVariant Rueckgabe;
	if (richtung==Qt::Vertical)
		return QAbstractTableModel::headerData(auswahl,richtung,rolle);
	if (richtung==Qt::Horizontal)
	{
		switch (rolle)
		{
			case Qt::DisplayRole:
				switch (auswahl)
				{
					case 1:
						Rueckgabe=tr("Dienstbereit");
						break;
					case 0:
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
				break;
			default:
				Rueckgabe=QAbstractTableModel::headerData(auswahl,richtung,rolle);
				break;
		}
	}
	else
		Rueckgabe=QAbstractTableModel::headerData(auswahl,richtung,rolle);
	return Rueckgabe;
}

void TmWochenabfrage::KWgeaendert(int kw)
{
	QVector<int> Rollen;
	Rollen<<Qt::DisplayRole;

	K_KW=kw;
	Q_EMIT dataChanged(index(0,0),index(6,5),Rollen);
}

Qt::ItemFlags TmWochenabfrage::flags(const QModelIndex &index) const
{
	Qt::ItemFlags Rueckgabe;
	//Dienstbereit kann immer geändert werden.
	switch(index.column())
	{
		//Dienstbereit kann immer geändert werden.
		case 1:
			Rueckgabe=Qt::ItemIsUserCheckable|Qt::ItemIsEditable|Qt::ItemIsEnabled;
			break;
		//Ganztags+Verdienstausfall kann nur geändert werden, wenn Dienstbereit
		case 2:
		case 5:
			if(data(this->index(index.row(),1),Qt::CheckStateRole).toInt()==Qt::Checked)
				Rueckgabe=Qt::ItemIsUserCheckable|Qt::ItemIsEditable|Qt::ItemIsEnabled;
			else
				Rueckgabe=Qt::ItemIsUserCheckable|Qt::ItemIsEditable;
			break;
		//Von + Bis kann nur geändert werden, wenn Dienstbereit+ Nicht ganztags
		case 3:
		case 4:
			if((data(this->index(index.row(),1),Qt::CheckStateRole).toInt()==Qt::Checked) &&
			   (data(this->index(index.row(),2),Qt::CheckStateRole).toInt()==Qt::Unchecked))
				Rueckgabe=Qt::ItemIsEditable|Qt::ItemIsEnabled;
			else
				Rueckgabe=Qt::ItemIsEditable;
			break;
		default:
			Rueckgabe=QAbstractTableModel::flags(index);
			break;

	}
	return Rueckgabe;
}
