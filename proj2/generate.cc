#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

const int MAX_MATRIX = 5;

int main(){
  std::ofstream matrix;
  std::srand (std::time(NULL));
  int i = 0;
  matrix.open("matrix.csv");
  
  for(int i = 0; i < MAX_MATRIX; i++){
    int rNum = std::rand() % 9 + 0;
    for(int j = 1; j < MAX_MATRIX; j++){
      matrix << rNum << ",";
      rNum = std::rand() % 9 + 0;
    }
    matrix << rNum << std::endl;
  }
  matrix.close();
  return 0;
}