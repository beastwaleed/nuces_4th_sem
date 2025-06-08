
echo "Enter Your Password:"
read  password

if [[ ${#password} -lt 8 ]]; then
	echo "The password is weak. It must have atleast 8 characters"
	exit 1
fi


if ! [[ "$password" =~ [A-Z] ]]; then
	echo "The password is weak. It must contain atleast one uppercase letter"
	exit 1

fi


if ! [[ "$password" =~ [a-z] ]]; then
	echo "The password is weak. It must contain atleast one lowercase letter"
        exit 1
fi


if ! [[ "$password" =~ [0-9] ]]; then
        echo "The password is weak. It must contain atleast one digit"
        exit 1
fi


if ! [[ "$password" =~ [\@\#\$\%\^\&\*\(\)\_\+\~\?\>\<] ]]; then
	echo "The password is weak. It must contain atleast one special character"
	exit 1
fi

echo "Your Password is Strong"

