#!/bin/bash

echo "Enter Number : "
read x

if [ $((x%2)) -eq 0 ];then
    echo "$x is even number."
else 
    echo "$x is Odd Number."
fi
