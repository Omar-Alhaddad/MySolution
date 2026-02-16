#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * @brief Prints a separator line with the specified character and count.
 *
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
	size_t start = str.find_first_not_of(" \t\n\r");

	if (start == string::npos)
	{
		return "";   // String is all whitespace
	}

	size_t end = str.find_last_not_of(" \t\n\r");

	return str.substr(start, end - start + 1);
}

/**
 * @brief Reads the user's name from the input with validation.
 *
 * Prompts the user with a custom message and reads the entire line,
 * including spaces. Validates that the input is not empty and
 * handles input errors gracefully. Repeats until valid input is received.
 *
 * @param prompt The message to display when asking for user input.
 * @return A non-empty, trimmed string containing the user's name.
 *
 * @note Uses getline to support names with spaces (e.g., "John Doe").
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

				return "";
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

		if (!isValidName(name))
		{
			cerr << "Error: Name contains invalid characters. Please use only letters, spaces, hyphens, and apostrophes.\n";

			continue;
		}

		return name;
	}
}

/**
 * @brief Prints the entered name with a formatted message.
 *
 * Displays the provided name with a descriptive label.
 *
 * @param name A constant reference to the name string to display.
 */
void printName(const string& name)
{
	printSeparator('=');
	cout << "Your name is: " << name << '\n';
	printSeparator('=');
}

int main()
{
	printName(readName("Enter your name: "));

	return 0;
}