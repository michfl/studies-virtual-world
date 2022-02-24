#pragma once
#include "Roslina.h"

#define TRAWA_SILA 0
#define TRAWA_SZANSA 25

class Trawa :
	public Roslina
{
public:
	Trawa(int, int, Swiat&);
	Trawa(const Roslina*, int, int);
	~Trawa();
};

