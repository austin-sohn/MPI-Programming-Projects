#!/bin/bash
mpic++ proj2.cc -std=c++11 
if [ $# -ne 0 ] && [ -f "a.out" ]; then
  mpirun -n $1 a.out
  rm a.out
elif [ $# -ge 0 ] && [ -f "a.out" ]; then
  mpirun -n 11 a.out 
  rm a.out
else
  echo "error"
fi