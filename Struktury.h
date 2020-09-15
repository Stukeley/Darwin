/**
 * @file
 */
#pragma once

 //lista osobnikow z podwieszona lista chromosomow

 /**
  * Struktura odpowiedzialna za liste jednokierunkowa chromosomow.
  */
struct Chromosom
{
	int liczba;			///< liczba naturalna bedaca chromosomem
	Chromosom* pNext;	///< wskaznik na kolejny element listy chromosomow
};

/**
 *	Struktura odpowiedzialna za liste jednokierunkowa osobnikow.
 */
struct Osobnik
{
	double dopasowanie;		///< wartosc funkcji dopasowania z przedzialu [0;1] - wartosc -1 oznacza "jeszcze nie wylosowano"
	Chromosom* chromosom;	///< wskaznik na pierwszy element listy jednokierunkowej chromosomow
	Osobnik* pNext;			///< wskaznik na kolejny element listy osobnikow
};