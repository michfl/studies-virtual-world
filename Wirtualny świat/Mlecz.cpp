#include "Mlecz.h"

void Mlecz::akcja()
{
	for (int i = 0; i < 3; i++)
	{
		if (this->sprawdzSzanse())
		{
			this->rozmnazanie();
			break;
		}
	}
}


Mlecz::Mlecz(int x, int y, Swiat& swiat) :
	Roslina(x, y, MLECZ_SZANSA, swiat)
{
	this->setSymbol('M');
	this->setSila(MLECZ_SILA);
}

Mlecz::Mlecz(const Roslina* wzorzec, int x, int y) :
	Roslina(wzorzec, x, y)
{}

Mlecz::~Mlecz()
{}