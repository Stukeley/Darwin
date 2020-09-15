/**
 * @file
 */
#pragma once
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "Struktury.h"
using namespace std;

/**
 * Funkcja wczytuje osobniki z pliku wejsciowego o nazwie podanej jako przelacznik i zapisuje ich do listy jednokierunkowej osobnikow podwieszonej lista chromosomow.
 * @param Wejscie Nazwa pliku wejsciowego podana jako przelacznik.
 * @return Lista osobnikow wczytanych z pliku.
 * @note Parametr jest przekazywany przez referencje, gdyz i tak nie jest modyfikowany przez funkcje.
 */
Osobnik* WczytajOsobnikowZPliku(string& Wejscie);

/**
 * Funkcja zapisuje obecny stan populacji do pliku wejsciowego o nazwie podanej jako przelacznik.
 * @param pHead Wskaznik na pierwszy element listy osobnikow.
 * @param Wyjscie Nazwa pliku wyjsciowego podana jako przelacznik.
 * @note Parametr jest przekazywany przez referencje, gdyz i tak nie jest modyfikowany przez funkcje.
 */
void ZapiszOsobnikowDoPliku(Osobnik* pHead, string& Wyjscie);

/**
 * Tworzy nowego osobnika na podstawie chromosomu oraz funkcji dopasowania, podanych jako parametry, i dodaje go do listy osobnikow.
 * @param pHead Wskaznik na pierwszy element listy, do ktorej nalezy dodac nowego osobnika.
 * @param chromosom Wskaznik na pierwszy element listy reprezentujacej chromosom osobnika.
 * @param dopasowanie Wartosc funkcji dopasowania osobnika.
 */
void DodajDoListyOsobnikow(Osobnik*& pHead, Chromosom* chromosom, double dopasowanie);

/**
 * Dodaje wartosc przekazana jako parametr do danej listy chromosomow osobnika.
 * @param pHead Wskaznik na pierwszy element listy chromosomow, do ktorej nalezy dodac nowa wartosc.
 * @param liczba Liczba reprezentujaca chromosom.
 */
void DodajDoListyChromosomow(Chromosom*& pHead, int liczba);

/**
 * Funkcja losuje dla osobnika wartosc dopasowania z przedzialu [0;1].
 * @return Wylosowana wartosc funkcji dopasowania.
 */
double WylosujFunkcjeDopasowania();

/**
 * Funkcja losuje kazdemu osobnikowi z wartoscia funkcji dopasowania rowna -1 nowa wartosc z przedzialu [0;1].
 * @param pHead Wskaznik na pierwszy element listy, dla ktorej losujemy nowe wartosci.
 * @note Wartosc (-1) oznacza "nie ustawiono", zostanie wylosowana dopiero po skrzyzowaniu pokolenia, by nowopowstale osobniki nie krzyzowaly sie od razu z innymi.
 */
void UstawFunkcjeDopasowania(Osobnik* pHead);

/**
 * Usuwa liste jednokierunkowa chromosomow.
 * @param pHead Wskaznik na pierwszy element listy chromosomow, ktora usuwamy.
 */
void UsunListeChromosomow(Chromosom*& pHead);

/**
 * Usuwa liste jednokierunkowa osobnikow, wraz z lista chromosomow dla kazdego osobnika.
 * @param pHead Wskaznik na pierwszy element listy osobnikow, ktora usuwamy.
 * @note Funkcja jest wykonywana przed zakonczeniem dzialania programu.
 */
void UsunListeOsobnikow(Osobnik*& pHead);

/**
 * Usuwa z populacji osobniki, ktore maja wartosc funkcji dopasowania ponizej progu podanego jako przelacznik.
 * @param pHead Wskaznik na pierwszy element listy osobnikow.
 * @param WspolczynnikWymierania Wspolczynnik wymierania podany jako przelacznik.
 */
void UsunOsobnikowZPopulacji(Osobnik*& pHead, double WspolczynnikWymierania);

