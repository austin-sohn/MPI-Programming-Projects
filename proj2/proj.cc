// Austin Sohn
// proj.cc
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
}

std::vector<int> getSubMatrix(std::vector<std::vector<int>> m, int col,
                              int row) {
  std::vector<int> sub;

  for (int i = 0; i < SUB_MATRIX_SIZE; i++) {
    for (int j = 0; j < SUB_MATRIX_SIZE; j++) {
      sub.push_back(m[i + col][j + row]);
    }
    // sub.push_back(temp);
  }

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
  std::vector<int> sub2;
  MPI_Init(&argc, &argv);
  MPI_Status stat;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int n = 4; // 2x2 vector

  // std::vector<std::vector<int>> sub;
  //  Now process 0 can receive from the last process.
  std::string line;
  std::vector<std::vector<int>> matrix;
  std::vector<int> maxSum;
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
    // ---

    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - 1; j++) {
        sub2 = getSubMatrix(matrix, i, j);
        MPI_Send(sub2.data(), sub2.size(), MPI_INT, (rank + 1) % size, 0,
                 MPI_COMM_WORLD);
        std::cout << "sent\n";
        for (int i = 0; i < sub2.size(); i++) {
          std::cout << sub2[i] << " ";
        }
        std::cout << std::endl;
      }
    }
  }

  else {
    std::cout << "rank: " << rank << std::endl;
    sub2.resize(4);
    MPI_Recv(sub2.data(), sub2.size(), MPI_INT, (rank - 1) % size, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "received";
    int sum = 0;
    for (int i = 0; i < 4; i++) {
      sum += sub2[i];
      if (maxSum.empty() || maxSum[maxSum.size() - 1] < sum) {
        maxSum.push_back(sum);
      }
    }
    std::cout << "\nsum: " << sum << std::endl;
    maxSum.push_back(sum);
    // else if (maxSum[maxSum.size() - 1] < sum) { // last element will be max
    //   maxSum.push_back(sum);
    // }
    // for (int i = 0; i < maxSum.size() - 1; i++) {
    //   std::cout << maxSum[i] << " ";
    // }
    // std::cout << std::endl;
  }
  // std::cout << "maxSum: ";
  // for (int i = 0; i < maxSum.size(); i++) {
  //   std::cout << maxSum[i] << " ";
  // }
  // std::cout << "\n";

  MPI_Finalize();

  return 0;
}