#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Displays the user's name with a formatted message.
 * @param name The name to display
 */
void printName(const string& name)
{
	cout << "\nYour name is: " << name << '\n';
}

/**
 * @brief Prompts for user input and validates it's not empty.
 * @param prompt The message to display to the user
 * @return The user's input string
 */
string getName(const string& prompt)
{
	string name;

	while (true)
	{
		cout << prompt << flush;
		getline(cin, name);

		if (!name.empty())
		{
			return name;
		}

		cerr << "Error: Name cannot be empty. Please try again.\n";
	}
}

int main()
{
	printName(getName("Enter your name: "));

	return 0;
}