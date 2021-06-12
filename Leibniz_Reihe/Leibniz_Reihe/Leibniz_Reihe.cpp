// Leibniz_Reihe.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <mpi.h>


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
	// Variablen zur Beschreibung des Systems
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	double time = 0.0, tstart;

	tstart = clock();

	long double sum = 0;

	if (rank > 0) {
		sum = calc_PI(size, (rank - 1));
		std::cout << "Summe: " << sum;
		MPI_Send(&sum, 100000, MPI_LONG_DOUBLE, login_NODE, 123, );
	}
	

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
	std::cout << "PI: " << std::setprecision(50) << pi << std::endl;

	time += clock() - tstart;

	time = time / CLOCKS_PER_SEC;

   
	std::cout << "Laufzeit: " << time;
	
	MPI_Finalize();
}

