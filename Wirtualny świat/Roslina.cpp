#include <vector>
#include "Roslina.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

int Roslina::getSzansa() const
{
	return szansa;
}

void Roslina::setSzansa(int szansa)
{
	this->szansa = szansa;
}


bool Roslina::sprawdzSzanse()
{
	return rand() % 100 < this->szansa;
}


void Roslina::akcja()
{
	if (this->sprawdzSzanse())
		this->rozmnazanie();
}

AkcjaZwrotna Roslina::kolizja(Organizm* atakujacy)
{
	this->zabij();
	return AkcjaZwrotna::RUCH;
}


void Roslina::rozmnazanie()
{
	if (this->getSwiat().czyKomunikaty())
		this->wypowiedz(" rozsiewa sie.");

	int x = this->getX();
	int y = this->getY();
	int wynik, przesX, przesY;
	std::vector<Kierunek> pola = { Kierunek::N, Kierunek::S,
	Kierunek::W, Kierunek::E, Kierunek::NW, Kierunek::NE,
	Kierunek::SW, Kierunek::SE };

	while (!pola.empty())
	{
		wynik = rand() % pola.size();
		std::tie(przesX, przesY) = kierunekNaPrzesuniecie(pola[wynik]);

		if (this->getSwiat().sprawdzCzyWGranicach(x + przesX, y + przesY) &&
			this->getSwiat().sprawdzCzyPuste(x + przesX, y + przesY))
		{
			Organizm* narodzony;

			switch (this->getSymbol())
			{
			case 'T':
				narodzony = new Trawa(this, x + przesX, y + przesY);
				break;
			case 'M':
				narodzony = new Mlecz(this, x + przesX, y + przesY);
				break;
			case 'G':
				narodzony = new Guarana(this, x + przesX, y + przesY);
				break;
			case 'J':
				narodzony = new WilczeJagody(this, x + przesX, y + przesY);
				break;
			case 'B':
				narodzony = new BarszczSosnowskiego(this, x + przesX, y + przesY);
				break;
			default:
				narodzony = new Roslina(this, x + przesX, y + przesY);
				break;
			}

			this->getSwiat().dodajOrganizm(narodzony, x + przesX, y + przesY);
			break;
		}
		else
			pola.erase(pola.begin() + wynik);
	}
	pola.clear();
}


Roslina::Roslina(int x, int y, int szansa, Swiat& swiat) :
	Organizm(x, y, swiat)
{
	this->setSzansa(szansa);
	this->setInicjatywa(0);
}

Roslina::Roslina(const Roslina* wzorzec, int x, int y) :
	Organizm(wzorzec)
{
	this->setX(x);
	this->setY(y);
	this->setSzansa(wzorzec->szansa);
	this->setInicjatywa(0);
}

Roslina::~Roslina()
{}