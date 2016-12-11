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
		const bool	&Dientsbereit() const {return  K_Bereit;}
		const bool	&Ganztags() const {return K_Ganztaegig;}
		const bool	&Gehaltsausfall() const {return K_Gehaltsausfall;}

		void		DienstbereitSetzen(const bool &bereit) {K_Bereit=bereit;}
		void		GanztaegigSetzen(const bool &ganztags) {K_Ganztaegig=ganztags;}
		void		Gehaltsausfall(const bool &ausfall) {K_Gehaltsausfall=ausfall;}
	private:
		QDate		K_Datum;
		QTime		K_Von;
		QTime		K_Bis;
		bool		K_Bereit;
		bool		K_Ganztaegig;
		bool		K_Gehaltsausfall;
};

#endif // MELDUNGSTAG_H
