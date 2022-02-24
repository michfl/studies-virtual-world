#pragma once
#include "Roslina.h"

#define GUARANA_SILA 0
#define GUARANA_SZANSA 10

class Guarana :
	public Roslina
{
public:
	AkcjaZwrotna kolizja(Organizm*) final;

	Guarana(int, int, Swiat&);
	Guarana(const Roslina*, int, int);
	~Guarana();
};

