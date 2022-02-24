#include "WilczeJagody.h"

AkcjaZwrotna WilczeJagody::kolizja(Organizm* atakujacy)
{
	if (this->getSwiat().czyKomunikaty())
		this->wypowiedz(" sa trujace...");

	this->zabij();
	atakujacy->zabij();
	return AkcjaZwrotna::STOJ;
}


WilczeJagody::WilczeJagody(int x, int y, Swiat& swiat) :
	Roslina(x, y, WILCZE_JAGODY_SZANSA, swiat)
{
	this->setSymbol('J');
	this->setSila(WILCZE_JAGODY_SILA);
}

WilczeJagody::WilczeJagody(const Roslina* wzorzec, int x, int y) :
	Roslina(wzorzec, x, y)
{}

WilczeJagody::~WilczeJagody()
{}