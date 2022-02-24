#pragma once
#include <stack>
#include <string>
#include "Organizm.h"
#include "Kierunek.h"
#include "ListaOrganizmow.h"

class Organizm;
class Czlowiek;

class Swiat
{
private:
	int rozmiarN;
	int rozmiarM;
	Organizm*** organizmy;
	Czlowiek* czlowiek;

	bool komunikakty;

	std::stack<Organizm*> doUsuniecia;

protected:
	void organizmyStartowe();
	void dodajLosowo(Org, int, int);

	bool czyGraTrwa() const;

public:
	Organizm** operator[](int);

	int getRozmiarN() const;
	int getRozmiarM() const;

	bool czyGlobalnaUmiejetnosc() const;
	int sprawdzCzasOdnowienia() const;

	bool czyKomunikaty() const;
	void setKomunikaty(bool);

	void rysujSwiat();
	bool wykonajTure(Kierunek, bool);
	void ruch(Organizm*, int, int);
	void dodajOrganizm(Organizm*, int, int);
	void dodajOrganizm(char, int, int);
	void doKolejkiUsuwania(Organizm*);

	bool sprawdzCzyWGranicach(int, int) const;
	bool sprawdzCzyPuste(int, int) const;

	bool zapiszSwiat(std::string);

	Swiat(int, int);
	Swiat(std::ifstream&);
	~Swiat();
};