/**
 * Funkcja zwraca ilosc elementow w liscie jednokierunkowej chromosomow.
 * @param pHead Wskaznik na pierwszy element listy chromosomow.
 * @return Ilosc elementow w liscie.
 */
int RozmiarListyChromosomow(Chromosom* pHead);

/**
 * Funkcja zwraca ilosc elementow w liscie jednokierunkowej osobnikow.
 * @param pHead Wskaznik na pierwszy element listy osobnikow.
 * @return Ilosc elementow w liscie.
 */
int RozmiarListyOsobnikow(Osobnik* pHead);

/**
 * Funkcja kopiuje liste chromosomow podana jako parametr, a nastepnie zwraca ja.
 * @param stary Chromosom, ktory kopiujemy.
 * @return Nowa lista zawierajaca takie same chromosomy jak ta podana jako parametr.
 * @note Funkcja ta ulatwia zwalnianie pamieci po wykonaniu programu.
 */
Chromosom* DuplikujChromosom(Chromosom* stary);

/**
 * Funkcja doprowadza do pekniecie dwoch chromosomow w wyznaczonych miejscach, a nastepnie laczy je.
 * @param pierwszy Wskaznik na pierwszy element pierwszej listy chromosomow.
 * @param k1 Miejsce pekniecia pierwszego chromosomu.
 * @param drugi Wskaznik na pierwszy element drugiej listy chromosomow.
 * @param k2 Miejsce peknecia drugiego chromosomu.
 * @return Zl¹czony chromosom.
 * @note Dla pierwszej listy zliczamy chromosomy od poczaku do miejsca pekniecia, a dla drugiej - od miejsca pekniecia do konca. Zakladamy rowniez, ze kazdy osobnik "daje" co najmniej jeden chromosom.
 */
Chromosom* PolaczChromosom(Chromosom* pierwszy, int k1, Chromosom* drugi, int k2);

/**
 * Funkcja losowo wybiera dwoch osobnikow do krzyzowania sie z listy wszystkich osobnikow.
 * @param pHead Wskaznik na pierwszy element listy wszystkich osobnikow.
 * @param WspolczynnikRozmnazania Wspolczynnik rozmnazania podany jako przelacznik.
 * @param pierwszy Pierwszy osobnik ze zwracanej pary.
 * @param drugi Drugi osobnik ze zwracanej pary.
 * @note Jezeli ktorys z wylosowanych osobnikow bedzie nullptr, oznacza to, ze w populacji jest zbyt malo osobnikow zdolnych do rozmnazania sie.
 */
void WylosujPareOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania, Osobnik*& pierwszy, Osobnik*& drugi);

/**
 * Rozmnaza osobniki i zwraca potomka powstalego wskutek pekniecia chromosomow krzyzujacych sie osobnikow.
 * @param pierwszy Pierwszy z osobnikow do rozmnozenia.
 * @param drugi Drugi z osobnikow do rozmnozenia.
 * @param WspolczynnikRozmnazania Wspolczynnik rozmnazania podany jako przelacznik.
 * @return Osobnik powstaly wskutek rozmnazania.
 * @note Funkcja zwroci nullptr jezeli ktorykolwiek z osobnikow jest niezdolny do rozmnazania (ma wartosc funkcji dopasowania ponizej progu).
 */
Osobnik* Rozmnoz(Osobnik* pierwszy, Osobnik* drugi, double WspolczynnikRozmnazania);

/**
 * Symuluje nastepne pokolenie osobnikow.
 * @param pHead Wskaznik na pierwszy element listy osobnikow.
 * @param LiczbaParOsobnikow Liczba par osobnikow do rozmnozenia w kazdym pokoleniu, podana jako przelacznik.
 * @param WspolczynnikRozmnazania Wspolczynnik rozmnazania podany jako przelacznik.
 * @note Po wykonaniu funkcji, lista wskazywana przez pHead bedzie zawierala nowostworzonych osobnikow.
 */
void NastepnePokolenie(Osobnik*& pHead, int LiczbaParOsobnikow, double WspolczynnikRozmnazania);