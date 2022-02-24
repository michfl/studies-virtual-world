#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Swiat.h"
#include "KomparatorOrganizmow.h"

#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Czlowiek.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

#define PROBY 100

#define LICZBA_WILKOW 5
#define LICZBA_OWIEC 15
#define LICZBA_LISOW 15
#define LICZBA_ZOLWI 5
#define LICZBA_ANTYLOP 3

#define LICZBA_TRAW 2
#define LICZBA_MLECZY 1
#define LICZBA_GUARAN 3
#define LICZBA_WILCZYCH_JAGOD 5
#define LICZBA_BARSZCZY_SOSNOWSKIEGO 6

Organizm** Swiat::operator[](int x)
{
	return organizmy[x];
}


int Swiat::getRozmiarN() const
{
	return rozmiarN;
}

int Swiat::getRozmiarM() const
{
	return rozmiarM;
}


bool Swiat::wykonajTure(Kierunek kierunek, bool umiejetnosc)
{
	if (!this->czyGraTrwa())
		return false;

	std::priority_queue<Organizm*, std::vector<Organizm*>,
	KomparatorOrganizmow> kolejkaAkcji;

	for (int x = 0; x < rozmiarN; x++)
	{
		for (int y = 0; y < rozmiarM; y++)
		{
			if (organizmy[x][y] != nullptr)
			{
				if (organizmy[x][y]->czyZyje())
					kolejkaAkcji.push(organizmy[x][y]);
				else
				{
					delete organizmy[x][y];
					organizmy[x][y] = nullptr;
				}
			}
		}
	}

	while (!kolejkaAkcji.empty())
	{
		if (kolejkaAkcji.top()->czyZyje())
		{
			kolejkaAkcji.top()->zwiekszWiek();

			if (kolejkaAkcji.top()->getSymbol() == '@')
				kolejkaAkcji.top()->akcja(kierunek, umiejetnosc);
			else
				kolejkaAkcji.top()->akcja();
		}
		kolejkaAkcji.pop();
	}

	while (!doUsuniecia.empty())
	{
		if (doUsuniecia.top()->getSymbol() == '@')
			return false;
		delete doUsuniecia.top();
		doUsuniecia.pop();
	}

	return true;
}

void Swiat::rysujSwiat()
{
	for (int y = rozmiarM - 1; y >= 0; y--)
	{
		std::cout << "| ";
		for (int x = 0; x < rozmiarN; x++)
		{
			if (organizmy[x][y] != nullptr)
			{
				if (organizmy[x][y]->czyZyje())
				{
					organizmy[x][y]->rysowanie();
					std::cout << " ";
				}
				else
					std::cout << ". ";
			}
			else
				std::cout << ". ";
		}
		std::cout << "|\n";
	}
}


bool Swiat::sprawdzCzyWGranicach(int x, int y) const
{
	if (x >= 0 && y >= 0 &&
		x < rozmiarN && y < rozmiarM)
	{
		return true;
	}
	return false;
}

bool Swiat::sprawdzCzyPuste(int x, int y) const
{
	return (organizmy[x][y] == nullptr || !organizmy[x][y]->czyZyje());
}


void Swiat::doKolejkiUsuwania(Organizm* organizm)
{
	this->doUsuniecia.push(organizm);
}


void Swiat::ruch(Organizm* organizm, int x, int y)
{
	if (organizmy[x][y] != nullptr)
	{
		if (!organizmy[x][y]->czyZyje())
		{
			doUsuniecia.push(organizmy[x][y]);
			organizmy[x][y] = organizm;
			organizmy[organizm->getX()][organizm->getY()] = nullptr;
		}
	}
	else
	{
		organizmy[x][y] = organizm;
		organizmy[organizm->getX()][organizm->getY()] = nullptr;
	}
}

void Swiat::dodajOrganizm(Organizm* organizm, int x, int y)
{
	if (organizmy[x][y] != nullptr)
		doUsuniecia.push(organizmy[x][y]);
	organizmy[x][y] = organizm;
}

