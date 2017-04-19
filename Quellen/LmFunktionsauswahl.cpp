#include "LmFunktionsauswahl.h"

#include <QtGui>

Q_LOGGING_CATEGORY(qalarm_klientLmFunktionsauswahl, "QAlarm Klient.LmFunktionsauswahl")
LmFunktionsauswahl::LmFunktionsauswahl(QObject *eltern) : QAbstractListModel (eltern)
{
	K_AnzahlDerFunktionen=K_Basisfunktionen;
	K_Funktionen.append("Abmelden");
	K_Funktionen.append("Beenden");
	K_Funktionsliste.append(QStringList()<<tr("Abmelden")<<"Abmelden.png"<<"Abmelden");
	K_Funktionsliste.append(QStringList()<<tr("Beenden")<<"Beenden.png"<<"Beenden");
}

QVariant LmFunktionsauswahl::data(const QModelIndex &index, int rolle) const
{
	QVariant Rueckgabe;
	switch (rolle)
	{
		case Qt::DisplayRole:
			Rueckgabe=K_Funktionsliste[index.row()][0];
			break;
		case Qt::DecorationRole:
				Rueckgabe=QIcon(QString(":/Bilder/%1").arg(K_Funktionsliste[index.row()][1]));
			break;
		default:
			Rueckgabe=QVariant();
			break;
	}
	return Rueckgabe;
}

void LmFunktionsauswahl::FunktionEinfuegen(const QString &name, const QString &bild, const QString &einsprung)
{
	if (K_Funktionen.contains(einsprung))
			return;
	K_Funktionen.append(einsprung);
	beginInsertRows(index(0,0),0,0);
	K_Funktionsliste.prepend(QStringList()<<name<<bild<<einsprung);
	K_AnzahlDerFunktionen++;
	endInsertRows();
}
