#include "LmFunktionsauswahl.h"

#include <QtGui>

Q_LOGGING_CATEGORY(qalarm_klientLmFunktionsauswahl, "QAlarm Klient.LmFunktionsauswahl")
LmFunktionsauswahl::LmFunktionsauswahl(QObject *eltern) : QAbstractListModel (eltern)
{
	K_AnzahlDerFunktionen=K_Basisfunktionen;
	K_Funktionsliste.append(QStringList()<<tr("Abmelden")<<"Abmelden.png");
	K_Funktionsliste.append(QStringList()<<tr("Einstellungen")<<"Einstellungen.png");
	K_Funktionsliste.append(QStringList()<<tr("Beenden")<<"Beenden.png");
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

void LmFunktionsauswahl::FunktionEinfuegen(const QString &name, const QString &bild)
{
	beginInsertRows(index(0,0),0,0);
	K_Funktionsliste.prepend(QStringList()<<name<<bild);
	K_AnzahlDerFunktionen++;
	endInsertRows();
}
