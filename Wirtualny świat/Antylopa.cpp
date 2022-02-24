#include <vector>
#include "Antylopa.h"

AkcjaZwrotna Antylopa::kolizja(Organizm* atakujacy)
{
	if (this->getSymbol() == atakujacy->getSymbol())
	{
		this->rozmnazanie();
		return AkcjaZwrotna::STOJ;
	}

	if (rand() % 2 == 0)
	{
		if (this->ucieczka())
			return AkcjaZwrotna::RUCH;
		else
		{
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
	}
	else
	{
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
}

void Antylopa::akcja()
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
		this->Zwierze::akcja();
	}
	else
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" na cos wskoczyla...");

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


Antylopa::Antylopa(int x, int y, Swiat& swiat) :
	Zwierze(x, y, swiat)
{
	this->setSymbol('A');
	this->setSila(ANTYLOPA_SILA);
	this->setInicjatywa(ANTYLOPA_INICJATYWA);
}

Antylopa::Antylopa(const Zwierze* wzorzec, int x, int y) :
	Zwierze(wzorzec, x, y)
{
	this->setX(x);
	this->setY(y);
	this->setSila(ANTYLOPA_SILA);
}

Antylopa::~Antylopa()
{}