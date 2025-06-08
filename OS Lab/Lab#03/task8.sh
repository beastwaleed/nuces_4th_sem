
echo "Temperatuer Converter"
echo "1. Celsius to Farenheit"
echo "2. Fahrenheit to Celsius"
echo "Enter Your Choice [1-2]: "
read choice

if [ "$choice" = 1 ]; then
	echo "Enter Temperature in Celsius:"
       	read celsius
	farenheit=$(( (celsius * 9/5) + 32 ))
 	echo "$celsius °C is $farenheit °F"

elif [ "$choice" = 2 ]; then
	echo "Enter Temperature in Farenheit:"
        read farenheit	
	celsius=$(( (farenheit - 32) * 5/9))
	echo "$farenheit °F is $celsius°C"

else
	echo "Invalid Choice! Please Enter 1 or 2"
fi
