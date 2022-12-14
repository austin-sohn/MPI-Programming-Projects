// Austin Sohn
// proj2.cc
// 12/2/22

#include <fstream> // read and write csv file
#include <iostream>
#include <mpi.h>
#include <string>
#include <vector>

std::vector<int> getMaxSubMatrix(std::vector<int> s1, std::vector<int> s2) {
  std::vector<int> sub;
  int i, tl, tr, bl, br, sum;
  int max = s1[0] + s2[0] + s1[1] + s2[1];
  tl = s1[0];
  bl = s2[0];
  tr = s1[1];
  br = s2[1];
  for (i = 1; i < s1.size(); i++) {

    int sum = s1[i - 1] + s2[i - 1] + s1[i] + s2[i];
    if (sum > max) {
      max = sum;
      tl = s1[i - 1];
      bl = s2[i - 1];
      tr = s1[i];
      br = s2[i];
    }
  }
  sub.push_back(tl);
  sub.push_back(tr);
  sub.push_back(bl);
  sub.push_back(br);
  return sub;
}

std::vector<int> getPos(std::vector<std::vector<int>> matrix,
                        std::vector<int> subMatrix) {
  std::vector<int> pos;
  for (int i = 0; i < matrix.size() - 1; i++) {
    for (int j = 0; j < matrix.size() - 1; j++) {
      if (matrix[i][j] == subMatrix[0] && matrix[i][j + 1] == subMatrix[1] &&
          matrix[i + 1][j] == subMatrix[2] &&
          matrix[i + 1][j + 1] == subMatrix[3]) {
        pos.push_back(i + 1);
        pos.push_back(j + 1);
      }
    }
  }
  return pos;
}

int main(int argc, char *argv[]) {
  int rank, size; // size = user input number
  int sum = 0, n;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::vector<int> s1, s2;
  std::vector<int> subMatrix;
  std::string line;
  std::vector<std::vector<int>> matrix;
  std::vector<int> maxSum{0, 0, 0, 0};

  if (rank == 0) {
    // open file
    std::ifstream matrix_csv("matrix.csv");
    if (!matrix_csv.is_open())
      throw std::runtime_error("Could not open file");
    else {
      int i = 0, j;
      // puts matrix in csv into a 2d vector
      while (std::getline(matrix_csv, line)) {
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

    for (int i = 1; i < size; i++) {
      // sends 2 rows starting from the bottom
      s1 = matrix[i - 1];
      s2 = matrix[i];
      for (int j = 0; j < size - 1; j++) {
        // sends size of matrix
        MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        // sends 1 row
        MPI_Send(s1.data(), s1.size(), MPI_INT, i, 0, MPI_COMM_WORLD);
        // sends another row
        MPI_Send(s2.data(), s2.size(), MPI_INT, i, 0, MPI_COMM_WORLD);
      }
      // resizes size of t to fit 2x2 array
      subMatrix.resize(4);
      // receives 2x2 array from some process
      MPI_Recv(subMatrix.data(), 4, MPI_INT, i, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);

      // sum of receieved vector
      sum = subMatrix[0] + subMatrix[1] + subMatrix[2] + subMatrix[3];

      // saves the values of the max sum
      if (maxSum[0] + maxSum[1] + maxSum[2] + maxSum[3] < sum) {
        maxSum[0] = subMatrix[0];
        maxSum[1] = subMatrix[1];
        maxSum[2] = subMatrix[2];
        maxSum[3] = subMatrix[3];
      }

      // outputs individual sums
      std::cout << "2x2 submatrix from process " << i << " has sum: " << sum
                << std::endl;
    }
    std::cout << std::endl;
    std::vector<int> pos = getPos(matrix, maxSum); // 0 = row, 1 = col
    int msum = maxSum[0] + maxSum[1] + maxSum[2] + maxSum[3];
    std::cout << "Process: 0; max sum: " << msum << "; in pos: (" << pos[0]
              << ", " << pos[1] << ")." << std::endl;
  }

  if (rank != 0) {
    //  receieves size of matrix
    MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // resizes vector to fit the sent over data
    s1.resize(n);
    s2.resize(n);
    // recieves row 1
    MPI_Recv(s1.data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // receives row 2
    MPI_Recv(s2.data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // returns a matrix with the given offset
    subMatrix = getMaxSubMatrix(s1, s2);
    MPI_Send(subMatrix.data(), subMatrix.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}