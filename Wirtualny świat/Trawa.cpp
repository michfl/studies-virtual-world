#include "Trawa.h"

Trawa::Trawa(int x, int y, Swiat& swiat) :
	Roslina(x, y, TRAWA_SZANSA, swiat)
{
	this->setSymbol('T');
	this->setSila(TRAWA_SILA);
}

Trawa::Trawa(const Roslina* wzorzec, int x, int y) :
	Roslina(wzorzec, x, y)
{}

Trawa::~Trawa()
{}