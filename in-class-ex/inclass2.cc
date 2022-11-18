#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[]){
  int rank, size;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  int token;
  if (rank != 0) {
      MPI_Recv(&token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cout << "Rank " << rank << " received token " << token << " from process " << (rank-1) % size << endl;
  } else {
      // Set the token's value if you are process 0
      token = -1;
  }
  MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

  // Now process 0 can receive from the last process.
  if (rank == 0) {
      MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cout << "Rank " << rank << " received token " << token << " from process " << size - 1 << endl;
  }
  MPI_Finalize();
  return 0;
}