echo "Enter a Number"
read n
i=`expr $n - 1`
p=1
while (( $i >= 1 ))
do
    n=`expr $n \* $i`
    i=$(( $i - 1 ))
done
echo "The Factorial of the given Number is $n"