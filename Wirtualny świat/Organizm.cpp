#include "Organizm.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>

std::tuple<int, int> Organizm::kierunekNaPrzesuniecie(Kierunek kierunek)
{
	switch (kierunek)
	{
	case Kierunek::N:
		return { 0, 1 };
	case Kierunek::S:
		return { 0, -1 };
	case Kierunek::E:
		return { 1, 0 };
	case Kierunek::W:
		return { -1, 0 };
	case Kierunek::NE:
		return { 1, 1 };
	case Kierunek::NW:
		return { 1, -1 };
	case Kierunek::SE:
		return { -1, 1 };
	case Kierunek::SW:
		return { -1, -1 };
	}
}


std::string Organizm::nazwa(char znak) const
{
	std::string nazwa;

	switch (znak)
	{
	case '@':
		nazwa = "Czlowiek";
		break;
	case 'W':
		nazwa = "Wilk";
		break;
	case 'O':
		nazwa = "Owca";
		break;
	case 'L':
		nazwa = "Lis";
		break;
	case 'Z':
		nazwa = "Zolw";
		break;
	case 'A':
		nazwa = "Antylopa";
		break;
	case 'T':
		nazwa = "Trawa";
		break;
	case 'M':
		nazwa = "Mlecz";
		break;
	case 'G':
		nazwa = "Guarana";
		break;
	case 'J':
		nazwa = "Wilcze jagody";
		break;
	case 'B':
		nazwa = "Barszcz sosnowskiego";
		break;
	default:
		nazwa = "?";
		break;
	}
	return nazwa;
}

void Organizm::wypowiedz(std::string slowa) const
{
	std::cout << this->nazwa(this->getSymbol())
		<< " [" << this->getWiek() << "]" << " ("
		<< this->getX() << ", " << this->getY()
		<< ") " << slowa << "\n";
}


char Organizm::getSymbol() const
{
	return this->symbol;
}

void Organizm::setSymbol(char symbol)
{
	this->symbol = symbol;
}


int Organizm::getSila() const
{
	return this->sila;
}

void Organizm::setSila(int sila) 
{
	this->sila = sila;
}


int Organizm::getInicjatywa() const 
{
	return this->inicjatywa;
}

void Organizm::setInicjatywa(int inicjatywa)
{
	this->inicjatywa = inicjatywa;
}

int Organizm::getWiek() const
{
	return this->wiek;
}

void Organizm::setWiek(int wiek)
{
	this->wiek = wiek;
}

void Organizm::zwiekszWiek()
{
	this->wiek++;
}


void Organizm::setCzyZyje(bool stan)
{
	this->zyje = stan;
}


int Organizm::getX() const 
{
	return this->x;
}

void Organizm::setX(int x)
{
	this->x = x;
}

int Organizm::getY() const
{
	return this->y;
}

void Organizm::setY(int y)
{
	this->y = y;
}


Swiat& Organizm::getSwiat() const
{
	return this->swiat;
}

void Organizm::setSwiat(Swiat& swiat) 
{
	this->swiat = swiat;
}


bool Organizm::czyOdbilAtak(Organizm* atakujacy) const
{
	if (this->getSila() > atakujacy->getSila())
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" odbija atak...");
		return true;
	}
	else if (this->getSila() == atakujacy->getSila())
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" przegrywa pojedynek...");
		return false;
	}
	else
	{
		if (this->getSwiat().czyKomunikaty())
			this->wypowiedz(" przegrywa pojedynek...");
		return false;
	}
}

bool Organizm::czyZyje() const
{
	return this->zyje;
}

void Organizm::zabij()
{
	if (this->getSwiat().czyKomunikaty())
		this->wypowiedz(" umiera.");
	this->zyje = false;
}

void Organizm::rysowanie() const
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (this->getSymbol())
	{
	case '@':
		SetConsoleTextAttribute(hOut, 12 * 16 + 15);
		std::cout << this->symbol;
		break;
	case 'W':
		SetConsoleTextAttribute(hOut, 8 * 16);
		std::cout << this->symbol;
		break;
	case 'O':
		SetConsoleTextAttribute(hOut, 7 * 16);
		std::cout << this->symbol;
		break;
	case 'L':
		SetConsoleTextAttribute(hOut, 4 * 16);
		std::cout << this->symbol;
		break;
	case 'Z':
		SetConsoleTextAttribute(hOut, 2 * 16);
		std::cout << this->symbol;
		break;
	case 'A':
		SetConsoleTextAttribute(hOut, 6 * 16);
		std::cout << this->symbol;
		break;
	case 'T':
		SetConsoleTextAttribute(hOut, 10);
		std::cout << this->symbol;
		break;
	case 'M':
		SetConsoleTextAttribute(hOut, 14);
		std::cout << this->symbol;
		break;
	case 'G':
		SetConsoleTextAttribute(hOut, 12);
		std::cout << this->symbol;
		break;
	case 'J':
		SetConsoleTextAttribute(hOut, 13);
		std::cout << this->symbol;
		break;
	case 'B':
		SetConsoleTextAttribute(hOut, 15);
		std::cout << this->symbol;
		break;
	default:
		std::cout << this->symbol;
		break;
	}
	SetConsoleTextAttribute(hOut, 7);
}


Organizm::Organizm(int x, int y, Swiat& swiat) :
	x(x), y(y), swiat(swiat)
{
	sila = 0;
	inicjatywa = 0;
	symbol = '#';
	wiek = 0;
	zyje = true;
}

Organizm::Organizm(const Organizm* wzor):
	symbol(wzor->getSymbol()), inicjatywa(wzor->getInicjatywa()), 
	wiek(0), zyje(true), x(wzor->getX()), y(wzor->getY()),
	swiat(wzor->getSwiat())
{
	if (this->getSwiat().czyKomunikaty())
		this->wypowiedz(" przychodzi na swiat.");
}