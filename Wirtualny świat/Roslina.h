#pragma once
#include "Organizm.h"
class Roslina :
	public Organizm
{
private:
	int szansa;

public:
	int getSzansa() const;
	void setSzansa(int);

	bool sprawdzSzanse();

	virtual void akcja() override;
	virtual void akcja(Kierunek, bool) override {};
	virtual AkcjaZwrotna kolizja(Organizm*) override;

	void rozmnazanie() final;

	Roslina(int, int, int, Swiat&);
	Roslina(const Roslina*, int, int);
	~Roslina();
};

