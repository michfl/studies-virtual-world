#include <vector>
#include "Lis.h"

std::tuple<int, int> Lis::ustalPozycje()
{
	int x = this->getX();
	int y = this->getY();
	int wynik, przesX, przesY;
	std::vector<Kierunek> pola = { Kierunek::N, Kierunek::S,
	Kierunek::W, Kierunek::E };

	while (!pola.empty())
	{
		wynik = rand() % pola.size();
		std::tie(przesX, przesY) = kierunekNaPrzesuniecie(pola[wynik]);

		if (this->getSwiat().sprawdzCzyWGranicach(x + przesX, y + przesY))
		{
			if (this->getSwiat().sprawdzCzyPuste(x + przesX, y + przesY))
			{
				pola.clear();
				return { x + przesX, y + przesY };
			}
			else if (this->getSila() >= this->getSwiat()[x + przesX][y + przesY]->getSila())
			{
				if (this->getSwiat().czyKomunikaty())
					this->wypowiedz(" zweszyl ofiare...");

				pola.clear();
				return { x + przesX, y + przesY };
			}
			else
				pola.erase(pola.begin() + wynik);
		}
		else
			pola.erase(pola.begin() + wynik);
	}
	pola.clear();
	return { x, y };
}


Lis::Lis(int x, int y, Swiat& swiat) :
	Zwierze(x, y, swiat)
{
	this->setSymbol('L');
	this->setSila(LIS_SILA);
	this->setInicjatywa(LIS_INICJATYWA);
}

Lis::Lis(const Zwierze* wzorzec, int x, int y) :
	Zwierze(wzorzec, x, y)
{
	this->setX(x);
	this->setY(y);
	this->setSila(LIS_SILA);
}

Lis::~Lis()
{}