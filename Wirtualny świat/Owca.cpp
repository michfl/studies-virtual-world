#include "Owca.h"

Owca::Owca(int x, int y, Swiat& swiat) :
	Zwierze(x, y, swiat)
{
	this->setSymbol('O');
	this->setSila(OWCA_SILA);
	this->setInicjatywa(OWCA_INICJATYWA);
}

Owca::Owca(const Zwierze* wzorzec, int x, int y) :
	Zwierze(wzorzec, x, y)
{
	this->setX(x);
	this->setY(y);
	this->setSila(OWCA_SILA);
}

Owca::~Owca()
{}