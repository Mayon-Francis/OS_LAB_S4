#!/bin/bash

# For Loops

echo "Simple for loop"
for elem in a b c
do  
    echo $elem
done

echo " " 
echo "Range Based for loop"

for i in {1..5}
do
    echo $i
done

echo " " 
echo "Range Based for loop in steps of 2"
for n in {1..5..2}; 
do
    echo $n
done