#include <cstdlib>
#include <vector>
#include "Zwierze.h"

#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

Zwierze::Zwierze(int x, int y, Swiat& swiat):
	Organizm(x, y, swiat)
{}

Zwierze::Zwierze(const Zwierze* wzorzec, int x, int y) :
	Organizm(wzorzec)
{
	this->setX(x);
	this->setY(y);
}

Zwierze::~Zwierze()
{}


bool Zwierze::ucieczka()
{
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
			this->getSwiat().ruch(this, x + przesX, y + przesY);
			this->setX(x + przesX);
			this->setY(y + przesY);

			if (this->getSwiat().czyKomunikaty())
				this->wypowiedz(" ucieka...");
			return true;
		}
		else
			pola.erase(pola.begin() + wynik);
	}
	pola.clear();

	if (this->getSwiat().czyKomunikaty())
		this->wypowiedz(" nie daje rady uciec...");
	return false;
}

void Zwierze::rozmnazanie()
{
	if (this->getSwiat().czyKomunikaty())
		this->wypowiedz(" rozmnaza sie.");

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
			case 'W':
				narodzony = new Wilk(this, x + przesX, y + przesY);
				break;
			case 'O':
				narodzony = new Owca(this, x + przesX, y + przesY);
				break;
			case 'L':
				narodzony = new Lis(this, x + przesX, y + przesY);
				break;
			case 'Z':
				narodzony = new Zolw(this, x + przesX, y + przesY);
				break;
			case 'A':
				narodzony = new Antylopa(this, x + przesX, y + przesY);
				break;
			default:
				narodzony = new Zwierze(this, x + przesX, y + przesY);
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


std::tuple<int, int> Zwierze::ustalPozycje()
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
			pola.clear();
			return { x + przesX, y + przesY };
		}
		else
			pola.erase(pola.begin() + wynik);
	}
	pola.clear();
	return { x, y };
}

AkcjaZwrotna Zwierze::kolizja(Organizm* atakujacy)
{
	if (this->getSymbol() == atakujacy->getSymbol())
	{
		this->rozmnazanie();
		return AkcjaZwrotna::STOJ;
	}

	if (this->czyOdbilAtak(atakujacy))
	{
		atakujacy->zabij();
		return AkcjaZwrotna::STOJ;
	}
	else
	{
		this->zabij();
		return AkcjaZwrotna::RUCH;
	}
}

void Zwierze::akcja()
{
	int noweX, noweY;
	std::tie(noweX, noweY) = this->ustalPozycje();
	if (noweX == this->getX() && noweY == this->getY())
		return;

	if (this->getSwiat().sprawdzCzyPuste(noweX, noweY))
	{
		this->getSwiat().ruch(this, noweX, noweY);
		this->setX(noweX);
		this->setY(noweY);
	}
	else
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" atakuje...");

		switch (this->getSwiat()[noweX][noweY]->kolizja(this))
		{
		case AkcjaZwrotna::RUCH:
			this->getSwiat().ruch(this, noweX, noweY);
			this->setX(noweX);
			this->setY(noweY);
			break;
		case AkcjaZwrotna::STOJ:
			break;
		}
	}
}