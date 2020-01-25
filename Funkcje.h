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
 * Funkcja wczytuje osobniki z pliku wejœciowego i zapisuj¹ca ich do listy jednokierunkowej osobników podwieszonej list¹ DNA (chromosomem).
 * @param Wejscie Nazwa pliku wejœciowego podana jako prze³¹cznik.
 * @return Lista osobników wczytanych z pliku.
 * @note Parametr jest przekazywany przez referencjê, gdy¿ i tak nie jest modyfikowany przez funkcjê.
 */
Osobnik* WczytajOsobnikowZPliku(string& Wejscie);

/**
 * Funkcja zapisuje obecny stan populacji do pliku wejœciowego o nazwie podanej jako prze³¹cznik.
 * @param pHead WskaŸnik na pierwszy element listy osobników.
 * @param Wyjscie Nazwa pliku wyjœciowego podana jako prze³¹cznik.
 * @note Parametr jest przekazywany przez referencjê, gdy¿ i tak nie jest modyfikowany przez funkcjê.
 */
void ZapiszOsobnikowDoPliku(Osobnik* pHead, string& Wyjscie);

/**
 * Funkcja zwraca iloœæ elementów w liœcie jednokierunkowej chromosomów.
 * @param pHead WskaŸnik na pierwszy element listy chromosomów.
 * @return Iloœæ elementów w liœcie.
 */
int RozmiarListyChromosomow(Chromosom* pHead);

/**
 * Funkcja zwraca iloœæ elementów w liœcie jednokierunkowej osobników.
 * @param pHead WskaŸnik na pierwszy element listy osobników.
 * @return Iloœæ elementów w liœcie.
 */
int RozmiarListyOsobnikow(Osobnik* pHead);

/**
 * Funkcja zwraca iloœæ osobników w liœcie zdolnych do rozmna¿ania (z wartoœci¹ funkcji dopasowania powy¿ej wspó³czynnika podanego jako prze³¹cznik).
 * @param pHead WskaŸnik na pierwszy element listy osobników.
 * @param WspolczynnikRozmnazania Wspó³czynnik rozmna¿ania, podany jako prze³¹cznik.
 * @return Iloœæ zdolnych do rozmna¿ania osobników.
 */
int IloscZdolnychOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania);

/**
 * Dodaje osobnika przekazanego jako parametr do danej listy osobników.
 * @param pHead WskaŸnik na pierwszy element listy, do której nale¿y dodaæ nowego osobnika.
 * @param pChromosom WskaŸnik na pierwszy element listy chromosomów dodawanego osobnika.
 * @param dopasowanie Wartoœæ funkcji dopasowania doawanego osobnika.
 */
void DodajDoListyOsobnikow(Osobnik*& pHead, Chromosom* pChromosom, double dopasowanie);

/**
 * Dodaje wartoœæ przekazan¹ jako parametr do danej listy chromosomów osobnika.
 * @param pHead WskaŸnik na pierwszy element listy chromosomów, do której nale¿y dodaæ now¹ wartoœæ.
 * @param wartosc Liczba naturalna któr¹ dodajemy do listy.
 */
void DodajDoListyChromosomow(Chromosom*& pHead, int wartosc);

/**
 * Funkcja losuje dla osobnika wartoœæ dopasowania z przedzia³u [0;1].
 * @return Wylosowana wartoœæ funkcji dopasowania.
 */
double WylosujFunkcjeDopasowania();

/**
 * Usuwa listê jednokierunkow¹ chromosomu.
 * @param pHead WskaŸnik na pierwszy element listy chromosomów, któr¹ usuwamy.
 */
void UsunListeChromosomow(Chromosom*& pHead);

/**
 * Usuwa listê jednokierunkow¹ osobników. Domyœlnie funkcja ta wywo³ywana jest na koniec programu.
 * @param pHead WskaŸnik na pierwszy element listy osobników, któr¹ usuwamy.
 */
void UsunListeOsobnikow(Osobnik*& pHead);

/**
 * Losowo wybiera dwóch osobników do krzy¿owania siê z listy wszystkich osobników, i zwraca listê jednokierunkow¹ zawieraj¹c¹ obu z nich.
 * @param pHead WskaŸnik na pierwszy element listy wszystkich osobników.
 * @param WspolczynnikRozmnazania Wspó³czynnik rozmna¿ania podany jako prze³¹cznik.
 * @return Dwuelementowa lista jednokierunkowa zawieraj¹ca osobniki do krzy¿owania siê.
 */
Osobnik* WylosujPareOsobnikow(Osobnik* pHead, double WspolczynnikRozmnazania);

/**
 * Usuwa z populacji osobniki, które maj¹ wartoœæ funkcji dopasowania poni¿ej progu podanego jako prze³¹cznik.
 * @param pHead WskaŸnik na pierwszy element listy osobników.
 * @param WspolczynnikWymierania Wspó³czynnik wymierania podany jako prze³¹cznik.
 */
void UsunOsobnikowZPopulacji(Osobnik*& pHead, double WspolczynnikWymierania);

/**
 * Rozmna¿a osobniki i zwraca potomka powsta³ego wskutek pêkniêcia chromosomów krzy¿uj¹cych siê osobników.
 * @param pHead WskaŸnik na pierwszy element listy osobników, do której dodany zostanie nowy osobnik.
 * @param pierwszy Pierwszy z osobników do rozmno¿enia.
 * @param drugi Drugi z osobników do rozmno¿enia.
 * @param WspolczynnikRozmnazania Wspó³czynnik rozmna¿ania podany jako prze³¹cznik.
 * @return Osobnik powsta³y wskutek rozmna¿ania.
 * @note Funkcja zwróci nullptr je¿eli którykolwiek z osobników jest niezdolny do rozmna¿ania (ma wartoœæ funkcji dopasowania poni¿ej progu).
 */
Osobnik* Rozmnoz(Osobnik*& pHead, Osobnik* pierwszy, Osobnik* drugi, double WspolczynnikRozmnazania);

/**
 * Symuluje nastêpne pokolenie osobników.
 * @param pHead WskaŸnik na pierwszy element listy osobników.
 * @param LiczbaParOsobnikow Liczba par osobników do rozmno¿enia w ka¿dym pokoleniu, podana jako prze³¹cznik.
 * @param WspolczynnikWymierania Wspó³czynnik wymierania podany jako prze³¹cznik.
 * @param WspolczynnikRozmnazania Wspó³czynnik rozmna¿ania podany jako prze³¹cznik.
 * @note Po wykonaniu funkcji lista wskazywana przez pHead bêdzie zawiera³a nowo-stworzonych osobników.
 */
void NastepnePokolenie(Osobnik*& pHead, int LiczbaParOsobnikow, double WspolczynnikWymierania, double WspolczynnikRozmnazania);