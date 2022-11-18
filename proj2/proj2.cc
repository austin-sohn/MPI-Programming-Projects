// Austin Sohn
// proj2.cc
// 12/3/22
// mpic++ proj2.cc
// mpirun -n <# of times> a.out

// 2. Identifying the submatrix of 2x2 with the largest sum of values:
// Given a very large (n>10) matrix of n x n elements, write a distributed
// program in MPI that outputs a submatrix of size 2x2 with the largest sum of
// its elements and its relative position or displacement (row-column of the top
// left element) in the original matrix. There will be only one process with
// rank 0, that will read the file name with the input data, read from the file
// the value of n, read from the file the entire matrix, and will output the
// submatrix of size 2x2 with the largest sum of its elements and its position
// on the screen. All the other processes will receive portions of the matrix
// and contribute to identifying the submatrix.

#include <fstream>
#include <iostream>
#include <mpi.h>
#include <stdexcept>
#include <string>
#include <vector>

const int SUB_MATRIX_SIZE = 2;

void print(std::vector<std::vector<int>> m) {
  std::cout << "in print\n";
  int i, j, k;
  for (i = 0; i < m[0].size() - 1; i++) {
    for (j = 0; j < m[0].size() - 1; j++) {
      std::cout << m[i][j] << " ";
    }
    std::cout << m[i][j] << std::endl;
  }
  for (k = 0; k < m[i].size() - 1; k++) {
    std::cout << m[j][k] << " ";
  }
  std::cout << m[j][k] << std::endl;
  std::cout << "out print\n";
}

// std::vector<std::vector<int>> getSubMatrix(std::vector<std::vector<int>> m,
//                                            int col, int row) {
//   std::vector<std::vector<int>> sub;

//   for (int i = 0; i < SUB_MATRIX_SIZE; i++) {
//     std::vector<int> temp;
//     for (int j = 0; j < SUB_MATRIX_SIZE; j++) {
//       temp.push_back(m[i + col][j + row]);
//     }
//     sub.push_back(temp);
//   }

//   return sub;
// }

int *getSubMatrix(std::vector<std::vector<int>> m, int col, int row) {
  static int sub[4];

  for (int i = 0; i < SUB_MATRIX_SIZE; i++) {
    for (int j = 0; j < SUB_MATRIX_SIZE; j++) {
      sub[i * SUB_MATRIX_SIZE + j] = (m[i + col][j + row]);
      // std::cout << sub[i * SUB_MATRIX_SIZE + j] << " ";
    }
    // std::cout << std::endl;
  }
  // std::cout << "----------\n";
  return sub;
}
int addSubMatrix(std::vector<std::vector<int>> m) {
  int sum = 0;
  for (int i = 0; i < SUB_MATRIX_SIZE; i++) {
    for (int j = 0; j < SUB_MATRIX_SIZE; j++) {
      sum += m[i][j];
    }
  }
  return sum;
}

int main(int argc, char *argv[]) {
  // remove later
  int rank, size;
  // std::vector<int> sub2;
  std::vector<int> sub4;
  sub4.push_back(1);
  sub4.push_back(2);
  sub4.push_back(3);
  sub4.push_back(4);
  int *sub2;
  int arr[5];
  int sub3[4] = {0, 1, 2, 3};
  MPI_Init(&argc, &argv);
  MPI_Status stat;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // std::cout << "rank is: " << rank << std::endl;
  int n = 4; // 2x2 vector
  int token;

  std::vector<std::vector<int>> sub;
  // Now process 0 can receive from the last process.
  std::string line;
  std::vector<std::vector<int>> matrix;
  if (rank == 0) {
    std::ifstream matrix_csv("matrix.csv");
    if (!matrix_csv.is_open())
      throw std::runtime_error("Could not open file");

    else {
      int i = 0, j;
      // puts csv matrix into a 2d vector
      while (std::getline(matrix_csv, line)) {
        // std::cout << "line: " << line << std::endl;
        std::vector<int> m;
        std::string temp = line;
        for (j = 0; j < line.size() / 2; j++) {
          if (temp.find(',') != -1) {
            int num = std::stoi(temp.substr(0, temp.find(',')));
            m.push_back(num);
            temp = temp.substr(temp.find(',') + 1);
          }
        }
        m.push_back(std::stoi(temp));
        matrix.push_back(m);
        i++;
      }
    }
    // closes file
    matrix_csv.close();

    n = matrix.size();

    // get sub matrix

    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - 1; j++) {
        sub2 = getSubMatrix(matrix, i, j);
        // sub2.push_back(sub[i][j]);
        // for (int f = 0; f < sub2.size(); f++) {
        //   std::cout << sub2[f] << " ";
        // }
        // std::cout << std::endl;
        // starts sending
        // MPI_Send(&sub2[j], n, MPI_INT, 1, 0, MPI_COMM_WORLD);
        // std::cout << "sending\n";
        // std::cout << "-------------\n";
      }

      // std::cout << "size: " << size << std::endl;

      // MPI_Send(&sub2[0], n, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
      // MPI_Send(&sub2[i + 1], n, MPI_INT, (rank + 1) % size, 0,
      // MPI_COMM_WORLD);
    }
    int arrsize = 4;
    std::cout << "sadge: ";
    for (int i = 0; i < arrsize; i++) {
      std::cout << sub2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "sub2.size()= " << arrsize << std::endl;
    MPI_Send(sub3, 4, MPI_INT, 1, 0, MPI_COMM_WORLD);
    // getting 1 sub matrix test

    // for (int i = 0; i < n; i++) {
    //   // std::cout << "push: ";
    //   for (int j = 0; j < n - 1; j++) {
    //     for (int k = 0; k < n - 1; k++) {
    //       sub = getSubMatrix(matrix, j, k);
    //       for (int f = 0; f < 2; f++) {
    //         for (int g = 0; g < 2; g++) {
    //           std::cout << sub[f][g] << " ";
    //         }
    //         std::cout << std::endl;
    //       }
    //       std::cout << "--------" << std::endl;
    //       sub2.push_back(sub[j][k]);
    //       // std::cout << sub[j][k] << " ";
    //     }
    //   }
    //   // std::cout << std::endl;
    //   MPI_Send(&sub2[i], 4, MPI_INT, 1, 0, MPI_COMM_WORLD);
    //   // std::cout << "sending: " << rank << "\n";
    // }
  }

  else if (rank == 1) {
    std::cout << "rank: " << rank << std::endl;
    std::cout << "n: " << n << std::endl;
    // sub2.resize(n);

    MPI_Recv(sub3, 4, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //  MPI_Recv(&sub2[rank], n, MPI_INT, 0, 0, MPI_COMM_WORLD,
    //  MPI_STATUS_IGNORE);
    int sum = 0;
    std::vector<int> maxSum;
    // std::cout << "receiving\n";
    // for (int i = 0; i < 4; i++) {
    //   std::cout << sub2[i] << " ";
    //   sum += sub2[i];

    //   if (maxSum[maxSum.size()] < sum) { // last element will be max
    //     maxSum.push_back(sum);
    //   }
    //   std::cout << "\nsum: " << sum << std::endl;
    // }

    std::cout << "maxSum: " << maxSum[maxSum.size()] << std::endl;
    //  std::cout << "sub[0][0]: " << sub[0][0] << std::endl;
    //   int sum = addSubMatrix(sub);
    //   std::cout << "Rank " << rank << " received token " << token
    //             << " from process " << (rank - 1) % size << std::endl;
  }

  MPI_Finalize();
  return 0;
}