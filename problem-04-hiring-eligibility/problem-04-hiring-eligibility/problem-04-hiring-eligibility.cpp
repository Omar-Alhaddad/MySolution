#include <iostream>
#include <string>
#include <limits>

using namespace std;

constexpr int MIN_AGE = 1;
constexpr int MAX_AGE = 150;
constexpr int MIN_HIRING_AGE = 22;

/**
 * @struct ApplicantInfo
 * @brief Represents the information of a job applicant.
 */
struct ApplicantInfo
{
	int age;	///< The age of the applicant
	bool hasDriverLicense;	///< Whether the applicant has a driver's license
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
 * @brief Validates and returns a positive integer within specified range.
 * @param prompt The message to display to the user.
 * @param minValue The minimum acceptable value.
 * @param maxValue The maximum acceptable value.
 * @return The validated integer.
 */
int validatePositiveInteger(const string& prompt, int minValue, int maxValue)
{
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
			clearInputBuffer();		// Discard any trailing characters on the line.

			cout << "Invalid input! Number must be between " << minValue << " and " << maxValue << " (inclusive).\n\n";
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
 * @param prompt The message to display to the user.
 * @return True if the input is 'y', false if the input is 'n'.
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

			cout << "Invalid input! Please enter y or n\n\n";

			continue;
		}

		char lower = tolower(c);

		if (lower == 'y' || lower == 'n')
		{
			clearInputBuffer();		// Discard any trailing characters on the line.

			return lower == 'y';
		}
		else
		{
			clearInputBuffer();		// Discard any trailing characters on the line.

			cout << "Invalid input! Please enter y or n\n\n";
		}
	}
}

/**
 * @brief Reads applicant information from the user.
 * @return The applicant information.
 */
ApplicantInfo readInfo()
{
	ApplicantInfo info;

	info.age = validatePositiveInteger("Enter your age: ", MIN_AGE, MAX_AGE);

	printSeparator();

	info.hasDriverLicense = readYesNo("Do you have driver license (y/n): ");

	return info;
}

/**
 * @brief Checks if the applicant is accepted for hiring.
 * @param info The applicant information.
 * @return True if the applicant is accepted, false otherwise.
 */
bool isAccepted(const ApplicantInfo& info)
{
	return (info.age >= MIN_HIRING_AGE && info.hasDriverLicense);
}

/**
 * @brief Prints the hiring result.
 * @param info The applicant information.
 */
void printResult(const ApplicantInfo& info)
{
	if (isAccepted(info))
	{
		cout << "\nCongratulations, You are Hired.\n";
	}
	else
	{
		cout << "\nSorry, you are Rejected.\n";

		if (info.age < MIN_HIRING_AGE)
		{
			cout << "Reason: Age must be at least " << MIN_HIRING_AGE << ".\n";
		}
		if (!info.hasDriverLicense)
		{
			cout << "Reason: Driver license required.\n";
		}
	}
}

int main()
{
	printResult(readInfo());

	return 0;
}