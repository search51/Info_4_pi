// amk.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <time.h>
double a;
int iteration ;

//rechenoperationsfunktion dient als vereinfachte idee hinter leibniz reihe
 int testfunktion(int rank, int iteration) {
	 a = 0;
	// for welche den jedes mal die erste bzw 3 vierte zahl nimmt eventuell anpassung mit variabeler hochzählung 
	for (int i = rank; i <= iteration; i+= 4) {
	// for (int i = 0; i <= iteration; i++) {
		a+=i;
		
		//std::cout << "das ergebnis von "<< rank <<"ist:" << i << std::endl;
				//+rank "und bin ein hs\n"<<std::end;
		}
	
	return a;
}
 //hat den sinn zzm vergleich
 int testfunktiondie1(int rank, int iteration) {
	 a = 0;
	 // for welche den jedes mal die erste bzw 3 vierte zahl nimmt eventuell anpassung mit variabeler hochzählung 
	 
		 for (int i = 0; i <= iteration; i++) {
		 a += i;

		// std::cout << "das ergebnis von " << rank << "ist:" << i << std::endl;
		 //+rank "und bin ein hs\n"<<std::end;
	 }

	 return a;
 }

 //soll die viertuelle maschine ersetzen bzw als logik dahinter dienen
int worker1(int rank, long int summ1) {
	///std::cout << "hello ich bin worker" << rank << std::endl;
	summ1 =testfunktion(rank, iteration);
	
	return summ1;
}


int worker2(int rank, double summ2) {
	//std::cout << "hello ich bin worker" << rank << std::endl;
	summ2 = testfunktion(rank, iteration);
	return summ2;
}


int worker3(int rank, double summ3) {
	//std::cout << "hello ich bin worker" << rank << std::endl;
	summ3 = testfunktion(rank, iteration);
		return summ3;
}


int worker4(int rank, double summ4) {
	//std::cout << "hello ich bin worker" << rank << std::endl;
	summ4 = testfunktion(rank, iteration);
	return summ4;
}

//
int main()
{
	double time = 0.0, tstart;

	tstart = clock();

	double zahl;
	iteration = 100000;
	//zählt die ergebnisse zurück wäre nach mpi analog das gesendete ergebnis 
	zahl = worker1(1, 0)+worker2(2,0) + worker3(3, 0) + worker4(4, 0);
	
	//zahl = testfunktiondie1(0,iteration);
	 
	std::cout << "miau miau ich bin ein hau hau:" << zahl << std::endl;
	time += clock() - tstart;

	time = time / CLOCKS_PER_SEC;
	std::cout << "Laufzeit: " << time;
	return 0;
}
