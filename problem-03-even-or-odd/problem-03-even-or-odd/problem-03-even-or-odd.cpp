#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * @enum NumberType
 * @brief Enum to represent if a number is even or odd.
 */
enum class NumberType {
	Odd = 1,  ///< The number is odd
	Even = 2  ///< The number is even
};

/**
 * @brief Prints a separator line with the specified character and count.
 * @param fillChar The character to fill the line with. Default is '-'.
 * @param count The number of characters in the line. Default is 50.
 */
void printSeparator(char fillChar = '-', int count = 50)
{
	cout << string(count, fillChar) << '\n';
}

/**
 * @brief Clears the input buffer to handle invalid input.
 */
void clearInputBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * @brief Prompts the user for an integer input and handles invalid input.
 * @param prompt The prompt to display to the user.
 * @return The user's input as an integer.
 */
int readNumber(const string& prompt = "Enter a number: ") {

	int number;

	while (true)
	{
		cout << prompt;

		if (!(cin >> number))
		{
			clearInputBuffer();		// Clear the input buffer to handle invalid input

			cout << "Invalid input! Please enter a valid number.\n\n";
		}
		else
		{
			clearInputBuffer();		// Discard any trailing characters on the line.

			return number;
		}
	}
}

/**
 * @brief Checks if a number is even or odd.
 * @param number The number to check.
 * @return NumberType The type of the number (even or odd).
 */
NumberType checkNumberType(int number)
{
	return (number % 2 != 0) ? NumberType::Odd : NumberType::Even;
}

/**
 * @brief Gets the string representation of a number type (even or odd).
 * @param numberType The type of the number (even or odd).
 * @return The string representation of the number type.
 */
string getNumberType(NumberType numberType)
{
	return (numberType == NumberType::Even ? "Even" : "Odd");
}

/**
 * @brief Prints whether a number is even or odd.
 * @param numberType The type of the number (even or odd).
 */
void printFormattedNumberType(NumberType numberType)
{
	printSeparator('=');
	cout << "Number is " << getNumberType(numberType) << '\n';
	printSeparator('=');
}

int main()
{
	printFormattedNumberType(checkNumberType(readNumber("Enter number: ")));

	return 0;
}