void Swiat::dodajOrganizm(char znak, int x, int y)
{
	switch (znak)
	{
	case 'W':
		organizmy[x][y] = new Wilk(x, y, *this);
		break;
	case 'O':
		organizmy[x][y] = new Owca(x, y, *this);
		break;
	case 'L':
		organizmy[x][y] = new Lis(x, y, *this);
		break;
	case 'Z':
		organizmy[x][y] = new Zolw(x, y, *this);
		break;
	case 'A':
		organizmy[x][y] = new Antylopa(x, y, *this);
		break;
	case 'T':
		organizmy[x][y] = new Trawa(x, y, *this);
		break;
	case 'M':
		organizmy[x][y] = new Mlecz(x, y, *this);
		break;
	case 'G':
		organizmy[x][y] = new Guarana(x, y, *this);
		break;
	case 'J':
		organizmy[x][y] = new WilczeJagody(x, y, *this);
		break;
	case 'B':
		organizmy[x][y] = new BarszczSosnowskiego(x, y, *this);
		break;
	default:
		break;
	}
}

void Swiat::dodajLosowo(Org organizm, int ilosc, int proby)
{
	for (int i = 0; i < ilosc; i++)
	{
		for (int j = 0; j < proby; j++)
		{
			int x = rand() % rozmiarN;
			int y = rand() % rozmiarM;
			if (this->sprawdzCzyPuste(x, y))
			{
				switch (organizm)
				{
				case Org::WILK:
					organizmy[x][y] = new Wilk(x, y, *this);
					break;
				case Org::OWCA:
					organizmy[x][y] = new Owca(x, y, *this);
					break;
				case Org::LIS:
					organizmy[x][y] = new Lis(x, y, *this);
					break;
				case Org::ZOLW:
					organizmy[x][y] = new Zolw(x, y, *this);
					break;
				case Org::ANTYLOPA:
					organizmy[x][y] = new Antylopa(x, y, *this);
					break;
				case Org::TRAWA:
					organizmy[x][y] = new Trawa(x, y, *this);
					break;
				case Org::MLECZ:
					organizmy[x][y] = new Mlecz(x, y, *this);
					break;
				case Org::GUARANA:
					organizmy[x][y] = new Guarana(x, y, *this);
					break;
				case Org::WILCZE_JAGODY:
					organizmy[x][y] = new WilczeJagody(x, y, *this);
					break;
				case Org::BARSZCZ_SOSNOWSKIEGO:
					organizmy[x][y] = new BarszczSosnowskiego(x, y, *this);
					break;
				default:
					break;
				}
				break;
			}
		}
	}
}

void Swiat::organizmyStartowe()
{
	int x, y;
	x = rand() % rozmiarN;
	y = rand() % rozmiarM;
	Czlowiek* czlowiek = new Czlowiek(x, y, *this);
	organizmy[x][y] = czlowiek;
	this->czlowiek = czlowiek;

	dodajLosowo(Org::WILK, LICZBA_WILKOW, PROBY);
	dodajLosowo(Org::OWCA, LICZBA_OWIEC, PROBY);
	dodajLosowo(Org::LIS, LICZBA_LISOW, PROBY);
	dodajLosowo(Org::ZOLW, LICZBA_ZOLWI, PROBY);
	dodajLosowo(Org::ANTYLOPA, LICZBA_ANTYLOP, PROBY);

	dodajLosowo(Org::TRAWA, LICZBA_TRAW, PROBY);
	dodajLosowo(Org::MLECZ, LICZBA_MLECZY, PROBY);
	dodajLosowo(Org::GUARANA, LICZBA_GUARAN, PROBY);
	dodajLosowo(Org::WILCZE_JAGODY, LICZBA_WILCZYCH_JAGOD, PROBY);
	dodajLosowo(Org::BARSZCZ_SOSNOWSKIEGO, LICZBA_BARSZCZY_SOSNOWSKIEGO, PROBY);
}


bool Swiat::czyGraTrwa() const
{
	return this->czlowiek->czyZyje();
}

bool Swiat::czyGlobalnaUmiejetnosc() const
{
	return this->czlowiek->czyNiesmiertelny();
}

int Swiat::sprawdzCzasOdnowienia() const
{
	return this->czlowiek->getCzasOdnowienia();
}

