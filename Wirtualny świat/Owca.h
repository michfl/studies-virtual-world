#pragma once
#include "Zwierze.h"

#define OWCA_SILA 4
#define OWCA_INICJATYWA 4

class Owca :
	public Zwierze
{
public:
	Owca(int, int, Swiat&);
	Owca(const Zwierze*, int, int);
	~Owca();
};

