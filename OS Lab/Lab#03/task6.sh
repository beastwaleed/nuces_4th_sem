
echo "Enter Your Age: "
read age

if [[ "$age" =~ ^[0-9]+$ ]]; then
	if [ "$age" -ge 18 ]; then
		echo "You are eligible to vote"
	else
		echo "You are not eligible to vote:"
	fi

else
	echo "Invalid Input! Please enter numeric value"

fi



