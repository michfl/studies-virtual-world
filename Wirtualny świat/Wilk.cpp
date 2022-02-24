#include "Wilk.h"

Wilk::Wilk(int x, int y, Swiat& swiat) :
	Zwierze(x, y, swiat)
{
	this->setSymbol('W');
	this->setSila(WILK_SILA);
	this->setInicjatywa(WILK_INICJATYWA);
}

Wilk::Wilk(const Zwierze* wzorzec, int x, int y) :
	Zwierze(wzorzec, x, y)
{
	this->setX(x);
	this->setY(y);
	this->setSila(WILK_SILA);
}

Wilk::~Wilk()
{}