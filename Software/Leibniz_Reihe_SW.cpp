#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <mpi.h>


long double calc_PI(int step_Size, int start_Point) {
        long double sum = 0;
        for (int k = start_Point; k <= 3000000; k=k+step_Size)
        {
                sum += pow(-1, k) / (2 * k + 1);
        }
        return sum;
}

int main (int argc, char** argv)
{
		std::cout << "Programm ist gestartet" << std::endl;
		
        int size, rank, length;
		long double sum = 0;

        // initialisation of mpi
        MPI_Init(&argc, &argv);
        // get my rank
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        // get number of rank
        MPI_Comm_size(MPI_COMM_WORLD, &size);
		
		MPI_Status status;
		
        // output
		std::cout << "Number of Ranks: " << size << std::endl;

        // slave
        if (rank!=0)
        {
			std::cout << "Slave " << rank << " fuehrt Berechnung durch" << std::endl;
			sum = calc_PI(size-1, rank-1);
			// send
			length = sizeof(sum);
			
			//MPI_Send( &length,sizeof(length) , MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Send(&sum, length , MPI_LONG_DOUBLE, 0, 1, MPI_COMM_WORLD);
        }

		// master
		if (rank==0)
		{
			// start of calculation
			std::cout << "Rank of Master: " << rank << std::endl;
			
			if (size==1)
			{
				//sum = calc_PI(1,0); //calc_PI(int step_Size, int start_Point)
			}
			
			//MPI_Recv(&length, 50, MPI_LONG_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&sum, 50, MPI_LONG_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);
			
					// output
			std::cout << "Sum: " << sum << std::endl;
	
			// sum into pi as result
			long double pi = sum * 4;
	
			// output
			std::cout << "PI: " << std::setprecision(50) << pi << std::endl;
		}

		


        //std::cout << "Run-Time: " << time << std::endl;

        // end of mpi
        return(MPI_Finalize());
}
