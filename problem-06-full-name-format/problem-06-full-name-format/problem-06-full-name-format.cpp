#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <cctype>

// Using directives for commonly used namespaces for brevity
using std::cout;
using std::cin;
using std::cerr;
using std::getline;
using std::string;
using std::streamsize;
using std::numeric_limits;

// Constants
constexpr size_t MAX_NAME_LENGTH = 100;
constexpr char SEPARATOR_CHAR = '-';
constexpr int SEPARATOR_LENGTH = 50;
constexpr char WHITESPACE[] = " \t\n\r";

/**
 * @enum NameOrder
 * @brief Enumerates the possible orderings of a person's name.
 */
enum class NameOrder
{
	Normal,		///< First name followed by last name
	Reversed 		///< Last name followed by first name
};

/**
 * @struct UserInfo
 * @brief Stores a user's first and last name.
 */
struct UserInfo
{
	string firstName;	///< The person's first name
	string lastName;	///< The person's last name
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
 * @brief Checks if a string contains only letters and spaces.
 *
 * @param name The string to check.
 * @return True if the string contains only letters and spaces, false otherwise.
 */
bool isValidName(const string& name)
{
	for (char c : name)
	{
		if (!isalpha(static_cast<unsigned char>(c)) && c != ' ' && c != '-' && c != '\'')
		{
			return false;
		}
	}

	return true;
}

/**
 * @brief Trims leading and trailing whitespace from a string.
 *
 * @param str The string to trim.
 * @return A new string with whitespace removed from both ends.
 */
string trim(const string& str)
{
	size_t start = str.find_first_not_of(WHITESPACE);

	if (start == string::npos)
	{
		return "";   // String is all whitespace
	}

	size_t end = str.find_last_not_of(WHITESPACE);

	return str.substr(start, end - start + 1);
}

/**
 * @brief Formats a given name by capitalizing the first letter of each word.
 *
 * @param name The name to format.
 * @return The formatted name.
 * @note This function takes a name as input and formats it by capitalizing the first letter of each word.
 * It handles names with spaces, hyphens, and apostrophes.
 */
string formatName(const string& name)
{
	string result;
	result.reserve(name.size());	// Performance optimization

	bool capitalizeNext = true;

	for (unsigned char c : name)	// Type safety 
	{
		if (isalpha(c))
		{
			if (capitalizeNext)
			{
				result += toupper(c);

				capitalizeNext = false;
			}
			else
			{
				result += tolower(c);
			}
		}

		else if (c == ' ' || c == '-' || c == '\'')
		{
			result += c;

			capitalizeNext = true;
		}

		// Invalid characters are skipped
	}

	return result;
}

/**
 * @brief Reads the user's name from the input with validation.
 *
 * @param prompt The message to display when asking for user input.
 * @return A non-empty, trimmed string containing the user's name.
 *
 * @note Uses getline to support names with spaces (e.g., "John Doe").
 * @note Prompts the user with a custom message and reads the entire line,
 * including spaces. Validates that the input is not empty and
 * handles input errors gracefully. Repeats until valid input is received.
 */
string readName(const string& prompt)
{
	string name;

	while (true)
	{
		cout << prompt;

		if (!getline(cin, name))
		{
			// Handle input stream errors (e.g., EOF, read failure)
			if (cin.eof())
			{
				cerr << "\nInput terminated. Exiting...\n";

				std::exit(EXIT_FAILURE);
			}

			cerr << "Error: Failed to read input. Please try again.\n";

			clearInputBuffer();

			continue;
		}

		name = trim(name);

		if (name.empty())
		{
			cerr << "Error: Name cannot be empty. Please try again.\n";

			continue;
		}

		if (name.size() > MAX_NAME_LENGTH)
		{
			cerr << "Error: Name is too long. Please enter a name with a maximum of " << MAX_NAME_LENGTH << " characters.\n";

			continue;
		}

		if (!isValidName(name))
		{
			cerr << "Error: Name contains invalid characters. Please use only letters, spaces, hyphens, and apostrophes.\n";

			continue;
		}

		return name;
	}
}

/**
 * @brief Reads a yes or no input from the user.
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

			cerr << "Invalid input! Please enter y or n\n\n";

			continue;
		}

		char lower = tolower(static_cast<unsigned char>(c));

		clearInputBuffer();		// Discard any trailing characters on the line.

		if (lower == 'y' || lower == 'n')
		{
			return lower == 'y';
		}
		else
		{
			cerr << "Invalid input! Please enter y or n\n\n";
		}
	}
}

/**
 * @brief Returns the NameOrder enum value based on the input boolean value.
 *
 * @param isReversed A boolean value indicating whether to return the reversed name order.
 * @return The NameOrder enum value corresponding to the input boolean value.
 */
NameOrder getNameOrder(bool isReversed)
{
	return (isReversed) ? NameOrder::Reversed : NameOrder::Normal;
}

/**
 * @brief Prompts the user to enter their first and last name and reads them from input.
 *
 * @return A struct with the user's first and last name.
 */
UserInfo readInfo()
{
	UserInfo info;

	info.firstName = formatName(readName("Enter your first name: "));

	info.lastName = formatName(readName("Enter your last name: "));

	return info;
}

/**
 * @brief Formats the full name based on the given Info struct and reversal flag.
 *
 * @param info A struct containing the first and last name.
 * @param nameOrder A NameOrder enum value to determine whether to reverse the order of the name.
 * @return A string containing the full name in the specified order.
 */
string getFullName(const UserInfo& info, NameOrder nameOrder)
{
	return (nameOrder == NameOrder::Reversed) ? info.lastName + " " + info.firstName : info.firstName + " " + info.lastName;
}

/**
 * @brief Prints the full name provided as a parameter.
 *
 * @param fullName The full name to be printed.
 */
void printFullName(const string& fullName)
{
	printSeparator('=');

	cout << "\nYour full name is: " << fullName << '\n';

	printSeparator('=');
}

int main()
{
	NameOrder nameOrder = getNameOrder(readYesNo("Do you want to display the name in reverse order? (y/n): "));

	printFullName(getFullName(readInfo(), nameOrder));

	return 0;
}