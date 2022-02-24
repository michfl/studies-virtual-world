#include "SymulacjaSwiata.h"

void SymulacjaSwiata::menuStartowe()
{
	std::string nazwa = "";
	std::ifstream plikZapisu;
	char input;
	bool kontynuuj = true;

	while (kontynuuj)
	{
		system("CLS");
		std::cout << "1 ->\tNowa gra\n";
		std::cout << "2 ->\tWczytaj gre\n";
		std::cout << "3 ->\tWyjscie\n";
		input = (char)_getch();

		switch (input)
		{
		case KEY_1:
			system("CLS");
			if (!this->nowaGra())
				break;
			system("CLS");
			kontynuuj = false;
			break;
		case KEY_2:
			system("CLS");
			if (!this->wczytajGre())
				break;
			system("CLS");
			kontynuuj = false;
			break;
		case KEY_3:
			system("CLS");
			std::cout << "Farewell, dear User, farewell!\n";
			_getch();
			return;
		default:
			break;
		}
	}
}


bool SymulacjaSwiata::nowaGra()
{
	int N, M;
	std::cout << "Szerokosc swiata: ";
	std::cin >> N;
	std::cout << "Wysokosc swiata: ";
	std::cin >> M;
	if (N <= 0 || M <= 0)
	{
		std::cout << "To nie zadziala :/\n";
		_getch();
		return false;
	}

	this->swiat = new Swiat(N, M);
	return true;
}

bool SymulacjaSwiata::wczytajGre()
{
	std::ifstream plikZapisu;
	std::string nazwa;
	std::cout << "Nazwa zapisu stanu gry: ";
	std::cin >> nazwa;
	nazwa = this->sciezkaZapisu + nazwa + ".txt";

	plikZapisu.open(nazwa);
	if (!plikZapisu.is_open())
	{
		std::cout << "Plik o podanej nazwie nie istnieje\n";
		_getch();
		return false;
	}

	if (this->czySwiatIstnieje())
		delete this->swiat;
	this->swiat = new Swiat(plikZapisu);
	plikZapisu.close();
	return true;
}

void SymulacjaSwiata::zapiszGre()
{
	std::string nazwa;
	std::cout << "Nazwa zapisu stanu gry: ";
	std::cin >> nazwa;
	nazwa = this->sciezkaZapisu + nazwa;
	if (swiat->zapiszSwiat(nazwa))
		std::cout << "Zapisano " << nazwa << "\n";
	else
		std::cout << "Zapis zakonczony niepowodzeniem\n";
}


bool SymulacjaSwiata::symulacja()
{
	char input;
	bool kontynuuj = true;
	bool umiejetnosc = false;
	bool rysuj = true;
	while (kontynuuj)
	{
		if (rysuj)
		{
			std::cout << "\n";
			this->rysujSwiat();
		}

		input = (char)_getch();

		switch (input)
		{
		case KEY_SPACE:
			umiejetnosc = true;
			if (!this->swiat->czyGlobalnaUmiejetnosc())
				std::cout << "Niesmiertelnosc zostanie aktywowana w nastepnej turze.\n";
			rysuj = false;
			break;
		case KEY_UP:
			system("CLS");
			if (!this->swiat->wykonajTure(Kierunek::N, umiejetnosc))
			{
				if (this->czySkonczycGre())
					return false;
			}
			umiejetnosc = false;
			rysuj = true;
			break;
		case KEY_DOWN:
			system("CLS");
			if (!this->swiat->wykonajTure(Kierunek::S, umiejetnosc))
			{
				if (this->czySkonczycGre())
					return false;
			}
			umiejetnosc = false;
			rysuj = true;
			break;
		case KEY_LEFT:
			system("CLS");
			if (!this->swiat->wykonajTure(Kierunek::W, umiejetnosc))
			{
				if (this->czySkonczycGre())
					return false;
			}
			umiejetnosc = false;
			rysuj = true;
			break;
		case KEY_RIGHT:
			system("CLS");
			if (!this->swiat->wykonajTure(Kierunek::E, umiejetnosc))
			{
				if (this->czySkonczycGre())
					return false;
			}
			umiejetnosc = false;
			rysuj = true;
			break;
		case KEY_K:
			system("CLS");
			if (this->swiat->czyKomunikaty())
				this->swiat->setKomunikaty(false);
			else
				this->swiat->setKomunikaty(true);
			rysuj = true;
			break;
		case KEY_W:
			if (!this->wczytajGre())
			{
				rysuj = false;
				break;
			}
			system("CLS");
			rysuj = true;
			break;
		case KEY_Z:
			system("CLS");
			this->zapiszGre();
			_getch();
			system("CLS");
			rysuj = true;
			break;
		case KEY_X:
			kontynuuj = false;
			rysuj = false;
			break;
		default:
			rysuj = false;
			break;
		}
	}
	return false;
}

bool SymulacjaSwiata::czySkonczycGre()
{
	std::cout << "         .---.\n";
	std::cout << "    '-.  |   |  .-'\n";
	std::cout << "      ___|   |___\n";
	std::cout << " -=  [           ]  =-\n";
	std::cout << "     `---.   .---'\n";
	std::cout << "  __||__ |   | __||__\n";
	std::cout << "  '-..-' |   | '-..-'\n";
	std::cout << "    ||   |   |   ||\n";
	std::cout << "    ||_.-|   |-,_||\n";
	std::cout << "  .-'`   `'`'`   `'-.\n";
	std::cout << ".'                   '.\n\n";
	std::cout << "Czlowieczenstwo upadlo...\n";
	_getch();
	delete this->swiat;
	this->swiat = nullptr;
	this->menuStartowe();
	return !this->czySwiatIstnieje();
}


bool SymulacjaSwiata::czySwiatIstnieje() const
{
	return this->swiat != nullptr;
}

void SymulacjaSwiata::rysujSwiat() const
{
	this->swiat->rysujSwiat();
	if (this->swiat->czyGlobalnaUmiejetnosc())
		std::cout << "Niesmiertelnosc wlaczona!\n";
	else if (this->swiat->sprawdzCzasOdnowienia() > 0)
		std::cout << "Niesmiertelnosc bedzie gotowa za "
		<< this->swiat->sprawdzCzasOdnowienia() << " tury\n";
	else
		std::cout << "SPACJA\t-> niesmiertelnosc\n";
	if (this->swiat->czyKomunikaty())
		std::cout << "K\t-> komunikaty [wlaczone]\n";
	else
		std::cout << "K\t-> komunikaty [wylaczone]\n";
	std::cout << "W\t-> wczytaj stan gry\n";
	std::cout << "Z\t-> zapisz stan gry\n";
	std::cout << "X\t-> wyjscie\n";
}


SymulacjaSwiata::SymulacjaSwiata()
{
	this->swiat = nullptr;
	this->sciezkaZapisu = SCIEZKA_ZAPISU;
}

SymulacjaSwiata::~SymulacjaSwiata()
{
	if (this->swiat != nullptr)
		delete this->swiat;
}
