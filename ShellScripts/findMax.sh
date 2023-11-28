#!/bin/bash

echo "Enter num1 :"
read x

echo "Enter num2 :"
read y

echo "Enter num3 :"
read z

if [ $x -gt $y ] && [ $x -gt $z ]; then
    echo "$x is maximum"
elif [ $y -gt $x ] && [ $y -gt $z ]; then
     echo "$y is maximum"
else
    echo "$z is maximum"
fi
