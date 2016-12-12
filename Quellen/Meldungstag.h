#ifndef MELDUNGSTAG_H
#define MELDUNGSTAG_H

#include <QtCore>
class Meldungstag
{
	public:
		Meldungstag(){};
		Meldungstag(const QDate &datum,const QTime &von,const QTime &bis,const bool &bereit,const bool &ganztaegig,const bool &gehaltsausfall)
		{
			K_Datum=datum;
			K_Von=von;
			K_Bis=bis;
			K_Bereit=bereit;
			K_Ganztaegig=ganztaegig;
			K_Gehaltsausfall=gehaltsausfall;
		}
		Meldungstag(const QDate &datum)
		{
			K_Datum=datum;
			K_Ganztaegig=true;
			if((datum.dayOfWeek()==Qt::Saturday) || (datum.dayOfWeek()==Qt::Sunday))
				K_Gehaltsausfall=false;
			else
				K_Gehaltsausfall=true;
		}
		const bool			&Dientsbereit() const {return  K_Bereit;}
		const bool			&Ganztags() const {return K_Ganztaegig;}
		const bool			&Gehaltsausfall() const {return K_Gehaltsausfall;}
		const QDate			&Datum() const {return K_Datum;}
		const QTime			&Von() const {return K_Von;}
		const QTime			&Bis() const {return K_Bis;}
		const QByteArray	Datensatz(const bool &kompakt=true) const {
								QJsonDocument Rueckgabe;
								QJsonDocument::JsonFormat Format=QJsonDocument::Compact;
								if(!kompakt)
									Format=QJsonDocument::Indented;
								return Rueckgabe.toJson(Format);
							}

		void				DienstbereitSetzen(const bool &bereit) {K_Bereit=bereit;}
		void				GanztaegigSetzen(const bool &ganztags) {K_Ganztaegig=ganztags;}
		void				GehaltsausfallSetzen(const bool &ausfall) {K_Gehaltsausfall=ausfall;}
		void				VonSetzen(const QTime &von) {K_Von=von;}
		void				BisSetzen(const QTime &bis) {K_Bis=bis;}

	private:
		QDate				K_Datum;
		QTime				K_Von;
		QTime				K_Bis;
		bool				K_Bereit;
		bool				K_Ganztaegig;
		bool				K_Gehaltsausfall;
};

#endif // MELDUNGSTAG_H
