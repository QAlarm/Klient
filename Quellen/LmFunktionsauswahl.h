#ifndef LMFUNKTIONSAUSWAHL_H
#define LMFUNKTIONSAUSWAHL_H

#include <QtCore>

Q_DECLARE_LOGGING_CATEGORY(qalarm_klientLmFunktionsauswahl)
class LmFunktionsauswahl : public QAbstractListModel
{
	Q_OBJECT
	public:
		explicit LmFunktionsauswahl(QObject *eltern=Q_NULLPTR);
		int						rowCount(const QModelIndex &eltern=QModelIndex()) const Q_DECL_OVERRIDE {Q_UNUSED(eltern);return K_AnzahlDerFunktionen;}
		QVariant				data(const QModelIndex &index, int rolle=Qt::DisplayRole) const Q_DECL_OVERRIDE;
		void					FunktionEinfuegen(const QString &name, const QString &bild, const QString &einsprung);
		const QString			&Einsprung(const QModelIndex &index) const { return K_Funktionsliste[index.row()][2];}

	private:
		static const int		K_Basisfunktionen=2;
		int						K_AnzahlDerFunktionen;
		QVector<QStringList>	K_Funktionsliste;
};

#endif // LMFUNKTIONSAUSWAHL_H
