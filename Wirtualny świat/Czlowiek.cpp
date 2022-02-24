#include <iostream>
#include "Czlowiek.h"

void Czlowiek::akcja(Kierunek kierunek, bool umiejetnosc)
{
	this->aktualizujCzas();

	if (umiejetnosc)
		this->wlaczNiesmiertelnosc();

	int x = this->getX();
	int y = this->getY();
	int przesX, przesY;
	std::tie(przesX, przesY) = this->kierunekNaPrzesuniecie(kierunek);
	if (!this->getSwiat().sprawdzCzyWGranicach(x + przesX, y + przesY))
		return;

	if (this->getSwiat().sprawdzCzyPuste(x + przesX, y + przesY))
	{
		this->getSwiat().ruch(this, x + przesX, y + przesY);
		this->setX(x + przesX);
		this->setY(y + przesY);
	}
	else
	{
		if (this->czyNiesmiertelny())
		{
			if (this->getSwiat()[x + przesX][y + przesY]->getSila() > this->getSila())
			{
				if (this->getSwiat().czyKomunikaty())
					this->wypowiedz(" unika smierci.");
				return;
			}
		}
		switch (this->getSwiat()[x + przesX][y + przesY]->kolizja(this))
		{
		case AkcjaZwrotna::RUCH:
			this->getSwiat().ruch(this, x + przesX, y + przesY);
			this->setX(x + przesX);
			this->setY(y + przesY);
			break;
		case AkcjaZwrotna::STOJ:
			break;
		}
	}
}

AkcjaZwrotna Czlowiek::kolizja(Organizm* atakujacy)
{
	if (this->czyOdbilAtak(atakujacy))
	{
		atakujacy->zabij();
		return AkcjaZwrotna::STOJ;
	}
	else
	{
		if (this->czyNiesmiertelny())
		{
			if (this->ucieczka())
				return AkcjaZwrotna::RUCH;
			else
				return AkcjaZwrotna::STOJ;
		}
		else
		{
			this->zabij();
			return AkcjaZwrotna::RUCH;
		}
	}
}


void Czlowiek::zabij()
{
	this->Organizm::zabij();
}

bool Czlowiek::czyNiesmiertelny() const
{
	return niesmiertelnosc;
}

void Czlowiek::wlaczNiesmiertelnosc()
{
	if (this->czasAktywacji == 0)
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" czuje wstepujaca w siebie moc...");

		this->niesmiertelnosc = true;
		this->czasAktywacji = 1;
	}
}

void Czlowiek::aktualizujCzas()
{
	if (this->czasAktywacji == 0)
		return;

	if (this->czasAktywacji > 0)
		this->czasAktywacji++;
	else
		this->czasAktywacji--;

	if (this->czasAktywacji > CZLOWIEK_CZAS_UMIEJETNOSCI)
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" nie czuje sie juz tak dobrze jak kiedys...");

		this->niesmiertelnosc = false;
		this->czasAktywacji = -1;
		return;
	}

	if (this->czasAktywacji < -(CZLOWIEK_CZAS_UMIEJETNOSCI))
	{
		this->czasAktywacji = 0;
		return;
	}
}


int Czlowiek::getCzasOdnowienia() const
{
	if (this->czasAktywacji < 0)
		return this->czasAktywacji + CZLOWIEK_CZAS_UMIEJETNOSCI;
	else
		return 0;
}

int Czlowiek::getCzasAktywacji() const
{
	return this->czasAktywacji;
}


void Czlowiek::setUmiejetnosc(bool stan)
{
	this->niesmiertelnosc = stan;
}

void Czlowiek::setCzasAktywacji(int czas)
{
	this->czasAktywacji = czas;
}


Czlowiek::Czlowiek(int x, int y, Swiat& swiat) :
	Zwierze(x, y, swiat)
{
	this->niesmiertelnosc = false;
	this->czasAktywacji = 0;
	this->setSymbol('@');
	this->setSila(CZLOWIEK_SILA);
	this->setInicjatywa(CZLOWIEK_INICJATYWA);
}

Czlowiek::~Czlowiek()
{}