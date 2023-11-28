#!bin/bash

echo "Enter a Year : "
read year

if [ $((year%4)) -eq 0 ]; then
   if [ $((year%100)) -eq 0 ]; then
      if [ $((year%400)) -eq 0 ]; then
         echo "Year $year is Leap Year."
      else
         echo "Year $year isn't leap Year."
      fi
    else
       echo "Year $year is Leap Year."
    fi
else
    echo "Year $year isn't Leap Year."
fi
