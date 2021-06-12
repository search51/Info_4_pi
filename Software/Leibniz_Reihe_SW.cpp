#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <mpi.h>


long double calc_PI(int step_Size, int start_Point) {
        long double sum = 0;
        for (int k = start_Point; k <= 300000000; k += step_Size)
        {
                sum += pow(-1, k) / (2 * k + 1);
        }
        return sum;
}

int main (int argc, char** argv)
{		
        int size, rank, length;
		long double sum = 0;

        // initialisation of mpi
        MPI_Init(&argc, &argv);
        // get my rank
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        // get number of rank
        MPI_Comm_size(MPI_COMM_WORLD, &size);
		
		MPI_Status status;

		// Beginn der Laufzeitmessung
		double time = 0.0, tstart;
		tstart = clock();

        // slave
        if (rank!=0)
        {
			long double help_sum = 0;
			help_sum = calc_PI(size-1, rank-1);

			//std::cout << "Ergebnis der Berechnung: " << help_sum;
			
			//MPI_Send( &length,sizeof(length) , MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Send(&help_sum, 1 , MPI_LONG_DOUBLE, 0, 1, MPI_COMM_WORLD);
			std::cout << std::endl << "##### SLAVE " << rank << " ##### Ergebnis: " << std::setprecision(5) << help_sum << std::endl;
        }

		// master
		if (rank==0)
		{
			long double help_sum = 0;
			std::cout << std::endl << "##### MASTER #####" << std::endl;
			
			if (size==1)
			{
				sum = calc_PI(1,0); //calc_PI(int step_Size, int start_Point)
			}
			else {
				for (int i = 1; i < size; i++)
				{
					//MPI_Recv(&length, 50, MPI_LONG_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);
					MPI_Recv(&help_sum, 1, MPI_LONG_DOUBLE, i, 1, MPI_COMM_WORLD, &status);
					// Ausgabe der empfangenen Daten
					std::cout << "Received Message Number " << i << ": " << help_sum << std::endl;
					// Addition der Hilfssumme zur Hauptsumme
					sum += help_sum;
				}
			}

			// sum into pi as result
			long double pi = sum * 4;
	
			// output
			std::cout << std::endl << "PI: " << std::setprecision(50) << pi << std::endl;
			// Berechnung und Ausgabe der Laufzeit
			time += clock() - tstart;
			time = time / CLOCKS_PER_SEC;
			std::cout << "Laufzeit: " << std::setprecision(4) << time << std::endl;
		}

		// Berechnung und Ausgabe der Laufzeit
		//time += clock() - tstart;
		//time = time / CLOCKS_PER_SEC;
		//std::cout << std::endl << "Laufzeit: " << time << std::endl;

        //std::cout << "Run-Time: " << time << std::endl;

        // end of mpi
        return(MPI_Finalize());
}
