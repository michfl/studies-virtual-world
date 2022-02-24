#pragma once
#include "Roslina.h"

#define MLECZ_SILA 0
#define MLECZ_SZANSA 15

class Mlecz :
	public Roslina
{
public:
	void akcja() final;

	Mlecz(int, int, Swiat&);
	Mlecz(const Roslina*, int, int);
	~Mlecz();
};