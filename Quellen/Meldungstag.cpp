#include "Meldungstag.h"

Meldungstag::Meldungstag(const QDate &datum,const QTime &von,const QTime &bis,const bool &bereit,const bool &ganztaegig,const bool &gehaltsausfall)
{
	K_Datum=datum;
	K_Von=von;
	K_Bis=bis;
	K_Bereit=bereit;
	K_Ganztaegig=ganztaegig;
	K_Gehaltsausfall=gehaltsausfall;
}

Meldungstag::Meldungstag(const QDate &datum)
{
	K_Datum=datum;
	K_Ganztaegig=true;
	if((datum.dayOfWeek()==Qt::Saturday) || (datum.dayOfWeek()==Qt::Sunday))
		K_Gehaltsausfall=false;
	else
		K_Gehaltsausfall=true;
}

const QJsonObject Meldungstag::Datensatz() const
{
	QJsonObject Rueckgabe;

	Rueckgabe["date"]=K_Datum.toString(Qt::ISODate);
	Rueckgabe["full Day"]=K_Ganztaegig;
	Rueckgabe["salary loss"]=K_Gehaltsausfall;
	if(!K_Ganztaegig)
	{
		QJsonObject Verfuegbar;
		Verfuegbar["from"]=K_Von.toString(Qt::ISODate);
		Verfuegbar["to"]=K_Bis.toString(Qt::ISODate);
		Rueckgabe["available"]=Verfuegbar;
	}
	return Rueckgabe;
}

QDebug operator<<(QDebug dbg, const Meldungstag &tag)
{
	dbg.nospace()<<"Meldungstag(" << tag.Datensatz() << ")";
	return dbg.maybeSpace();
}
