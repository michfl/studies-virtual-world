#pragma once
#include <tuple>
#include <string>
#include "Swiat.h"
#include "Kierunek.h"
#include "AkcjaZwrotna.h"

class Swiat;

class Organizm
{
private:
	char symbol;
	int sila;
	int inicjatywa;
	int wiek;

	bool zyje;
	int x;
	int y;

	Swiat &swiat;

protected:
	Organizm(int, int, Swiat&);
	Organizm(const Organizm*);

	virtual bool czyOdbilAtak(Organizm*) const;

	std::string nazwa(char) const;
	void wypowiedz(std::string) const;

public:
	std::tuple<int, int> kierunekNaPrzesuniecie(Kierunek);

	char getSymbol() const;
	void setSymbol(char);

	int getSila() const;
	void setSila(int);

	int getInicjatywa() const;
	void setInicjatywa(int);

	int getWiek() const;
	void setWiek(int);
	void zwiekszWiek();

	void setCzyZyje(bool);

	int getX() const;
	int getY() const;
	void setX(int);
	void setY(int);

	Swiat& getSwiat() const;
	void setSwiat(Swiat&);

	virtual void akcja() = 0;
	virtual void akcja(Kierunek, bool) = 0;
	virtual AkcjaZwrotna kolizja(Organizm*) = 0;
	virtual void rozmnazanie() = 0;

	bool czyZyje() const;
	virtual void zabij();
	void rysowanie() const;
};

