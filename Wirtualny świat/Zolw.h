#pragma once
#include "Zwierze.h"

#define ZOLW_SILA 2
#define ZOLW_INICJATYWA 1

class Zolw :
	public Zwierze
{
protected:
	bool czyOdbilAtak(Organizm*) const final;

public:
	void akcja() final;

	Zolw(int, int, Swiat&);
	Zolw(const Zwierze*, int, int);
	~Zolw();
};

