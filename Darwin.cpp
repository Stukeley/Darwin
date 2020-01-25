#include "Funkcje.h"

int main(int argc, char* argv[])
{
	//wczytywanie przelacznikow (zakladamy, ze kazdy z nich jest podany przy kazdym uruchomieniu programu)

	//Nazwa pliku wej�ciowego podana jako prze��cznik.
	string Wejscie;

	//Nazwa pliku wyj�ciowego podana jako prze��cznik.
	string Wyjscie;

	//Pr�g wymierania osobnik�w podany jako prze��cznik.
	double WspolczynnikWymierania;

	//Pr�g rozmna�ania osobnik�w podany jako prze��cznik.
	double WspolczynnikRozmnazania;

	//Ilo�� pokole� do zasymulowania, podana jako prze��cznik.
	int LiczbaPokolen;

	//Ilo�� krzy�uj�cych si� par osobnik�w podana jako prze��cznik.
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