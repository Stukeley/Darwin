#include "Funkcje.h"

void DodajDoListyOsobnikow(Osobnik*& pHead, Chromosom* chromosom, double dopasowanie)
{
	if (!pHead)
	{
		pHead = new Osobnik{ dopasowanie, chromosom, nullptr };
	}
	else
	{
		Osobnik* temp = pHead;
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = new Osobnik{ dopasowanie, chromosom, nullptr };
	}
}

void DodajDoListyChromosomow(Chromosom*& pHead, int liczba)
{
	if (!pHead)
	{
		pHead = new Chromosom{ liczba, nullptr };
	}
	else
	{
		Chromosom* temp = pHead;
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = new Chromosom{ liczba, nullptr };
	}
}

double WylosujFunkcjeDopasowania()
{
	default_random_engine rng;
	rng.seed(chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution<double> rozklad(0.0, 1.0);

	return rozklad(rng);
}

void UstawFunkcjeDopasowania(Osobnik* pHead)
{
	while (pHead)
	{
		if (pHead->dopasowanie == -1)
		{
			pHead->dopasowanie = WylosujFunkcjeDopasowania();
		}
		pHead = pHead->pNext;
	}
}

void UsunListeChromosomow(Chromosom*& pHead)
{
	while (pHead)
	{
		Chromosom* p = pHead->pNext;
		delete pHead;
		pHead = p;
	}
}

void UsunListeOsobnikow(Osobnik*& pHead)
{
	while (pHead)
	{
		Osobnik* p = pHead->pNext;
		UsunListeChromosomow(pHead->chromosom);
		delete pHead;
		pHead = p;
	}
}

void UsunOsobnikowZPopulacji(Osobnik*& pHead, double WspolczynnikWymierania)
{
	//usuwaj pierwszy element tak dlugo az bedzie on mial dopasowanie >= wspolczynnikowi wymierania
	while (pHead->dopasowanie < WspolczynnikWymierania)
	{
		Osobnik* temp2 = pHead->pNext;
		UsunListeChromosomow(pHead->chromosom);
		delete pHead;
		pHead = temp2;
	}

	//pierwszy element ma teraz na pewno dopasowanie powyzej wspolczynniku wymierania
	Osobnik* temp = pHead;

	while (temp->pNext)
	{
		if (temp->pNext->dopasowanie < WspolczynnikWymierania)
		{
			Osobnik* temp2 = temp->pNext->pNext;
			UsunListeChromosomow(temp->pNext->chromosom);
			delete temp->pNext;
			temp->pNext = temp2;
		}
		else
		{
			temp = temp->pNext;
		}
	}
}

int RozmiarListyChromosomow(Chromosom* pHead)
{
	int ilosc = 0;

	while (pHead)
	{
		ilosc++;
		pHead = pHead->pNext;
	}

	return ilosc;
}

int RozmiarListyOsobnikow(Osobnik* pHead)
{
	int ilosc = 0;

	while (pHead)
	{
		ilosc++;
		pHead = pHead->pNext;
	}

	return ilosc;
}

Chromosom* DuplikujChromosom(Chromosom* stary)
{
	Chromosom* nowy = nullptr;

	while (stary)
	{
		DodajDoListyChromosomow(nowy, stary->liczba);

		stary = stary->pNext;
	}

	return nowy;
}

Chromosom* PolaczChromosom(Chromosom* pierwszy, int k1, Chromosom* drugi, int k2)
{
	//opis dzialania:
	//Pierwszy: 1 2 3 * 4 5
	//Drugi:	6 7 * 8 9
	//Razem:	1 2 3 8 9

	Chromosom* nowy = nullptr;

	//dla pierwszej listy zapisujemy pierwsze k1 chromosomów
	for (int i = 0; i < k1; i++)
	{
		DodajDoListyChromosomow(nowy, pierwszy->liczba);
		pierwszy = pierwszy->pNext;
	}

	//dla drugiej listy zapisujemy chromosomy pozosta³e od k2 do konca
	for (int i = 0; i < k2; i++)
	{
		drugi = drugi->pNext;
	}

	while (drugi)
	{
		DodajDoListyChromosomow(nowy, drugi->liczba);
		drugi = drugi->pNext;
	}

	return nowy;
}

void WylosujPareOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania, Osobnik*& pierwszy, Osobnik*& drugi)
{
	if (!pHead)
	{
		//brak populacji (np. wymarla)
		pierwszy = nullptr;
		drugi = nullptr;
		return;
	}

	Osobnik* zdolne = nullptr;
	Osobnik* temp = pHead;

	while (temp)
	{
		if (temp->dopasowanie > WspolczynnikRozmnazania)
		{
			Chromosom* kopia = DuplikujChromosom(temp->chromosom);
			DodajDoListyOsobnikow(zdolne, kopia, temp->dopasowanie);
		}
		temp = temp->pNext;
	}

	int n = RozmiarListyOsobnikow(zdolne);

	if (n < 2)
	{
		//zbyt malo osobnikow zdolnych do rozmnazania sie
		pierwszy = nullptr;
		drugi = nullptr;
		return;
	}

	default_random_engine rng;
	rng.seed(chrono::system_clock::now().time_since_epoch().count());

	//okresla ilosc "przejsc" po liscie do znalezienia danego osobnika (tylko dla zdolnych do rozmnazania sie) - od 0 do (n - 1)
	uniform_int_distribution<int> rozklad(0, n - 1);

	int a = rozklad(rng);
	int b;

	//upewniamy sie ze wylosowalismy 2 roznych osobnikow
	do
	{
		b = rozklad(rng);
	} while (a == b);

	temp = zdolne;
	for (int i = 0; i < a; i++)
	{
		temp = temp->pNext;
	}
	pierwszy = new Osobnik{ temp->dopasowanie, DuplikujChromosom(temp->chromosom), nullptr };

	temp = zdolne;
	for (int i = 0; i < b; i++)
	{
		temp = temp->pNext;
	}
	drugi = new Osobnik{ temp->dopasowanie, DuplikujChromosom(temp->chromosom), nullptr };

	UsunListeOsobnikow(zdolne);
}

