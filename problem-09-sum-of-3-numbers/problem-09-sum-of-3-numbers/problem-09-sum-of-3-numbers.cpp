#include <iostream>
#include <string>
#include <limits>
#include <array>
#include <type_traits>

// Using directives for commonly used namespaces for brevity
using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::to_string;
using std::streamsize;
using std::numeric_limits;
using std::apply;
using std::array;

// Constants
constexpr char SEPARATOR_CHAR = '-';
constexpr int SEPARATOR_LENGTH = 50;
constexpr int ARRAY_SIZE = 3;	// Number of elements in the array

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
 * @brief Validates and returns an integer within specified range.
 *
 * @param prompt The message to display to the user.
 * @return The validated integer.
 */
long long readNumber(const string& prompt)
{
	long long number;

	while (true)
	{
		cout << prompt;

		// Input piped from a file: "42" (no trailing newline, hits EOF).
		// false! eofbit set, even though 42 was read correctly.
		// Using fail() instead of good() handles EOF edge case better:
		// - good() requires ALL flags clear (including eofbit)
		// - fail() only checks failbit/badbit (ignores eofbit)
		// This allows piped input like "42" without trailing newline to work
		bool isValidInput = (cin >> number).good();	// requires ALL flags clear: failbit, badbit, AND eofbit.

		// Discard any trailing characters on the line or handle invalid input
		clearInputBuffer();

		if (!isValidInput)
		{
			printError("Invalid input! Please enter a valid number.");
		}
		else
		{
			return number;
		}
	}
}

/**
 * @brief Reads N numbers from the user and stores them in an array.
 *
 * @tparam N The number of integers to read (compile-time constant).
 * @return array<long long, N> An array containing the validated user input.
 *
 * @note Uses long long to support the full 64-bit integer range.
 * @example auto nums = readNumbers<3>(); // Reads 3 long long integers
 */
template<size_t N>
array<long long, N> readNumbers()
{
	array<long long, N> numbers;

	for (size_t i = 0; i < N; i++)
	{
		numbers[i] = readNumber("Enter number " + to_string(i + 1) + ": ");
	}

	return numbers;
}

/**
 * @brief A template function that calculates the sum of numbers.
 *
 * @tparam Args The types of the arguments passed to the function.
 * @param args The numbers to be added together.
 * @return The sum of all the numbers passed as arguments.
 */
template <typename... Args>
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
 * @brief Prints the sum of three numbers.
 *
 * @param sum The sum of the three numbers.
 */
void printResult(auto sum)
{
	printSeparator('*');
	cout << "The total sum of numbers is: " << sum << '\n';
	printSeparator('*');
}

int main()
{
	auto numbers = readNumbers<ARRAY_SIZE>();

	// Creates a lambda function that accepts any number of arguments and calls the sumOfNumbers function.
	auto sumArgs = [](auto... args) {return sumOfNumbers(args...); };

	auto result = apply(sumArgs, numbers);

	printResult(result);

	return 0;
}