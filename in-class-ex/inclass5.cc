#include <iostream>
#include <mpi.h>

// SCATTER
int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  //  std::cout << "I am rank " << rank << " of " << size << " processes \n";
  int A[20] = {0, 0, 0, 0, 0};
  int B[5] = {0, 0, 0, 0, 0};
  std::cout << "Process " << rank << " has array A[]=(" << A[0] << "," << A[1]
            << "," << A[2] << "," << A[3] << "," << A[4] << ")\n";
  std::cout << "Process " << rank << " has array B[]=(" << B[0] << "," << B[1]
            << "," << B[2] << "," << B[3] << "," << B[4] << ")\n";
  std::cout << "-------------\n\n";
  if (rank == 0)
    for (int i = 0; i < 20; i++)
      A[i] = 2 * (i + 1);
  std::cout << "Process " << rank << " has array A[]=(" << A[0] << "," << A[1]
            << "," << A[2] << "," << A[3] << "," << A[4] << ")\n";
  std::cout << "Process " << rank << " has array B[]=(" << B[0] << "," << B[1]
            << "," << B[2] << "," << B[3] << "," << B[4] << ")\n"
            << std::endl;
  MPI_Scatter(A, 2, MPI_INT, B, 2, MPI_INT, 0, MPI_COMM_WORLD);
  std::cout << "After scatter, process " << rank << " has array B[]=(" << B[0]
            << "," << B[1] << "," << B[2] << "," << B[3] << "," << B[4] << ")\n"
            << std::endl;
  MPI_Finalize();
  return 0;
}

// // GATHER
// int main(int argc, char *argv[]) {
//   int rank, size;
//   MPI_Init(&argc, &argv);
//   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//   MPI_Comm_size(MPI_COMM_WORLD, &size);
//   //  std::cout << "I am rank " << rank << " of " << size << " processe \n";
//   float A[2] = {2 * rank + 0.5, 3 * rank - 0.5};
//   float B[20] = {0.0, 0.0};
//   std::cout << "Process " << rank << " has array A[]=(" << A[0] << "," <<
//   A[1]
//             << ")\n"
//             << std::endl;
//   if (rank == 3)
//     for (int i = 0; i < 20; i++)
//       B[i] = 0.0;
//   std::cout << "Process " << rank << " has array A[]=(" << A[0] << "," <<
//   A[1]
//             << "), and array B[]=(" << B[0] << "," << B[1] << "," << B[2]
//             << B[3] << "," << B[4] << "," << B[5] << ")\n"
//             << std::endl;
//   MPI_Gather(A, 2, MPI_FLOAT, B, 2, MPI_FLOAT, 3, MPI_COMM_WORLD);
//   std::cout << "After gathering, process " << rank << " has array B[]=(" <<
//   B[0]
//             << "," << B[1] << "," << B[2] << "," << B[3] << "," << B[4] <<
//             ")\n"
//             << std::endl;
//   MPI_Finalize();
//   return 0;
// }
