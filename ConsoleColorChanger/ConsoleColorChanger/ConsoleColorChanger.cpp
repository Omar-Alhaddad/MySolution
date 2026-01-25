
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Constants
constexpr int MIN_COLOR = 0;
constexpr int MAX_COLOR = 15;
constexpr int SEPARATOR_LENGTH = 60;

// Color enumeration for type safety
enum class ConsoleColor : int {
	Black = 0, Blue = 1, Green = 2, Aqua = 3, Red = 4, Purple = 5, Yellow = 6, White = 7, Gray = 8, LightBlue = 9,
	LightGreen = 10, LightAqua = 11, LightRed = 12, LightPurple = 13, LightYellow = 14, BrightWhite = 15
};

// Utility Functions
void printSeparator(char fillChar = '-', int length = SEPARATOR_LENGTH) {

	cout << string(length, fillChar) << "\n";
}

void clearInputBuffer() {

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {

	system("cls");
}

// Input validation with range checking
int validateIntegerInRange(const string& prompt, int minValue, int maxValue) {

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
			clearInputBuffer();

			cout << "Invalid screen color! Number must be between " << minValue << " and " << maxValue << "\n\n";
		}
		else
		{
			clearInputBuffer();
			return number;
		}
	}
}

// Display color selection menu
void displayColorMenu() {
	printSeparator('=');
	cout << "           CONSOLE COLOR CHANGER\n";
	printSeparator('=');
	cout << "\nPlease choose the number of your color:\n\n";

	cout << "  STANDARD COLORS:              BRIGHT COLORS:\n";
	cout << "  ----------------              --------------\n";
	cout << "  (0)  Black                    (8)  Gray\n";
	cout << "  (1)  Blue                     (9)  Light Blue\n";
	cout << "  (2)  Green                    (10) Light Green\n";
	cout << "  (3)  Aqua                     (11) Light Aqua\n";
	cout << "  (4)  Red                      (12) Light Red\n";
	cout << "  (5)  Purple                   (13) Light Purple\n";
	cout << "  (6)  Yellow                   (14) Light Yellow\n";
	cout << "  (7)  White                    (15) Bright White\n";

	printSeparator('=');
}

// Get color name from color code
string getColorName(int colorNumber) {

	static const string colors[] = {
		"Black", "Blue", "Green", "Aqua","Red", "Purple", "Yellow", "White","Gray", "Light Blue",
		"Light Green", "Light Aqua","Light Red", "Light Purple", "Light Yellow", "Bright White"
	};

	return (colorNumber >= MIN_COLOR && colorNumber <= MAX_COLOR) ? colors[colorNumber] : "Unknown Color";
}

// Convert color number to hex character
string colorToHex(int colorNumber) {

	static const char hexDigits[] = "0123456789ABCDEF";
	return string(1, hexDigits[colorNumber]);
}

// Display preview of selected colors
void displayPreview(int bgColor, int fgColor) {
	cout << '\n';
	printSeparator('-');
	cout << "SELECTED COLORS:\n";
	cout << "Background: (" << bgColor << ") " << getColorName(bgColor) << '\n';
	cout << "Text:       (" << fgColor << ") " << getColorName(fgColor) << '\n';
	printSeparator('-');
}

// Confirm color choice, especially if they match
bool confirmColorChoice(int screenColor, int textColor) {

	if (screenColor == textColor)
	{
		cout << "\n\n";
		printSeparator('!');
		cout << "WARNING: Background and text colors are the same!\n";
		cout << "Text will be invisible on the screen.\n";
		printSeparator('!');

		return false;
	}
	return true;
}

// Change console colors using Windows color command
bool changeScreenAndTextColor(int screenColor, int textColor) {

	// Windows console colors use 4-bit values (0-15)
	// Screen color is stored in upper 4 bits (x), text color in lower 4 bits (y). "color xy"
	string command = "color " + colorToHex(screenColor) + colorToHex(textColor);

	int result = system(command.c_str());

	if (result != 0)
	{
		cerr << "Error: Failed to change console colors.\n";
		return false;
	}

	return true;
}

// Ask if user wants to continue
bool askToContinue() {

	cout << "\n\nWould you like to change colors again? (y/n): ";
	char choice;
	cin >> choice;
	clearInputBuffer();

	return (choice == 'y' || choice == 'Y');
}

// Display welcome message
void displayWelcome() {
	cout << "Welcome to Console Color Changer!\n";
	cout << "Customize your Windows console colors easily.\n\n";
}

// Display success message
void displaySuccess(int bgColor, int fgColor) {
	cout << '\n';
	printSeparator('*');
	cout << "Colors successfully applied!\n";
	cout << "Background: " << getColorName(bgColor) << '\n';
	cout << "Text:       " << getColorName(fgColor) << '\n';
	printSeparator('*');
}

int main()
{
	displayWelcome();

	bool continueProgram = true;

	while (continueProgram)
	{
		// Clear screen before showing menu
		clearScreen();

		displayColorMenu();

		// Get user color choices
		int screenColor = validateIntegerInRange("Choose screen color: ", MIN_COLOR, MAX_COLOR);

		int textColor = validateIntegerInRange("Choose text color: ", MIN_COLOR, MAX_COLOR);

		// Show preview
		displayPreview(screenColor, textColor);

		// Confirm if colors match
		if (!confirmColorChoice(screenColor, textColor))
		{
			cout << "\nColor change cancelled. Please choose different colors.\n";
			continue;
		}

		cout << "\nApplying colors...\n";

		if (changeScreenAndTextColor(screenColor, textColor))
		{
			displaySuccess(screenColor, textColor);
		}
		else
		{
			cerr << "Failed to apply colors. Please try again.\n";
		}

		// Ask to continue
		continueProgram = askToContinue();
	}

	cout << "\nThank you for using Console Color Changer!\n";

	return 0;
}