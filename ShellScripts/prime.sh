#!/bin/bash

echo "Enter number : "
read x

if [ $x -lt 2 ]; then
  echo "Number $x is not prime."
else
   flag=1
   limit=$(echo "sqrt($x)" | bc)
   for ((i=2; i<=limit; i++)); do
      if [ $((x%i)) -eq 0 ]; then
         flag=0
         break
      fi
   done

   if [ $flag -eq 1 ]; then
      echo "Number $x is prime."
   else
      echo "Number $x is not prime."
   fi
fi

