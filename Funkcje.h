#pragma once
#include "Struktury.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
using namespace std;

//todo: usunac polskie znaki

/**
 * Funkcja wczytuje osobniki z pliku wej�ciowego i zapisuj�ca ich do listy jednokierunkowej osobnik�w podwieszonej list� DNA (chromosomem).
 * @param Wejscie Nazwa pliku wej�ciowego podana jako prze��cznik.
 * @return Lista osobnik�w wczytanych z pliku.
 * @note Parametr jest przekazywany przez referencj�, gdy� i tak nie jest modyfikowany przez funkcj�.
 */
Osobnik* WczytajOsobnikowZPliku(string& Wejscie);

/**
 * Funkcja zapisuje obecny stan populacji do pliku wej�ciowego o nazwie podanej jako prze��cznik.
 * @param pHead Wska�nik na pierwszy element listy osobnik�w.
 * @param Wyjscie Nazwa pliku wyj�ciowego podana jako prze��cznik.
 * @note Parametr jest przekazywany przez referencj�, gdy� i tak nie jest modyfikowany przez funkcj�.
 */
void ZapiszOsobnikowDoPliku(Osobnik* pHead, string& Wyjscie);

/**
 * Funkcja zwraca ilo�� element�w w li�cie jednokierunkowej chromosom�w.
 * @param pHead Wska�nik na pierwszy element listy chromosom�w.
 * @return Ilo�� element�w w li�cie.
 */
int RozmiarListyChromosomow(Chromosom* pHead);

/**
 * Funkcja zwraca ilo�� element�w w li�cie jednokierunkowej osobnik�w.
 * @param pHead Wska�nik na pierwszy element listy osobnik�w.
 * @return Ilo�� element�w w li�cie.
 */
int RozmiarListyOsobnikow(Osobnik* pHead);

/**
 * Funkcja zwraca ilo�� osobnik�w w li�cie zdolnych do rozmna�ania (z warto�ci� funkcji dopasowania powy�ej wsp�czynnika podanego jako prze��cznik).
 * @param pHead Wska�nik na pierwszy element listy osobnik�w.
 * @param WspolczynnikRozmnazania Wsp�czynnik rozmna�ania, podany jako prze��cznik.
 * @return Ilo�� zdolnych do rozmna�ania osobnik�w.
 */
int IloscZdolnychOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania);

/**
 * Dodaje osobnika przekazanego jako parametr do danej listy osobnik�w.
 * @param pHead Wska�nik na pierwszy element listy, do kt�rej nale�y doda� nowego osobnika.
 * @param pChromosom Wska�nik na pierwszy element listy chromosom�w dodawanego osobnika.
 * @param dopasowanie Warto�� funkcji dopasowania doawanego osobnika.
 */
void DodajDoListyOsobnikow(Osobnik*& pHead, Chromosom* pChromosom, double dopasowanie);

/**
 * Dodaje warto�� przekazan� jako parametr do danej listy chromosom�w osobnika.
 * @param pHead Wska�nik na pierwszy element listy chromosom�w, do kt�rej nale�y doda� now� warto��.
 * @param wartosc Liczba naturalna kt�r� dodajemy do listy.
 */
void DodajDoListyChromosomow(Chromosom*& pHead, int wartosc);

/**
 * Funkcja losuje dla osobnika warto�� dopasowania z przedzia�u [0;1].
 * @return Wylosowana warto�� funkcji dopasowania.
 */
double WylosujFunkcjeDopasowania();

/**
 * Usuwa list� jednokierunkow� chromosomu.
 * @param pHead Wska�nik na pierwszy element listy chromosom�w, kt�r� usuwamy.
 */
void UsunListeChromosomow(Chromosom*& pHead);

/**
 * Usuwa list� jednokierunkow� osobnik�w. Domy�lnie funkcja ta wywo�ywana jest na koniec programu.
 * @param pHead Wska�nik na pierwszy element listy osobnik�w, kt�r� usuwamy.
 */
void UsunListeOsobnikow(Osobnik*& pHead);

/**
 * Losowo wybiera dw�ch osobnik�w do krzy�owania si� z listy wszystkich osobnik�w, i zwraca list� jednokierunkow� zawieraj�c� obu z nich.
 * @param pHead Wska�nik na pierwszy element listy wszystkich osobnik�w.
 * @param WspolczynnikRozmnazania Wsp�czynnik rozmna�ania podany jako prze��cznik.
 * @return Dwuelementowa lista jednokierunkowa zawieraj�ca osobniki do krzy�owania si�.
 */
Osobnik* WylosujPareOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania);

/**
 * Usuwa z populacji osobniki, kt�re maj� warto�� funkcji dopasowania poni�ej progu podanego jako prze��cznik.
 * @param pHead Wska�nik na pierwszy element listy osobnik�w.
 * @param WspolczynnikWymierania Wsp�czynnik wymierania podany jako prze��cznik.
 */
void UsunOsobnikowZPopulacji(Osobnik*& pHead, double WspolczynnikWymierania);

/**
 * Rozmna�a osobniki i zwraca potomka powsta�ego wskutek p�kni�cia chromosom�w krzy�uj�cych si� osobnik�w.
 * @param pHead Wska�nik na pierwszy element listy osobnik�w, do kt�rej dodany zostanie nowy osobnik.
 * @param pierwszy Pierwszy z osobnik�w do rozmno�enia.
 * @param drugi Drugi z osobnik�w do rozmno�enia.
 * @param WspolczynnikRozmnazania Wsp�czynnik rozmna�ania podany jako prze��cznik.
 * @return Osobnik powsta�y wskutek rozmna�ania.
 * @note Funkcja zwr�ci nullptr je�eli kt�rykolwiek z osobnik�w jest niezdolny do rozmna�ania (ma warto�� funkcji dopasowania poni�ej progu).
 */
Osobnik* Rozmnoz(Osobnik*& pHead, Osobnik* pierwszy, Osobnik* drugi, double WspolczynnikRozmnazania);

/**
 * Symuluje nast�pne pokolenie osobnik�w.
 * @param pHead Wska�nik na pierwszy element listy osobnik�w.
 * @param LiczbaParOsobnikow Liczba par osobnik�w do rozmno�enia w ka�dym pokoleniu, podana jako prze��cznik.
 * @param WspolczynnikWymierania Wsp�czynnik wymierania podany jako prze��cznik.
 * @param WspolczynnikRozmnazania Wsp�czynnik rozmna�ania podany jako prze��cznik.
 * @note Po wykonaniu funkcji lista wskazywana przez pHead b�dzie zawiera�a nowo-stworzonych osobnik�w.
 */
void NastepnePokolenie(Osobnik*& pHead, int LiczbaParOsobnikow, double WspolczynnikWymierania, double WspolczynnikRozmnazania);