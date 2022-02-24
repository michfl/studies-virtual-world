#include "SymulacjaSwiata.h"

int main()
{
	srand(time(NULL));

	SymulacjaSwiata* gra = new SymulacjaSwiata;
	gra->menuStartowe();
	if (!gra->czySwiatIstnieje())
	{
		delete gra;
		return 0;
	}

	if (!gra->symulacja())
	{
		delete gra;
		return 0;
	}

	delete gra;
	return 0;
}