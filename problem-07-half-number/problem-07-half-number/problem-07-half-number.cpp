#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

// Using directives for commonly used namespaces for brevity
using std::cout;
using std::cin;
using std::cerr;
using std::fixed;
using std::setprecision;
using std::string;
using std::streamsize;
using std::numeric_limits;

// Constants
constexpr char SEPARATOR_CHAR = '-';
constexpr int SEPARATOR_LENGTH = 50;

/**
 * @brief Prints a separator line with the specified character and count.
 *
 * @param fillChar The character to fill the line with. Default is '-'.
 * @param count The number of characters in the line. Default is 50.
 */
void printSeparator(char fillChar = SEPARATOR_CHAR, int count = SEPARATOR_LENGTH)
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
 * @brief Prints an error message to the console.
 *
 * @param message The error message to print.
 */
void printError(const string& message)
{
	printSeparator();
	cerr << "Error: " << message << '\n';
	printSeparator();
}

/**
 * @brief Prompts the user for an integer input and handles invalid input.
 *
 * @param prompt The prompt to display to the user.
 * @return The user's input as an integer.
 */
int readNumber(const string& prompt) {

	int number;

	while (true)
	{
		cout << prompt;

		if (!(cin >> number))
		{
			clearInputBuffer();		// Clear the input buffer to handle invalid input

			printError("Invalid input! Please enter a valid number.");
		}
		else
		{
			clearInputBuffer();		// Discard any trailing characters on the line.

			return number;
		}
	}
}

/**
 * @brief Reads a yes or no input from the user.
 *
 * @param prompt The message to display to the user.
 * @return True if the input is 'y' or 'Y', false if the input is 'n' or 'N'.
 * @note Input is case-insensitive. Prompts repeatedly until valid input.
 */
bool readYesNo(const string& prompt)
{
	char c;

	while (true)
	{
		cout << prompt;

		if (!(cin >> c))
		{
			clearInputBuffer();		// Discard any trailing characters on the line.

			printError("Invalid input! Please enter 'y' or 'n'");

			continue;
		}

		// Prevents undefined behavior with negative char values
		char lower = tolower(static_cast<unsigned char>(c));

		clearInputBuffer();		// Discard any trailing characters on the line.

		if (lower == 'y' || lower == 'n')
		{
			return lower == 'y';
		}
		else
		{
			printError("Invalid input! Please enter 'y' or 'n'");
		}
	}
}

/**
 * @brief Calculates the half of a given number.
 *
 * @param number The number to calculate the half of.
 * @return double The half of the given number.
 */
double calculateHalfNumber(int number)
{
	return static_cast<double>(number) / 2;
}

/**
 * @brief Prints the half of a given number to the console.
 *
 * @param number The number to calculate the half of.
 */
void printResult(int number)
{
	printSeparator('*');
	cout << "Half of " << number << " is " << fixed << setprecision(1) << calculateHalfNumber(number) << '\n';
	printSeparator('*');
}

int main()
{
	do
	{
		printResult(readNumber("Enter a number: "));

	} while (readYesNo("Calculate another? (y/n): "));

	return 0;
}