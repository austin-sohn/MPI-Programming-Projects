#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  float A[2] = {2 * rank + 0.5, -2 * rank + 0.5};
  float B[20] = {0, 0, 0, 0};
  std::cout << "Process " << rank << " has array A[]=(" << A[0] << "," << A[1]
            << "), and array B[]=(" << B[0] << ")\n"
            << std::endl;
  for (int i = 0; i < 20; i++) {
    B[i] = 0.0;
  }
  std::cout << "Process " << rank << " has array A[]=(" << A[0] << "," << A[1]
            << "), and array B[]=(" << B[0] << "," << B[1] << "," << B[2] << ","
            << B[3] << "," << B[3] << ")\n"
            << std::endl;
  MPI_Scan(A, B, 1, MPI_FLOAT, MPI_PROD, MPI_COMM_WORLD);
  std::cout << "After partial parallel reducing, process " << rank
            << " has array B[]=(" << B[0] << "," << B[1] << "," << B[2] << ","
            << B[3] << "," << B[3] << ")\n"
            << std::endl;

  MPI_Finalize();
  return 0;
}