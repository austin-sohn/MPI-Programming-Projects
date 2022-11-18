#include <iostream>
#include <mpi.h>
using namespace std;

// int main(int argc, char *argv[]){
//   int rank, size;
//   MPI_Init( &argc, &argv );
//   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
//   MPI_Comm_size( MPI_COMM_WORLD, &size );
//   cout << "I am " << rank << " of " << size << endl;
//   int number=0;
//   cout << "Process " << rank << " has number = " << number << endl;
//   if (rank == 3) {
//     number = 100;
//     cout << "At rank " << rank << ", value of number is " << number << endl;
//     MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
//     cout << "Process " << rank << " sent number " << number << " to process
//     1\n";
//   }
//   else if (rank == 1) {
//     cout << "At rank " << rank << ", value of number is " << number << endl;
//     MPI_Recv(&number, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//     cout << "Process " << rank << " received number " << number << " to
//     process 3\n";
//   }
//   MPI_Finalize();
//   return 0;
// }

int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  cout << "I am " << rank << " of " << size << endl;
  int A[3] = {0, 0, 0};

  cout << "Process " << rank << " has array = " << A[0] << ", " << A[1] << ", "
       << A[2] << endl;
  if (rank == 3) {
    A[0] = A[1] = A[2] = -10;
    cout << "At rank " << rank << ", value of number is " << A[0] << ", "
         << A[1] << ", " << A[2] << endl;
    MPI_Send(A, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
    cout << "Process 0 " << rank << " sent array " << A[0] << ", " << A[1]
         << ", " << A[2] << " to process 1\n";
  } else if (rank == 1) {
    cout << "At rank " << rank << ", value of number is " << A[0] << ", "
         << A[1] << ", " << A[2] << endl;
    MPI_Recv(A, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cout << "Process 1 " << rank << " received array " << A[0] << ", " << A[1]
         << ", " << A[2] << " to process 3\n";
  }
  MPI_Finalize();
  return 0;
}