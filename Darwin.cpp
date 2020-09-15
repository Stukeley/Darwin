#include "Funkcje.h"

int main(int argc, char* argv[])
{
	//wczytywanie przelacznikow (program wymaga podania wszystkich z nich, w dowolnej kolejnosci)

	//Nazwa pliku wejsciowego
	string Wejscie;

	//Nazwa pliku wyjsciowego
	string Wyjscie;

	//Prog wymierania osobnikow
	double WspolczynnikWymierania;

	//Prog rozmnazania osobnikow
	double WspolczynnikRozmnazania;

	//Ilosc pokolen do zasymulowania
	int LiczbaPokolen;

	//Ilosc krzyzujacych sie par osobnikow
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

	Osobnik* pGlowa = WczytajOsobnikowZPliku(Wejscie);

	for (int i = 0; i < LiczbaPokolen; i++)
	{
		NastepnePokolenie(pGlowa, LiczbaParOsobnikow, WspolczynnikRozmnazania);
		UstawFunkcjeDopasowania(pGlowa);
		UsunOsobnikowZPopulacji(pGlowa, WspolczynnikWymierania);
	}

	ZapiszOsobnikowDoPliku(pGlowa, Wyjscie);

	UsunListeOsobnikow(pGlowa);

	return 0;
}