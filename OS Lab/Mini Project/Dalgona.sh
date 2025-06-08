#!/bin/bash

# ASCII Art Shapes
circle="
  *****
 *     *
*       *
 *     *
  *****
"

star="
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
"

umbrella="
  *****
 *******
  *****
    |
    |
"

triangle="
    *
   ***
  *****
 *******
*********
"

shapes=("circle" "star" "umbrella" "triangle")
ascii_shapes=("$circle" "$star" "$umbrella" "$triangle")

# Game Variables
attempts=3
player_score=0
computer_score=0
difficulty=10  # Default difficulty (Medium)

# Functions
choose_shape() {
	random_index=$((RANDOM % 4))
  	return $random_index
}

display_shape() {
  	local shape_index="$1"
  	echo "${ascii_shapes[$shape_index]}"
}

play_round() {
	choose_shape
	local random_index=$?
	local correct_shape=${shapes[$random_index]}

	echo "Here is your challenge shape:"
	display_shape $random_index

	read -p "Enter the shape name: " -t "$difficulty" player_guess

	#player fail
	if [[ -z "$player_guess" ]]; then
		echo -e "\n\nTime's up! You failed to enter the shape name in time."
    		((attempts--))
    		echo "-> Only $attempts attempt(s) left."
    		echo "-> The correct answer was: $correct_shape"
	#player wins
  	elif [[ "$player_guess" == "$correct_shape" ]]; then
    		echo "-> Well done! You have successfully identified the shape!"
    		echo "-> You earn 10 points."
    		player_score=$((player_score + 10))
  	else	#wrong answer
    		((attempts--))
    		echo "-> Wrong guess! $attempts attempt(s) left."
      	echo "-> The correct answer was: $correct_shape"
  	fi
}

vs_computer() {
  	choose_shape
	local random_index=$?
  	local correct_shape=${shapes[$random_index]}

  	echo "Here is your challenge shape:"
  	display_shape $random_index

  	read -p "Enter the shape name: " -t "$difficulty" player_guess

	#player fails
  	if [[ -z "$player_guess" ]]; then
    		echo -e "\n\nTime's up! You failed to enter the shape name in time."
    		((attempts--))
    		echo "-> Only $attempts attempt(s) left."
    		echo "The correct answer was: $correct_shape"
	#player wins
	elif [[ "$player_guess" == "$correct_shape" ]]; then
		echo "-> Well done! You have successfully identified the shape!"
		echo "-> You earn 10 points."
		player_score=$((player_score + 10))
	else	#player fails
		((attempts--))
		echo "-> Wrong guess! $attempts attempt(s) left."
		echo "-> You failed to guess correctly."
	fi

	#computer guess
	choose_shape
	local computer_index=$?
  	local computer_guess=${shapes[$computer_index]}

	echo -e "\nComputer Guess: $computer_guess"

	#computer wins
	if [[ "$computer_guess" == "$correct_shape" ]]; then
		echo "-> Computer guessed correctly!"
		echo "-> Computer earns 10 points."
		computer_score=$((computer_score + 10))
	#player wins
	elif [[ "$computer_guess" != "$correct_shape" ]]; then
		echo "-> Computer failed to guess correctly."
	else	#draw
		echo "-> Both failed! The correct answer was: $correct_shape"
	fi
}

main_menu() {
	while true; do
		clear
		echo -e "\t\tWelcome to the Dalgona Challenge!"
		echo -e "--Can you correctly identify the shape before time runs out?\n"
		echo "--Game Modes--"
		echo "1. Single Player Mode"
		echo "2. VS Computer Mode"
		read -p "Choose a mode (1-3): " mode
		
		if [[ $mode == 1 || $mode == 2 || $mode == 3 ]]; then
			break
		else
			echo -e "\n-----Invalid Input! Try again-----"
			sleep 1
		fi
	done
	
	return $mode
}

select_difficulty() {
	while true; do
		clear
		echo "--Game Difficulty Levels--"
		echo "1. Easy (15 sec)"
		echo "2. Medium (10 sec)"
		echo "3. Hard (5 sec)"
		read -p "Choose a level (1-3): " difficulty_choice
		
		case $difficulty_choice in
			1)
				difficulty=15 
				break
				;;
			2)
				difficulty=10 
				break
				;;
			3)
				difficulty=5
				break
				;;
			*)
				echo -e "\n-----Invalid Input! Try again-----"
				sleep 1 
				;;
		esac
	done
}

single_player() {
	round=1
	
	while [[ $attempts -gt 0 ]]; do
		echo -e "\n\t\t-----Round $round begins!-----"
		echo -e "\nYou have $attempts attempts."
	  	echo "Generating a random shape..."
		play_round
		sleep 3
		((round++))
	done
	echo -e "\n-----You earned $player_score points-----\n"
	
	return 0
}

play_vs_computer() {
	round=1
	
	while [[ $attempts -gt 0 ]]; do
		echo -e "\n\t\t-----Round $round begins!-----"
		echo -e "\nPlayer have $attempts attempts."
	  	echo "Generating a random shape..."
		vs_computer
		sleep 3
		((round++))
	done
	echo -e "\n-----Computer earned $computer_score points-----"
	echo "-----You earned $player_score points-----"
	
	if [[ $player_score -gt $computer_score ]]; then
		echo -e "\n-----Player won the game!-----\n"
	elif [[ $computer_score -gt $player_score ]]; then
		echo -e "\n-----Computer won the game!-----\n"
	else
		echo -e "\n-----Game Draw!-----\n"
	fi
	
	return 0
}

main() {
	#call main menu
	main_menu
  	mode=$?
  	
  	#call difficulty menu
  	select_difficulty
  	
  	case $mode in
		1) 
        		single_player ;;
		2) 
        		play_vs_computer ;;
        *) 
        		echo "Invalid Option! Please try again."
			main_menu ;;
    	esac
  
	return 0
}

# Main Game Loop
while true; do
	attempts=3
	player_score=0
	computer_score=0

  	#call main function
  	main

  	read -p "Play again? (y/n): " play_again
  	if [[ "$play_again" != "y" ]]; then
    		break
  	fi
done

echo -e "\n-----Thank you for playing!-----\n"

exit 0