bool Swiat::czyKomunikaty() const
{
	return this->komunikakty;
}

void Swiat::setKomunikaty(bool stan)
{
	this->komunikakty = stan;
}


bool Swiat::zapiszSwiat(std::string nazwa)
{
	nazwa += ".txt";
	std::ofstream plikZapisu(nazwa);
	if (!plikZapisu.is_open())
		return false;

	plikZapisu << this->rozmiarN << "\n";
	plikZapisu << this->rozmiarM << "\n";
	plikZapisu << this->czlowiek->czyNiesmiertelny() << "\n";
	plikZapisu << this->czlowiek->getCzasAktywacji() << "\n";

	for (int x = 0; x < this->rozmiarN; x++)
	{
		for (int y = 0; y < this->rozmiarM; y++)
		{
			if (this->organizmy[x][y] != nullptr)
			{
				plikZapisu << organizmy[x][y]->getSymbol() << "\n";
				plikZapisu << organizmy[x][y]->getX() << "\n";
				plikZapisu << organizmy[x][y]->getY() << "\n";
				plikZapisu << organizmy[x][y]->getSila() << "\n";
				plikZapisu << organizmy[x][y]->getInicjatywa() << "\n";
				plikZapisu << organizmy[x][y]->getWiek() << "\n";
				plikZapisu << organizmy[x][y]->czyZyje() << "\n";
			}
		}
	}

	plikZapisu.close();
	return true;
}


Swiat::Swiat(std::ifstream& plikZapisu)
{
	bool umiejetnosc;
	int aktywacja;

	std::string linia;

	std::getline(plikZapisu, linia);
	this->rozmiarN = std::stoi(linia);
	std::getline(plikZapisu, linia);
	this->rozmiarM = std::stoi(linia);

	this->czlowiek = nullptr;

	organizmy = new Organizm * *[rozmiarN];

	for (int i = 0; i < rozmiarN; i++)
	{
		organizmy[i] = new Organizm * [rozmiarM]();
	}

	std::getline(plikZapisu, linia);
	umiejetnosc = std::stoi(linia);
	std::getline(plikZapisu, linia);
	aktywacja = std::stoi(linia);

	while (std::getline(plikZapisu, linia))
	{
		char symbol = linia[0];
		std::getline(plikZapisu, linia);
		int x = std::stoi(linia);
		std::getline(plikZapisu, linia);
		int y = std::stoi(linia);

		
		if (symbol == '@')
		{
			Czlowiek* czlowiek = new Czlowiek(x, y, *this);
			czlowiek->setUmiejetnosc(umiejetnosc);
			czlowiek->setCzasAktywacji(aktywacja);
			organizmy[x][y] = czlowiek;
			this->czlowiek = czlowiek;
		}
		else
			this->dodajOrganizm(symbol, x, y);

		std::getline(plikZapisu, linia);
		organizmy[x][y]->setSila(std::stoi(linia));

		std::getline(plikZapisu, linia);
		organizmy[x][y]->setInicjatywa(std::stoi(linia));

		std::getline(plikZapisu, linia);
		organizmy[x][y]->setWiek(std::stoi(linia));

		std::getline(plikZapisu, linia);
		organizmy[x][y]->setCzyZyje(std::stoi(linia));
	}

	this->komunikakty = false;
}

Swiat::Swiat(int rozmiarN, int rozmiarM):
	rozmiarN(rozmiarN), rozmiarM(rozmiarM)
{
	organizmy = new Organizm**[rozmiarN];

	for (int i = 0; i < rozmiarN; i++)
	{
		organizmy[i] = new Organizm*[rozmiarM]();
	}

	this->komunikakty = false;
	this->czlowiek = nullptr;
	this->organizmyStartowe();
}

Swiat::~Swiat()
{
	for (int x = 0; x < rozmiarN; x++)
	{
		for (int y = 0; y < rozmiarM; y++)
		{
			if (organizmy[x][y] != nullptr)
			{
				delete organizmy[x][y];
			}
		}
		delete[] organizmy[x];
	}
	delete[] organizmy;

	while (!doUsuniecia.empty())
	{
		delete doUsuniecia.top();
		doUsuniecia.pop();
	}
}