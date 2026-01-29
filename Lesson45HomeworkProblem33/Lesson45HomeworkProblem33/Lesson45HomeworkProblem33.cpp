
#include <iostream>
#include <string>
#include <limits>

using namespace std;

constexpr int MIN_GRADE = 0;
constexpr int MAX_GRADE = 100;

// Grade ranges after division by 10
constexpr int RANGE_A = 9;  // 90-99
constexpr int RANGE_B = 8;  // 80-89
constexpr int RANGE_C = 7;  // 70-79
constexpr int RANGE_D = 6;  // 60-69
constexpr int RANGE_E = 5;  // 50-59 

void printSeparator(char fillChar = '-', int length = 50) {

	cout << string(length, fillChar) << '\n';
}

void clearInputBuffer() {

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int validateIntegerInRange(const string& prompt, int minValue, int maxValue) {

	int number;

	while (true)
	{
		cout << prompt;

		if (!(cin >> number))
		{
			clearInputBuffer();

			cout << "Invalid input! Please enter a valid number.\n\n";
		}
		else if (number < minValue || number > maxValue)
		{
			clearInputBuffer();

			cout << "Invalid input! Number must be between " << minValue << " and " << maxValue << "\n\n";
		}
		else
		{
			clearInputBuffer();
			return number;
		}
	}
}

char gradeToLetter(int grade) {

	if (grade < 0) return 'F';  // Handle negative

	grade /= 10;

	if (grade >= 10) return 'A';   // Handles 100+ grades

	switch (grade) {

	case RANGE_A:
		return 'A';
	case RANGE_B:
		return 'B';
	case RANGE_C:
		return 'C';
	case RANGE_D:
		return 'D';
	case RANGE_E:
		return 'E';
	default:
		return 'F';
	}
}

int main()
{
	// Program to convert numeric grades to letter grades
	int grade = validateIntegerInRange("Enter your grade (0-100): ", MIN_GRADE, MAX_GRADE);

	printSeparator();

	cout << "Your letter grade is: " << gradeToLetter(grade) << '\n';

	return 0;
}