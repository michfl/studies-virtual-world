#include "KomparatorOrganizmow.h"

bool KomparatorOrganizmow::operator()(const Organizm* lewy, const Organizm* prawy)
{
	if (lewy->getInicjatywa() != prawy->getInicjatywa())
	{
		return lewy->getInicjatywa() < prawy->getInicjatywa();
	}
	else
	{
		return lewy->getWiek() < prawy->getWiek();
	}
}