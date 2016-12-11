#ifndef MELDUNGSTAG_H
#define MELDUNGSTAG_H

#include <QtCore>
class Meldungstag
{
	public:
		Meldungstag(const QDate &datum,const QTime &von,const QTime &bis,const bool &bereit,const bool &ganztaegig,const bool &gehaltsausfall)
		{
			K_Datum=datum;
			K_Von=von;
			K_Bis=bis;
			K_Bereit=bereit;
			K_Ganztaegig=ganztaegig;
			K_Gehaltsausfall=gehaltsausfall;
		}
	private:
		QDate	K_Datum;
		QTime	K_Von;
		QTime	K_Bis;
		bool	K_Bereit;
		bool	K_Ganztaegig;
		bool	K_Gehaltsausfall;
};

#endif // MELDUNGSTAG_H
