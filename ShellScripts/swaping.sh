#!/bin/bash

echo "Enter num1: "
read x

echo "Enter num2: "
read y

x=$((x+y))
y=$((x-y))
x=$((x-y))

echo "After Swaping num1=$x and num2=$y"

