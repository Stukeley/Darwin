#pragma once

//lista osobników z podwieszoną listą chromosomów

/**
 * Struktura odpowiedzialna za listę jednokierunkową chromosomów.
 */
struct Chromosom
{
	int liczba;			///< liczba naturalna będąca chromosomem
	Chromosom* pNext;	///< wskaźnik na kolejny element listy chromosomów
};

/**
 * Struktura odpowiedzialna za listę jednokierunkową osobników.
 */
struct Osobnik
{
	double dopasowanie;		///< wartość funkcji dopasowania z przedziału [0;1]
	Chromosom* chromosom;	///< wskaźnik na pierwszy element listy jednokierunkowej chromosomów
	Osobnik* pNext;			///< wskaźnik na kolejny element listy osobników
};