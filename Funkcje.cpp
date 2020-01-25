#include "Funkcje.h"
#include "memory/nvwa/debug_new.h"

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

int IloscZdolnychOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania)
{
	int ilosc = 0;

	while (pHead)
	{
		if (pHead->dopasowanie > WspolczynnikRozmnazania)
		{
			ilosc++;
		}
		pHead = pHead->pNext;
	}

	return ilosc;
}

void DodajDoListyOsobnikow(Osobnik*& pHead, Chromosom* pChromosom, double dopasowanie)
{
	if (!pHead)
	{
		pHead = new Osobnik{ dopasowanie, pChromosom, nullptr };
	}
	else
	{
		Osobnik* temp = pHead;
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = new Osobnik{ dopasowanie, pChromosom, nullptr };
	}
}

void DodajDoListyChromosomow(Chromosom*& pHead, int wartosc)
{
	if (!pHead)
	{
		pHead = new Chromosom{ wartosc, nullptr };
	}
	else
	{
		Chromosom* temp = pHead;
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = new Chromosom{ wartosc, nullptr };
	}
}

double WylosujFunkcjeDopasowania()
{
	default_random_engine rng;
	rng.seed(chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution<double> rozklad(0.0, 1.0);

	return rozklad(rng);
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

Osobnik* WylosujPareOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania)
{
	//bez tworzenia drugiej listy

	//n, czyli ilosc elementow z ktorych wybieramy - interesuja nas tylko osobniki ktore moga sie rozmnazac, czyli z odpowiednio wysoka wartoscia dopasowania
	int n = IloscZdolnychOsobnikow(pHead, WspolczynnikRozmnazania);

	if (n < 2)
	{
		//zbyt malo osobnikow zdolnych do rozmnozenia
		return nullptr;
	}

	default_random_engine rng;
	rng.seed(chrono::system_clock::now().time_since_epoch().count());
	//okresla ilosc "przejsc" po liscie do znalezienia danego osobnika (tylko dla zdolnych do rozmnazania sie) - od 0 do (n-1)
	uniform_int_distribution<int> rozklad(0, n - 1);

	//losujemy dwa "indeksy" osobnikow ktorych wykorzystamy do krzyzowania
	int a = rozklad(rng);
	int b;

	//upewniamy sie ze wylosowalismy 2 roznych osobnikow
	while (true)
	{
		b = rozklad(rng);
		if (b != a)
		{
			break;
		}
	}

	Osobnik* para = nullptr;

	Osobnik* temp = pHead;
	int i = 0;

	//wybieramy odpowiednich osobnikow do krzyzowania z listy
	//! problem - czasami wybieramy osobnikow ze zbyt mala funkcja

	while (true)
	{
		if (temp->dopasowanie > WspolczynnikRozmnazania)
		{
			if (i >= a)
			{
				break;
			}
			i++;
		}
		temp = temp->pNext;
	}
	para = temp;

	temp = pHead;
	i = 0;

	while (true)
	{
		if (temp->dopasowanie > WspolczynnikRozmnazania)
		{
			if (i >= b)
			{
				break;
			}
			i++;
		}
		temp = temp->pNext;
	}

	//upewniamy sie ze drugi element zwracanej listy nie wskazuje na nic (lista ma byc dwuelementowa)
	para->pNext->pNext = nullptr;

	return para;
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

Osobnik* Rozmnoz(Osobnik*& pHead, Osobnik* pierwszy, Osobnik* drugi, double WspolczynnikRozmnazania)
{
	//Funkcja rozmnozy osobnikow tylko, jezeli ich funkcja dopasowania jest powyzej progu, inaczej zwroci nullptr
	if (pierwszy->dopasowanie <= WspolczynnikRozmnazania || drugi->dopasowanie <= WspolczynnikRozmnazania)
	{
		return nullptr;
	}

	Osobnik* nowy = new Osobnik;
	nowy->chromosom = nullptr;
	Chromosom* pierwszyChromosom = pierwszy->chromosom;
	Chromosom* drugiChromosom = drugi->chromosom;

	default_random_engine rng;
	rng.seed(chrono::system_clock::now().time_since_epoch().count());

	//wylosuj pekniecie dla pierwszego osobnika (ilosc chromosomow ktore dodajemy) - liczymy od poczatku listy do wylosowanego miejsca
	int n = RozmiarListyChromosomow(pierwszy->chromosom);

	//zakladamy ze kazdy osobnik "daje" co najmniej jeden fragment chromosomu
	uniform_int_distribution<int> rozklad(1, n);
	int j = rozklad(rng);

	//dodaj elementy do chromosomu nowego osobnika
	for (int i = 0; i < j; i++)
	{
		DodajDoListyChromosomow(nowy->chromosom, pierwszyChromosom->liczba);
		pierwszyChromosom = pierwszyChromosom->pNext;
	}

	//wylosuj pekniecie dla drugiego osobnika - liczymy od wylosowanego miejsca do konca listy
	n = RozmiarListyChromosomow(drugi->chromosom);
	uniform_int_distribution<int> rozklad2(0, n);
	j = rozklad2(rng);

	for (int i = 0; i < j; i++)
	{
		drugiChromosom = drugiChromosom->pNext;
	}

	while (drugiChromosom)
	{
		DodajDoListyChromosomow(nowy->chromosom, drugiChromosom->liczba);
		drugiChromosom = drugiChromosom->pNext;
	}

	nowy->dopasowanie = WylosujFunkcjeDopasowania();

	return nowy;
}

void NastepnePokolenie(Osobnik*& pHead, int LiczbaParOsobnikow, double WspolczynnikWymierania, double WspolczynnikRozmnazania)
{
	//skrzyzuj LiczbaParOsobnikow par, nastepnie usun z populacji osobniki o zbyt malej wartosci funkcji dopasowania

	for (int i = 0; i < LiczbaParOsobnikow; i++)
	{
		//lista zawierajaca 2 wylosowanych osobnikow
		Osobnik* para = WylosujPareOsobnikow(pHead, WspolczynnikRozmnazania);

		if (!para)
		{
			//w populacji jest zbyt malo osobnikow zdolnych do rozmnazania
			break;
		}

		Osobnik* nowy = Rozmnoz(pHead, para, para->pNext, WspolczynnikRozmnazania);

		if (nowy != nullptr)
		{
			DodajDoListyOsobnikow(pHead, nowy->chromosom, nowy->dopasowanie);
		}

		/*delete para->pNext;
		delete para;*/
		delete nowy;
	}

	UsunOsobnikowZPopulacji(pHead, WspolczynnikWymierania);
}

Osobnik* WczytajOsobnikowZPliku(string& Wejscie)
{
	Osobnik* lista = nullptr;
	ifstream plikWejsciowy(Wejscie);
	string temp;

	//kazda linia to jeden osobnik
	while (getline(plikWejsciowy, temp))
	{
		Osobnik* nowy = new Osobnik;
		nowy->chromosom = nullptr;
		nowy->dopasowanie = WylosujFunkcjeDopasowania();

		//zamieniamy ciag liczb naturalnych oddzielonych spacjami na liste jednokierunkowa chromosomu
		//! zakladamy ze sa oddzielone spacjami, a co jesli nie?

		string tempDna;
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (temp[i] == ' ')
			{
				int dna = stoi(tempDna);
				tempDna = "";
				DodajDoListyChromosomow(nowy->chromosom, dna);
			}
			else
			{
				tempDna += temp[i];
			}
		}
		int dna = stoi(tempDna);
		DodajDoListyChromosomow(nowy->chromosom, dna);

		//dodaj nowego osobnika, wczytanego powyzej, do listy
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