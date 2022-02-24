#pragma once
#include "Zwierze.h"

#define CZLOWIEK_SILA 5
#define CZLOWIEK_INICJATYWA 4
#define CZLOWIEK_CZAS_UMIEJETNOSCI 5

class Czlowiek :
	public Zwierze
{
private:
	bool niesmiertelnosc;
	int czasAktywacji;

protected:
	void wlaczNiesmiertelnosc();
	void aktualizujCzas();

public:
	void akcja(Kierunek, bool) final;
	AkcjaZwrotna kolizja(Organizm*) final;

	int getCzasAktywacji() const;

	void setUmiejetnosc(bool);
	void setCzasAktywacji(int);

	bool czyNiesmiertelny() const;
	int getCzasOdnowienia() const;
	void zabij() final;

	Czlowiek(int, int, Swiat&);
	~Czlowiek();
};

