#include <iostream>
#include <string>
#include <limits>

// Using directives for commonly used namespaces for brevity
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::streamsize;
using std::numeric_limits;

// Constants
constexpr int MIN_MARK = 0;
constexpr int MAX_MARK = 100;
constexpr int PASSING_MARK = 50;
constexpr char SEPARATOR_CHAR = '-';
constexpr int SEPARATOR_LENGTH = 50;

/**
 * @enum FinalResult
 * @brief Enumerates the possible outcomes of a test.
 */
enum class FinalResult
{
	Pass,	//< The test has been passed
	Fail 	//< The test has been failed
};

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
 * @brief Prints a range error message to the console.
 *
 * @param minVal The minimum acceptable value.
 * @param maxVal The maximum acceptable value.
 */
void printRangeError(int minVal, int maxVal)
{
	printSeparator();
	cerr << "Error: " << "Number must be between " << minVal << " and " << maxVal << " (inclusive)." << '\n';
	printSeparator();
}

/**
 * @brief Validates and returns an integer within specified range.
 *
 * @param prompt The message to display to the user.
 * @param minVal The minimum acceptable value.
 * @param maxVal The maximum acceptable value.
 * @return The validated integer.
 */
int readNumber(const string& prompt, int minVal, int maxVal) {

	int number;

	while (true)
	{
		cout << prompt;

		bool isValidInput = (cin >> number).good();

		// Discard any trailing characters on the line or handle invalid input
		clearInputBuffer();

		if (!isValidInput)
		{
			printError("Invalid input! Please enter a valid number.");
		}
		else if (number < minVal || number > maxVal)
		{
			printRangeError(minVal, maxVal);
		}
		else
		{
			return number;
		}
	}
}

/**
 * @brief Checks the mark of a test.
 *
 * @param mark The mark of the test.
 * @return FinalResult The result of the test.
 */
FinalResult checkMark(int mark)
{
	return (mark >= PASSING_MARK) ? FinalResult::Pass : FinalResult::Fail;
}

/**
 * @brief Returns the string representation of the final result.
 *
 * @param result The final result to be converted to a string.
 * @return The string representation of the final result.
 */
string getFinalResult(FinalResult result)
{
	return (result == FinalResult::Pass) ? "Pass" : "Fail";
}

/**
 * @brief Prints the result of a test.
 *
 * @param mark The mark of the test.
 */
void printResult(int mark)
{
	printSeparator('*');
	cout << "You " << getFinalResult(checkMark(mark)) << '\n';
	printSeparator('*');
}

int main()
{
	printResult(readNumber("Enter your mark: ", MIN_MARK, MAX_MARK));

	return 0;
}