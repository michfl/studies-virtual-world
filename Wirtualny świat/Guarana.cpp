#include "Guarana.h"

AkcjaZwrotna Guarana::kolizja(Organizm* atakujacy)
{
	this->zabij();
	atakujacy->setSila(atakujacy->getSila() + 3);
	return AkcjaZwrotna::RUCH;
}


Guarana::Guarana(int x, int y, Swiat& swiat) :
	Roslina(x, y, GUARANA_SZANSA, swiat)
{
	this->setSymbol('G');
	this->setSila(GUARANA_SILA);
}

Guarana::Guarana(const Roslina* wzorzec, int x, int y) :
	Roslina(wzorzec, x, y)
{}

Guarana::~Guarana()
{}