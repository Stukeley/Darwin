#include "Funkcje.h"

int main(int argc, char* argv[])
{
	//wczytywanie przelacznikow (zakladamy, ze kazdy z nich jest podany przy kazdym uruchomieniu programu)

	//Nazwa pliku wejœciowego podana jako prze³¹cznik.
	string Wejscie;

	//Nazwa pliku wyjœciowego podana jako prze³¹cznik.
	string Wyjscie;

	//Próg wymierania osobników podany jako prze³¹cznik.
	double WspolczynnikWymierania;

	//Próg rozmna¿ania osobników podany jako prze³¹cznik.
	double WspolczynnikRozmnazania;

	//Iloœæ pokoleñ do zasymulowania, podana jako prze³¹cznik.
	int LiczbaPokolen;

	//Iloœæ krzy¿uj¹cych siê par osobników podana jako prze³¹cznik.
	int LiczbaParOsobnikow;

	//wczytaj przelaczniki

	for (int i = 0; i < argc; i++)
	{
		if ((string)argv[i] == "-i")
		{
			Wejscie = argv[++i];
		}
		else if ((string)argv[i] == "-o")
		{
			Wyjscie = argv[++i];
		}
		else if ((string)argv[i] == "-w")
		{
			WspolczynnikWymierania = stod(argv[++i]);
		}
		else if ((string)argv[i] == "-r")
		{
			WspolczynnikRozmnazania = stod(argv[++i]);
		}
		else if ((string)argv[i] == "-p")
		{
			LiczbaPokolen = stoi(argv[++i]);
		}
		else if ((string)argv[i] == "-k")
		{
			LiczbaParOsobnikow = stoi(argv[++i]);
		}
	}

	//Debug
	Wejscie = "Wejscie.txt";
	Wyjscie = "Wyjscie.txt";
	WspolczynnikWymierania = 0.2;
	WspolczynnikRozmnazania = 0.5;
	LiczbaPokolen = 3;
	LiczbaParOsobnikow = 2;
	//

	Osobnik* pGlowa = WczytajOsobnikowZPliku(Wejscie);

	for (int i = 0; i < LiczbaPokolen; i++)
	{
		NastepnePokolenie(pGlowa, LiczbaParOsobnikow, WspolczynnikWymierania, WspolczynnikRozmnazania);
	}

	ZapiszOsobnikowDoPliku(pGlowa, Wyjscie);

	UsunListeOsobnikow(pGlowa);

	return 0;
}