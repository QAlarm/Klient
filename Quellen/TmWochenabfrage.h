#ifndef TMWOCHENABFRAGE_H
#define TMWOCHENABFRAGE_H

#include <QtCore>

#include "Meldungstag.h"

Q_DECLARE_LOGGING_CATEGORY(qalarm_klientTmWochenabfrage)
class TmWochenabfrage : public QAbstractTableModel
{
	Q_OBJECT
	public:
		explicit TmWochenabfrage(QObject *eltern=Q_NULLPTR);
		int						rowCount(const QModelIndex &eltern=QModelIndex()) const Q_DECL_OVERRIDE {Q_UNUSED(eltern);return 7;}
		int						columnCount(const QModelIndex &eltern=QModelIndex()) const Q_DECL_OVERRIDE {Q_UNUSED(eltern);return 6;}
		QVariant				data(const QModelIndex &index, int rolle=Qt::DisplayRole) const Q_DECL_OVERRIDE;
		QVariant				headerData(int auswahl, Qt::Orientation richtung, int rolle=Qt::DisplayRole) const Q_DECL_OVERRIDE;
		Qt::ItemFlags			flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
		bool					setData(const QModelIndex &index, const QVariant &wert, int rolle=Qt::EditRole) Q_DECL_OVERRIDE;
		const QJsonArray		Meldungen() const;
		QVector<QDate>			&Wochen() {return K_Wochenliste;}

	public Q_SLOTS:
		void						KWgeaendert(int kw);

	private:
		Q_DISABLE_COPY(TmWochenabfrage)
		int							K_KW;
		QVector<Meldungstag>		K_Bereitschaftsmeldungen;
		void						DatenInitialisieren();
		QVector<QDate>				K_Wochenliste;
};

#endif // TMWOCHENABFRAGE_H
