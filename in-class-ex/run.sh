#!/bin/bash
mpic++ $1.cc -o $1
if [ $# -ne 0 ]; then
  mpirun -n $2 $1
else
  mpirun $1
fi
rm $1