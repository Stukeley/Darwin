#pragma once

//lista osobnik�w z podwieszon� list� chromosom�w

/**
 * Struktura odpowiedzialna za list� jednokierunkow� chromosom�w.
 */
struct Chromosom
{
	int liczba;			///< liczba naturalna b�d�ca chromosomem
	Chromosom* pNext;	///< wska�nik na kolejny element listy chromosom�w
};

/**
 * Struktura odpowiedzialna za list� jednokierunkow� osobnik�w.
 */
struct Osobnik
{
	double dopasowanie;		///< warto�� funkcji dopasowania z przedzia�u [0;1]
	Chromosom* chromosom;	///< wska�nik na pierwszy element listy jednokierunkowej chromosom�w
	Osobnik* pNext;			///< wska�nik na kolejny element listy osobnik�w
};