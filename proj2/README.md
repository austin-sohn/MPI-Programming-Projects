# Project 2
- Austin Sohn
  - austinsohn@csu.fullerton.edu

# How to run
- ./generate.sh
  - This command generates a n x n matrix csv file filled with random numbers from the range given by the user.
- ./proj2.sh or ./proj2.sh "#"
  - Type this command in console to run the project.
  - Without #, it runs default amount of time
  - With #, it runs a # amount of times.
  - e.g. ./proj2.sh 11
- if permission is denied when running the script.
  - chmod +x proj2.sh
  - chmod +x generate.sh

# Description
Identifying the submatrix of 2x2 with the largest sum of values: Given a very large (n>10) matrix of n x n elements, write a distributed program in MPI that outputs a submatrix of size 2x2 with the largest sum of its elements and its relative position or displacement (row-column of the top left element) in the original matrix. There will be only one process with rank 0, that will read the file name with the input data, read from the file the value of n, read from the file the entire matrix, and will output the submatrix of size 2x2 with the largest sum of its elements and its position on the screen. All the other processes will receive portions of the matrix and contribute to identifying the submatrix.
