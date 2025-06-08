
echo "Grading Calculator" 
echo "Enter the Student's score (0-100):"
read score

# Corrected the condition
if [[ "$score" =~ ^[0-9]+$ ]] && [ "$score" -ge 0 ] && [ "$score" -le 100 ]; then
    if [ "$score" -ge 90 ]; then
        echo "Grade: A - Excellent"
    elif [ "$score" -ge 80 ]; then
        echo "Grade: B - Good Job"
    elif [ "$score" -ge 70 ]; then
        echo "Grade: C - You Passed"
    elif [ "$score" -ge 60 ]; then
        echo "Grade: D - Needs Improvement"
    else
        echo "Grade: F - Failed, try harder next time"
    fi
else
    echo "Invalid input! Please enter a valid number between 0 and 100."
fi

