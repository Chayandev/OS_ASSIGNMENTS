#!/bin/bash

echo "Enter number : "
read x

reverseNum=0

while [ $x -ne 0 ]
do
   reverseNum=$(((reverseNum * 10) + (x % 10)))
   x=$((x / 10))
done

echo "Reversed Form is : $reverseNum"

