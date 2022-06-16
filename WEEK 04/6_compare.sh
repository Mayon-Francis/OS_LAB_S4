#! bin/bash

read -p "Enter num1: " num1
read -p "Enter num2: " num2

if [ $num1 -eq $num2 ]
    then
    echo "They are equal"
elif [ $num1 -gt $num2 ]
    then
    echo "$num1 > $num2"
elif [ $num1 -lt $num2 ]
    then
    echo "$num1 < $num2"
fi