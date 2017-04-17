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
	private:
		static const int		K_Basisfunktionen=3;
		int						K_AnzahlDerFunktionen;
		QVector<QStringList>	K_Funktionsliste;
};

#endif // LMFUNKTIONSAUSWAHL_H
