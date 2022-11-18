# How to run
- ./run.sh
  - type this command in console
  - runs the default amount of times
- ./run.sh "#"
  - you can add a # after if you want to run it a specific amount of times.
  - e.g. ./run.sh 5
- if permission is denied to run the script, type this.
  - chmod +x run.sh

# Description
Identifying the submatrix of 2x2 with the largest sum of values:
Given a very large (n>10) matrix of n x n elements, write a distributed
program in MPI that outputs a submatrix of size 2x2 with the largest sum of
its elements and its relative position or displacement (row-column of the top
left element) in the original matrix. There will be only one process with
rank 0, that will read the file name with the input data, read from the file
the value of n, read from the file the entire matrix, and will output the
submatrix of size 2x2 with the largest sum of its elements and its position
on the screen. All the other processes will receive portions of the matrix
and contribute to identifying the submatrix.

# What it's doing
Imports a 2d vector from the generated csv file.  Creates a 1d vector sub matrix
of all 4 elements in the 2x2 sub matrix.  Adds all 4 elements to a sum, and 
has a maxSum that's the highest sum from all 2x2 sub matrices.