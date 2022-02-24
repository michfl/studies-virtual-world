#pragma once
#include <tuple>
#include "Organizm.h"

class Zwierze :
	public Organizm
{
protected:
	virtual std::tuple<int, int> ustalPozycje();

public:
	virtual void akcja() override;
	virtual void akcja(Kierunek, bool) override {};
	virtual AkcjaZwrotna kolizja(Organizm*) override;

	bool ucieczka();
	void rozmnazanie() final;

	Zwierze(int, int, Swiat&);
	Zwierze(const Zwierze*, int, int);
	~Zwierze();
};

