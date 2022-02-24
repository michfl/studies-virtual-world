#pragma once
#include "Zwierze.h"

#define WILK_SILA 9
#define WILK_INICJATYWA 4

class Wilk :
	public Zwierze
{
public:
	Wilk(int, int, Swiat&);
	Wilk(const Zwierze*, int, int);
	~Wilk();
};

