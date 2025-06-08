
echo "Simple Calculator"
echo Choose any Operation:
echo 1. Addition:
echo 2. Subtraction:
echo 3. Multiplication
echo 4. Division
echo 5. Modulus
echo 6. Increment [On First Number]
echo 7. Decrement [On First Number]

echo Enter Your Choice [1-7]:
read choice

if [[ $choice -lt 6 ]]; then
	echo Enter First Number:
	read num1

	echo Enter Second Number: 
	read num2

else
	echo Enter a Number:
	read num1

fi

case $choice in
	1) echo "Result:  $((num1 + num2))";;
	2) echo "Result:  $((num1 - num2))";;
	3) echo "Result:  $((num1 * num2))";;
        4) echo "Result:  $((num1 / num2))";;
      	5) echo "Result:  $((num1 % num2))";;
        6) echo "Result:  $((num1 + 1))";;
        7) echo "Result:  $((num1 - 1))";;
        *) echo "Invalid Choice! Enter number [1-7]:";;

esac



