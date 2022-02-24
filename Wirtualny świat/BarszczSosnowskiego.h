#pragma once
#include "Roslina.h"

#define BARSZCZ_SOSNOWSKIEGO_SILA 10
#define BARSZCZ_SOSNOWSKIEGO_SZANSA 5

class BarszczSosnowskiego :
	public Roslina
{
public:
	void akcja() final;
	AkcjaZwrotna kolizja(Organizm*) final;

	BarszczSosnowskiego(int, int, Swiat&);
	BarszczSosnowskiego(const Roslina*, int, int);
	~BarszczSosnowskiego();
};

