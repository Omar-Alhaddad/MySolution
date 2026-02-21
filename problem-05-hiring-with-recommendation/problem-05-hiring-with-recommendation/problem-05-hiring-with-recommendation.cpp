#include <iostream>
#include <string>
#include <limits>

// Using directives for commonly used namespaces for brevity
using std::cout;
using std::cin;
using std::string;
using std::streamsize;
using std::numeric_limits;

constexpr int MIN_AGE = 1;
constexpr int MAX_AGE = 150;
constexpr int MIN_HIRING_AGE = 22;

/**
 * @enum ApplicationStatus
 * @brief Represents the status of an application.
 * @details This enumeration is used to indicate whether an application has been hired or rejected.
 */
enum class ApplicationStatus
{
	HIRED,	///< The application has been hired.
	REJECTED	///< The application has been rejected.
};

/**
 * @struct ApplicantInfo
 * @brief Stores candidate information including age, driving license status, and recommendation status.
 */
struct ApplicantInfo
{
	int age;	///< The age of the applicant
	bool hasDriverLicense;	///< Whether the applicant has a driver's license
	bool hasRecommendation;	///< Whether the applicant has a recommendation//
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
 * @brief Prompts the user to enter their age, driving license status, and recommendation status.
 * @return A struct containing applicant information.
 */
ApplicantInfo readInfo()
{
	ApplicantInfo info;

	info.age = validatePositiveInteger("Enter your age: ", MIN_AGE, MAX_AGE);

	info.hasDriverLicense = readYesNo("Do you have driver's license (y/n): ");

	info.hasRecommendation = readYesNo("Do you have recommendation (y/n): ");

	return info;
}

/**
 * @brief Determines if the candidate is accepted based on age, license, and recommendation status.
 * @param info A struct containing the applicant's information.
 * @return True if the applicant is accepted, false otherwise.
 */
ApplicationStatus isAccepted(const ApplicantInfo& info)
{
	if (info.hasRecommendation)
	{
		return ApplicationStatus::HIRED;
	}
	else if (info.age >= MIN_HIRING_AGE && info.hasDriverLicense)
	{
		return ApplicationStatus::HIRED;
	}

	return ApplicationStatus::REJECTED;
}

/**
 * @brief Prints whether the candidate is hired or rejected based on eligibility.
 * @param info A struct containing the applicant information.
 */
void printResult(const ApplicantInfo& info)
{
	cout << "\n--- Application Result ---\n";
	printSeparator('-', 26);

	if (isAccepted(info) == ApplicationStatus::HIRED)
	{
		cout << "\nCongratulations, You are Hired.\n";

		if (info.hasRecommendation)
		{
			cout << "Reason: You have recommendation\n";
		}
		else
		{
			cout << "Reason: Met age >= " << MIN_HIRING_AGE << " and have driver license requirements\n";
		}
	}
	else
	{
		cout << "\nSorry, you are Rejected.\n";

		cout << "Reason(s):\n";
		if (info.age < MIN_HIRING_AGE)
		{
			cout << "- Age must be at least " << MIN_HIRING_AGE << "\n";
		}
		if (!info.hasDriverLicense)
		{
			cout << "- Driver license required\n";
		}
	}

	printSeparator('-', 26);
}

int main()
{
	printResult(readInfo());

	return 0;
}