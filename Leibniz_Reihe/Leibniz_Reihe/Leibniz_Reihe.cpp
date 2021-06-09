// Leibniz_Reihe.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <time.h>


long double calc_PI(int step_Size, int start_Point) {
	long double sum = 0;
	for (int k = 0; k <= 3000000; k++)
	{
		sum += pow(-1, k) / (2 * k + 1);
	}
	return sum;
}


int main()
{
	double time = 0.0, tstart;

	tstart = clock();

	long double sum = 0;

	sum = calc_PI(2, 0);
	std::cout << "Summe: " << sum;
	

	//long double sum = 0;
	//for (int k = 0; k <= 300000000; k++)
	//{
	//	sum += pow(-1, k) / (2 * k + 1);
	//}

	//for (int k = 1; k <= 300000000; k+=2)
	//{
	//	sum += pow(-1, k) / (2 * k + 1);
	//}

	long double pi = sum * 4;

	time += clock() - tstart;

	time = time / CLOCKS_PER_SEC;

    std::cout << "PI: " << std::setprecision(50) << pi << std::endl; 
	std::cout << "Laufzeit: " << time;
}

