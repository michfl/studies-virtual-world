#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "Swiat.h"

#define SCIEZKA_ZAPISU "zapisy\\"

#define KEY_SPACE      32

#define KEY_1	   	   49
#define KEY_2		   50
#define KEY_3		   51

#define KEY_UP         72
#define KEY_LEFT       75
#define KEY_RIGHT      77
#define KEY_DOWN       80

#define KEY_K		   107
#define KEY_W		   119
#define KEY_X		   120
#define KEY_Z		   122

class Swiat;

class SymulacjaSwiata
{
private:
	Swiat* swiat;
	std::string sciezkaZapisu;

public:
	void menuStartowe();

	bool nowaGra();
	bool wczytajGre();
	void zapiszGre();

	bool symulacja();
	bool czySkonczycGre();

	bool czySwiatIstnieje() const;
	void rysujSwiat() const;

	SymulacjaSwiata();
	~SymulacjaSwiata();
};

