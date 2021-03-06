#include "TmWochenabfrage.h"

/*
 * Datum|Dienstbereit|ganztags|Von|Bis|Verdienstausfall
 * Wenn kein Dientsbereit dann ist der Rest egal
 * Wenn gaztags, dann kein Von/Bis
 */
Q_LOGGING_CATEGORY(qalarm_klientTmWochenabfrage, "QAlarm Klient.TmWochenabfrage")
TmWochenabfrage::TmWochenabfrage(QObject *eltern) : QAbstractTableModel (eltern)
{
	QDate Heute=QDate::currentDate();
	//QDate Heute=QDate(2016,12,26);
	QDate ersteWoche=QDate(Heute.year(),1,4);
	int Jahr;
	Heute.weekNumber(&Jahr);
	if (Heute.year()>Jahr)
		ersteWoche=QDate(Heute.year()-1,1,4);
	K_Wochenliste<<ersteWoche;
	QDate Woche=ersteWoche;
	do
	{
		Woche=Woche.addDays(8-Woche.dayOfWeek());
		K_Wochenliste<<Woche;
	}
	while(Woche.year()==ersteWoche.year());
	if (K_Wochenliste.last().year()>ersteWoche.year())
		K_Wochenliste.removeLast();
}

QVariant TmWochenabfrage::data(const QModelIndex &index, int rolle) const
{
	QVariant Rueckgabe;
	QTime Zeit;
	switch(rolle)
	{
		case Qt::DisplayRole:
			switch (index.column())
			{
				case 0:
					//Datum Spalte
					Rueckgabe=K_Bereitschaftsmeldungen[index.row()].Datum().toString("dd.MM.yyyy");
					break;
					//Von Spalte
				case 3:
					Zeit=K_Bereitschaftsmeldungen[index.row()].Von();
					if (Zeit.isValid())
						Rueckgabe=Zeit.toString("hh:mm");
					else
						Rueckgabe=tr("ungültig");
					break;
					//Bis Spalte
				case 4:
					Zeit=K_Bereitschaftsmeldungen[index.row()].Bis();
					if (Zeit.isValid())
						Rueckgabe=Zeit.toString("hh:mm");
					else
						Rueckgabe=tr("ungültig");
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
						if(K_Bereitschaftsmeldungen[index.row()].Dientsbereit())
							Rueckgabe=Qt::Checked;
						else
							Rueckgabe=Qt::Unchecked;
						break;
					//Ganztags
					case 2:
						if(K_Bereitschaftsmeldungen[index.row()].Ganztags())
							Rueckgabe=Qt::Checked;
						else
							Rueckgabe=Qt::Unchecked;
						break;
						//Gehaltsausfall
					case 5:
						if(K_Bereitschaftsmeldungen[index.row()].Gehaltsausfall())
							Rueckgabe=Qt::Checked;
						else
							Rueckgabe=Qt::Unchecked;
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
	DatenInitialisieren();
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
			Rueckgabe=Qt::ItemIsUserCheckable|Qt::ItemIsEnabled;
			break;
		//Ganztags+Verdienstausfall kann nur geändert werden, wenn Dienstbereit
		case 2:
		case 5:
			if(data(this->index(index.row(),1),Qt::CheckStateRole).toInt()==Qt::Checked)
				Rueckgabe=Qt::ItemIsUserCheckable|Qt::ItemIsEnabled;
			else
				Rueckgabe=Qt::ItemIsUserCheckable;
			break;
		//Von + Bis kann nur geändert werden, wenn Dienstbereit + nicht ganztags
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

void TmWochenabfrage::DatenInitialisieren()
{
	K_Bereitschaftsmeldungen.clear();
	QDate Start=K_Wochenliste[K_KW-1];

	for(int Tag=0;Tag<7;Tag++)
	{
		QDate Neu=Start.addDays(Tag);
		K_Bereitschaftsmeldungen.append(Meldungstag(Neu));
	}
}

bool TmWochenabfrage::setData(const QModelIndex &index, const QVariant &wert, int rolle)
{
	bool Rueckgabe=false;
	QTime Zeit;
	if (index.isValid())
	{
		switch (rolle)
		{
			case Qt::CheckStateRole:
				switch(index.column())
				{
					//Bereit
					case 1:
						if (wert.toBool() != K_Bereitschaftsmeldungen[index.row()].Dientsbereit())
						{
							K_Bereitschaftsmeldungen[index.row()].DienstbereitSetzen(wert.toBool());
							//Es kann sich denn die ganze Spalte geändert haben.
							Q_EMIT dataChanged(index,this->index(index.row(),5));
							Rueckgabe=true;
						}
						break;
					//Ganztags
					case 2:
						if(wert.toBool() != K_Bereitschaftsmeldungen[index.row()].Ganztags())
						{
							K_Bereitschaftsmeldungen[index.row()].GanztaegigSetzen(wert.toBool());
							//Es können sich denn auch die von/bis Felder ändern
							Q_EMIT dataChanged(index,this->index(index.row(),4));
							Rueckgabe=true;
						}
						break;
					//Verdienstausfall
					case 5:
						if (wert.toBool() != K_Bereitschaftsmeldungen[index.row()].Gehaltsausfall())
						{
							K_Bereitschaftsmeldungen[index.row()].GehaltsausfallSetzen(wert.toBool());
							Q_EMIT dataChanged(index,index);
							Rueckgabe=true;
						}
						break;
					default:
						Rueckgabe=QAbstractTableModel::setData(index,wert,rolle);
						break;
				}
			break;
			case Qt::EditRole:
				switch (index.column())
				{
					//Von
					case 3:
						Zeit=QTime::fromString(wert.toString(),"h:m");
						if(Zeit.isValid())
						{
							if(Zeit!=K_Bereitschaftsmeldungen[index.row()].Von())
							{
								if(K_Bereitschaftsmeldungen[index.row()].Bis().isValid())
								{
									//Von muss vor Bis liegen
									if(Zeit<K_Bereitschaftsmeldungen[index.row()].Bis())
									{
										K_Bereitschaftsmeldungen[index.row()].VonSetzen(Zeit);
										Q_EMIT dataChanged(index,index);
										Rueckgabe=true;
									}
								}
								else
								{
									K_Bereitschaftsmeldungen[index.row()].VonSetzen(Zeit);
									Q_EMIT dataChanged(index,index);
									Rueckgabe=true;
								}
							}
						}
						break;
					//Bis
					case 4:
						Zeit=QTime::fromString(wert.toString(),"h:m");
						if(Zeit.isValid())
						{
							if(Zeit!=K_Bereitschaftsmeldungen[index.row()].Bis())
							{
								if(K_Bereitschaftsmeldungen[index.row()].Von().isValid())
								{
									//Bis muss nach Vor liegen
									if(Zeit>K_Bereitschaftsmeldungen[index.row()].Von())
									{
										K_Bereitschaftsmeldungen[index.row()].BisSetzen(Zeit);
										Q_EMIT dataChanged(index,index);
										Rueckgabe=true;
									}
								}
								else
								{
									K_Bereitschaftsmeldungen[index.row()].BisSetzen(Zeit);
									Q_EMIT dataChanged(index,index);
									Rueckgabe=true;
								}
							}
						}
						break;
					default:
						Rueckgabe=QAbstractTableModel::setData(index,wert,rolle);
						break;
				}
				break;
			default:
				Rueckgabe=QAbstractTableModel::setData(index,wert,rolle);
				break;
		}
		return Rueckgabe;
	}
	return QAbstractTableModel::setData(index,wert,rolle);
}

const QJsonArray TmWochenabfrage::Meldungen() const
{
	QJsonArray Rueckgabe;
	for(auto Tag:K_Bereitschaftsmeldungen)
		Rueckgabe.append(Tag.Datensatz());
	return Rueckgabe;
}
