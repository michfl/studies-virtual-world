#include "BarszczSosnowskiego.h"
#include "Czlowiek.h"

void BarszczSosnowskiego::akcja()
{
	if (this->sprawdzSzanse())
		this->rozmnazanie();

	for (int x = this->getX() - 1; x <= this->getX() + 1; x++)
	{
		for (int y = this->getY() - 1; y <= this->getY() + 1; y++)
		{
			if (this->getSwiat().sprawdzCzyWGranicach(x, y))
			{
				if (!this->getSwiat().sprawdzCzyPuste(x, y) &&
					this->getSwiat()[x][y]->getInicjatywa() != 0)
				{
					if (this->getSwiat()[x][y]->getSymbol() == '@')
						if (this->getSwiat().czyGlobalnaUmiejetnosc())
							return;

					this->getSwiat()[x][y]->zabij();

					if (this->getSwiat().czyKomunikaty())
						this->wypowiedz(" zbiera zniwo...");
				}
			}
		}
	}
}

AkcjaZwrotna BarszczSosnowskiego::kolizja(Organizm* atakujacy)
{
	this->zabij();
	atakujacy->zabij();
	return AkcjaZwrotna::STOJ;
}


BarszczSosnowskiego::BarszczSosnowskiego(int x, int y, Swiat& swiat) :
	Roslina(x, y, BARSZCZ_SOSNOWSKIEGO_SZANSA, swiat)
{
	this->setSymbol('B');
	this->setSila(BARSZCZ_SOSNOWSKIEGO_SILA);
}

BarszczSosnowskiego::BarszczSosnowskiego(const Roslina* wzorzec, int x, int y) :
	Roslina(wzorzec, x, y)
{}

BarszczSosnowskiego::~BarszczSosnowskiego()
{}