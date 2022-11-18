#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[]){
  int rank, size;
  double start , end;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );


  int A[5]= {0, 0, 0, 0, 0};
  cout << "Process " << rank << " has array A[]=(" << A[0] << "," <<
    A[1] << "," << A[2] <<  "," << A[3] << "," << A[4] << ")\n" << endl;
  if (rank == 0) {
    for(int i=0; i<5; i++) A[i] = i;
  }
  cout << "Process " << rank << " has array A[]=(" << A[0] << "," <<
    A[1] << "," << A[2] <<  "," << A[3] << "," << A[4] << ")\n" << endl;
  MPI_Bcast(A, 5, MPI_INT, 0, MPI_COMM_WORLD);
  cout << "Process " << rank << " has array A[]=(" << A[0] << "," <<
    A[1] << "," << A[2] <<  "," << A[3] << "," << A[4] << ")\n" << endl;

  MPI_Finalize();
  return 0;
}