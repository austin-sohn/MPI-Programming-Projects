#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

int main() {
  std::ofstream matrix;
  std::srand(std::time(NULL));
  int i = 0;
  matrix.open("matrix.csv");
  int matrixSize = 11;
  int lowNum, highNum;
  std::cout << "Input matrix size (n>10): ";
  std::cin >> matrixSize;
  std::cout << "Lowest number: ";
  std::cin >> lowNum;
  std::cout << "Highest number: ";
  std::cin >> highNum;
  highNum++;

  for (int i = 0; i < matrixSize; i++) {
    int rNum = std::rand() % highNum + lowNum;
    for (int j = 1; j < matrixSize; j++) {
      matrix << rNum << ",";
      rNum = std::rand() % highNum + lowNum;
    }
    matrix << rNum << std::endl;

    // int count = 0;
    // for (int i = 0; i < matrixSize; i++) {
    //   for (int j = 1; j < matrixSize; j++) {
    //     matrix << count << ",";
    //     count++;
    //   }
    //   matrix << count << std::endl;
    //   // count++;
  }
  matrix.close();
  return 0;
}