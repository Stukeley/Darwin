#pragma once

//lista osobników z podwieszon¹ list¹ chromosomów

/**
 * Struktura odpowiedzialna za listê jednokierunkow¹ chromosomów.
 */
struct Chromosom
{
	int liczba;			///< liczba naturalna bêd¹ca chromosomem
	Chromosom* pNext;	///< wskaŸnik na kolejny element listy chromosomów
};

/**
 * Struktura odpowiedzialna za listê jednokierunkow¹ osobników.
 */
struct Osobnik
{
	double dopasowanie;		///< wartoœæ funkcji dopasowania z przedzia³u [0;1]
	Chromosom* chromosom;	///< wskaŸnik na pierwszy element listy jednokierunkowej chromosomów
	Osobnik* pNext;			///< wskaŸnik na kolejny element listy osobników
};