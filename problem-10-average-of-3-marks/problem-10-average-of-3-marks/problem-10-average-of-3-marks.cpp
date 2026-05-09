#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <array>

// Using directives for commonly used namespaces for brevity
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::streamsize;
using std::numeric_limits;
using std::array;
using std::to_string;
using std::fixed;
using std::setprecision;

// Constants
constexpr char SEPARATOR_CHAR = '-';
constexpr size_t SEPARATOR_LENGTH = 50;
constexpr int MIN_MARK = 0;
constexpr int MAX_MARK = 100;
constexpr int NUM_MARKS = 3;

/**
 * @brief Prints a separator line with the specified character and count.
 *
 * @param fillChar The character to fill the line with. Default is '-'.
 * @param count The number of characters in the line. Default is 50.
 */
void printSeparator(char fillChar = SEPARATOR_CHAR, size_t count = SEPARATOR_LENGTH)
{
	cout << string(count, fillChar) << '\n';
}

/**
 * @brief Clears the input buffer to handle invalid input.
 */
void clearInputBuffer()
{
	cin.clear();	// reset any error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	// discard remaining input
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
 * @return int The validated integer.
 */
int readNumberInRange(const string& prompt, int minVal, int maxVal) {

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
 * @brief Reads and validates N marks from the user.
 *
 * @tparam N The number of marks to read.
 * @return array<int, N> An array of N marks read from the user.
 */
template<size_t N>
array<int, N> readMarks()
{
	array<int, N> marks;

	for (size_t i = 0; i < marks.size(); i++)
	{
		marks[i] = readNumberInRange("Enter mark " + to_string(i + 1) + ": ", MIN_MARK, MAX_MARK);
	}

	return marks;
}

/**
 * @brief A template function that calculates the sum of numbers.
 *
 * @tparam Args The types of the arguments passed to the function.
 * @param args The numbers to be added together.
 * @return The sum of all the numbers passed as arguments.
 */
template<typename... Args>
auto sumOfNumbers(Args... args)
{
	// Compile-time check: ensure at least one argument
	static_assert(sizeof...(args) > 0, "sumOfNumbers requires at least one argument");

	// Compile-time check: ensure all arguments are arithmetic types
	static_assert((std::is_arithmetic_v<Args> && ...), "All arguments must be arithmetic types (int, float, double, etc.)");

	// Compile-time check: ensure all arguments are not bool
	static_assert((!std::is_same_v<Args, bool> && ...), "bool is not a valid numeric argument for sumOfNumbers");

	// Compile-time check: ensure all arguments are either signed or unsigned
	static_assert((std::is_signed_v<Args> && ...) || (std::is_unsigned_v<Args> && ...), "Mixing signed and unsigned types is not allowed");

	// Promote integral types to long long to reduce overflow risk.
	// Note: mixing int and float yields float, which may lose precision.
	using CommonType = std::common_type_t<Args...>;
	using ResultType = std::conditional_t<std::is_integral_v<CommonType>, long long, CommonType>;

	return (static_cast<ResultType>(args) + ...);
}

/**
 * @brief A template function that calculates the average of numbers.
 *
 * @tparam Args The types of the arguments passed to the function.
 * @param args The numbers to be averaged.
 * @return The average of all the numbers passed as arguments.
 */
template<typename... Args>
float calculateAverage(Args... args)
{
	// Compile-time check: ensure at least one argument
	static_assert(sizeof...(args) > 0, "calculateAverage requires at least one argument");

	return sumOfNumbers(args...) / static_cast<float>(sizeof...(args));
}

/**
 * @brief Prints the average of three marks.
 *
 * @param average The average of the marks.
 */
void printResult(const float average)
{
	printSeparator('*');
	cout << "The average of marks is: " << fixed << setprecision(2) << average << '\n';
	printSeparator('*');
}

int main()
{
	auto marks = readMarks<NUM_MARKS>();

	// Creates a lambda function that accepts any number of arguments and calls the calculateAverage function.
	auto averageArgs = [](auto... args) {return calculateAverage(args...); };

	auto result = std::apply(averageArgs, marks);

	printResult(result);

	return 0;
}