Osobnik* Rozmnoz(Osobnik* pierwszy, Osobnik* drugi, double WspolczynnikRozmnazania)
{
	//upewniamy sie, ze oba osobniki sa zdolne do rozmnazania
	if (pierwszy->dopasowanie <= WspolczynnikRozmnazania || drugi->dopasowanie <= WspolczynnikRozmnazania)
	{
		return nullptr;
	}

	//(-1) w funkcji dopasowania oznacza "nie ustawiono" - zostanie ustawiona po wylosowaniu calego pokolenia (zeby nowopowstale osobniki nie krzyzowaly sie z innymi od razu)
	Osobnik* nowy = new Osobnik{ -1, nullptr, nullptr };

	default_random_engine rng;
	rng.seed(chrono::system_clock::now().time_since_epoch().count());

	//losujemy miejsce pekniecia dla pierwszego chromosomu
	int n1 = RozmiarListyChromosomow(pierwszy->chromosom);

	uniform_int_distribution<int> rozklad1(1, n1 - 1);

	int k1 = rozklad1(rng);

	//losujemy miejsce pekniecia dla drugiego chromosomu
	int n2 = RozmiarListyChromosomow(drugi->chromosom);

	uniform_int_distribution<int> rozklad2(0, n2 - 2);

	int k2 = rozklad2(rng);

	//chromosomy pekaja w wylosowanych miejscach i zostaja polaczone, a nastepnie przypisane do nowego osobnika
	nowy->chromosom = PolaczChromosom(pierwszy->chromosom, k1, drugi->chromosom, k2);

	return nowy;
}

void NastepnePokolenie(Osobnik*& pHead, int LiczbaParOsobnikow, double WspolczynnikRozmnazania)
{
	//skrzyzuj LiczbaParOsobnikow par, nastepnie usun z populacji osobniki o zbyt malej wartosci funkcji dopasowania

	for (int i = 0; i < LiczbaParOsobnikow; i++)
	{
		//to beda nasi osobnicy
		Osobnik* pierwszy = nullptr;
		Osobnik* drugi = nullptr;

		WylosujPareOsobnikow(pHead, WspolczynnikRozmnazania, pierwszy, drugi);

		if (!pierwszy || !drugi)
		{
			//w populacji jest za malo osobnikow zdolnych do rozmnazania
			break;
		}

		Osobnik* nowy = Rozmnoz(pierwszy, drugi, WspolczynnikRozmnazania);

		if (!nowy)
		{
			//jezeli nowy jest nullptr, to najprawdopodobniej cos poszlo nie tak - sprobuj wykonac petle jeszcze raz
			continue;
		}

		DodajDoListyOsobnikow(pHead, DuplikujChromosom(nowy->chromosom), nowy->dopasowanie);

		//usun obu osobnikow (traktujemy ich jak liste jednoelementowa) - nie sa juz nam potrzebni (oczywiscie nadal znajduja sie w liscie wszystkich osobnikow)
		UsunListeOsobnikow(pierwszy);
		UsunListeOsobnikow(drugi);

		UsunListeOsobnikow(nowy);
	}
}

Osobnik* WczytajOsobnikowZPliku(string& Wejscie)
{
	Osobnik* lista = nullptr;
	ifstream plikWejsciowy(Wejscie);
	string linia;

	while (getline(plikWejsciowy, linia))
	{
		Osobnik* nowy = new Osobnik;
		nowy->chromosom = nullptr;
		nowy->dopasowanie = WylosujFunkcjeDopasowania();

		stringstream ss;
		ss << linia;

		int dna;

		while (ss >> dna)
		{
			DodajDoListyChromosomow(nowy->chromosom, dna);
		}

		DodajDoListyOsobnikow(lista, nowy->chromosom, nowy->dopasowanie);
		delete nowy;
	}

	plikWejsciowy.close();

	return lista;
}

void ZapiszOsobnikowDoPliku(Osobnik* pHead, string& Wyjscie)
{
	ofstream plikWyjsciowy(Wyjscie);

	while (pHead)
	{
		Chromosom* temp = pHead->chromosom;

		while (temp)
		{
			plikWyjsciowy << temp->liczba << " ";
			temp = temp->pNext;
		}

		plikWyjsciowy << endl;
		pHead = pHead->pNext;
	}

	plikWyjsciowy.close();
}