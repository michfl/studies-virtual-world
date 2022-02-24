#pragma once
#include "Roslina.h"

#define WILCZE_JAGODY_SILA 99
#define WILCZE_JAGODY_SZANSA 5

class WilczeJagody :
	public Roslina
{
public:
	AkcjaZwrotna kolizja(Organizm*) final;

	WilczeJagody(int, int, Swiat&);
	WilczeJagody(const Roslina*, int, int);
	~WilczeJagody();
};

