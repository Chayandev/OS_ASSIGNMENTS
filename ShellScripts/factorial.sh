#!/bin/bash

echo "Enter one number :"
read x
if [ $x -lt 0 ]; then 
   echo "Factorial is not defined  for negative numbers"
else
   factorial=1 
   y=$x
   while [ $y -ne 0 ]
   do  
       factorial=$((factorial * y))
       ((y--))
   done
   echo "Factorial of $x is : $factorial"
fi   

