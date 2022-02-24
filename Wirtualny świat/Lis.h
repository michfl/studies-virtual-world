#pragma once
#include "Zwierze.h"

#define LIS_SILA 3
#define LIS_INICJATYWA 7

class Lis :
	public Zwierze
{
protected:
	std::tuple<int, int> ustalPozycje() final;

public:
	Lis(int, int, Swiat&);
	Lis(const Zwierze*, int, int);
	~Lis();
};

