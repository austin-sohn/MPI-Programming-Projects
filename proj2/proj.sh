#!/bin/bash
mpic++ -std=c++11 proj.cc
if [ $# -ne 0 ] && [ -f "a.out" ]; then
  mpirun -n $1 a.out
  rm a.out
elif [ $# -ge 0 ] && [ -f "a.out" ]; then
  mpirun -n 2 a.out 
  rm a.out
else
  echo "error"
fi
