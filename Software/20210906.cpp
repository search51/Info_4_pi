long double calc_PI(int step_Size, int start_Point) {
        long double sum = 0;
        for (int k = 0; k <= 3000000; k++)
        {
                sum += pow(-1, k) / (2 * k + 1);
        }
        return sum;
}

int main (int argc, char** argv)
{
        int size, rank, length;
        char name[50];

        // initialisation of mpi
        MPI_Init(&argc, &argv);
        // get my rank
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        // get number of rank
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        // get processor name
        MPI_Get_processor_name(name, &length);
        // output file name
        const char OUTPUT_FILE_NAME[] = "ouput.txt";
        // define master root rank
        const int MASTER_ROOT_RANK = 0;
        // output
        std::cout << "Rank: " << rank << std::endl << "Size: " << size << std::>

        // define start time
        double time = o.0, tstart;
        tstart = clock();

        // define sum
        long double sum = 0;

        //
        if (rank==0)
        {

           std::cout << "Rank " << rank << " fuehrt Berechnung durch" << std::e>

        }

	// output
        std::cout << "Sum: " << sum << std::endl;

        // sum into pi as result
        long double pi = sum * 4;

        // calculate run-time
        time += clock() - tstart;
        time = time / CLOCKS_PER_SEC;

        // output
        std::cout << "PI: " << std::setprecision(50) << pi << std::endl;
        std::cout << "Run-Time: " << time << std::endl;

        // end of mpi
        return(MPI_Finalize());
}
