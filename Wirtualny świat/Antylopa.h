#pragma once
#include "Zwierze.h"

#define ANTYLOPA_SILA 4
#define ANTYLOPA_INICJATYWA 4

class Antylopa :
	public Zwierze
{
public:
	void akcja() final;
	AkcjaZwrotna kolizja(Organizm*) final;

	Antylopa(int, int, Swiat&);
	Antylopa(const Zwierze*, int, int);
	~Antylopa();
};

