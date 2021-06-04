#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {

  long int N = 1000000000; // 10^9 Werte
  long int treffer = 0, alle_treffer = 0;
  long int i, my_n;
  int rank, size, length;
  double start, end;
  char name[80];
  
  MPI_Status status;
  MPI_Init(&argc, &argv);
  start = MPI_Wtime();
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(name, &length);

  my_n = N / size;
  if (rank == 0) my_n += (N - size*my_n); // Teilerrest
  cout << "Rank " << rank << " fuehrt " << my_n << " Berechnungen durch." << endl;
  srand(rank);

  for (i=0; i<my_n; i++) {
    double x = (double) rand() / (double) RAND_MAX;
    double y = (double) rand() / (double) RAND_MAX;
    if (x*x+y*y < 1) treffer++;
  }

  MPI_Reduce(&treffer, &alle_treffer, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank==0) {
    cout << "Rank " << rank << " auf host " << name << " registrierte " 
	   << treffer << " Treffer." << endl;
    for (int j=1;j<size;j++) {
      MPI_Recv(name,80,MPI_CHAR,j,999,MPI_COMM_WORLD,&status);
      MPI_Recv(&treffer,1,MPI_INT,j,999,MPI_COMM_WORLD,&status);
      cout << "Node " << j << " auf host " << name << " registrierte " 
	   << treffer << " Treffer." << endl;
    }
    cout << "Insgesamt gab es " << alle_treffer << " Treffer." << endl;
    end = MPI_Wtime();
    cout << endl << size << " Prozesse: pi ist etwa " << setprecision(12) << setw(12)
	 << 4*((double)alle_treffer/(double)N)
         << "; Rechenzeit: " <<  end-start << "s" << endl;
  } else {
    MPI_Send(name,80,MPI_CHAR,0,999,MPI_COMM_WORLD);
    MPI_Send(&treffer,1,MPI_INT,0,999,MPI_COMM_WORLD);

  }

  MPI_Finalize();
  return 0;
}
