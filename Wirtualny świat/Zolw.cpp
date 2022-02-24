#include "Zolw.h"



void Zolw::akcja()
{
	if (rand() % 4 == 0)
		this->Zwierze::akcja();
}

bool Zolw::czyOdbilAtak(Organizm* atakujacy) const
{
	if (atakujacy->getSila() < 5)
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" ma twarda skorupe...");
		return true;
	}
	else
	{
		return this->Organizm::czyOdbilAtak(atakujacy);
	}
}


Zolw::Zolw(int x, int y, Swiat& swiat) :
	Zwierze(x, y, swiat)
{
	this->setSymbol('Z');
	this->setSila(ZOLW_SILA);
	this->setInicjatywa(ZOLW_INICJATYWA);
}

Zolw::Zolw(const Zwierze* wzorzec, int x, int y) :
	Zwierze(wzorzec, x, y)
{
	this->setX(x);
	this->setY(y);
	this->setSila(ZOLW_SILA);
}

Zolw::~Zolw()
{}