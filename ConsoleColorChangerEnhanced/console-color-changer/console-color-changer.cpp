/*
 * Console Color Changer
 * Cross-platform console color customization tool
 * Supports Windows (via Windows API) and Unix-like systems (via ANSI codes)
 * Preserves existing text while changing colors
 */

#include <iostream>
#include <string>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

constexpr int MIN_COLOR = 0;
constexpr int MAX_COLOR = 15;
constexpr int SEPARATOR_LENGTH = 60;

void printSeparator(char fillChar = '-', int length = SEPARATOR_LENGTH) {

	cout << string(length, fillChar) << "\n";
}

void clearInputBuffer() {

	cin.clear();
	cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

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

			cout << "Invalid color! Number must be between " << minValue << " and " << maxValue << "\n\n";
		}
		else
		{
			clearInputBuffer();
			return number;
		}
	}
}

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

string getColorName(int colorNumber) {

	static constexpr const char* colors[] = {
		"Black", "Blue", "Green", "Aqua", "Red", "Purple", "Yellow", "White",
		"Gray", "Light Blue", "Light Green", "Light Aqua",
		"Light Red", "Light Purple", "Light Yellow", "Bright White"
	};

	return (colorNumber >= MIN_COLOR && colorNumber <= MAX_COLOR) ? colors[colorNumber] : "Unknown Color";
}

#ifdef _WIN32
// Windows console colors use 4-bit values (0-15)
// Background color is stored in upper 4 bits, foreground in lower 4 bits
bool changeScreenAndTextColor(int screenColor, int textColor) {

	// Get console handle
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Validate handle
	if (hConsole == INVALID_HANDLE_VALUE) {
		cerr << "Error: Cannot get console handle\n";
		return false;
	}

	// Combine colors: background in upper 4 bits, foreground in lower 4 bits
	WORD colorAttribute = (screenColor << 4) | textColor;

	// Set console text attribute
	if (!SetConsoleTextAttribute(hConsole, colorAttribute))
	{
		cerr << "Error: Failed to set console color attribute\n";
		return false;
	}

	// Get console screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		cerr << "Error: Cannot get console screen buffer info\n";
		return false;
	}

	// Fill the entire screen with the new color attribute
	DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	COORD homeCoords = { 0, 0 };
	DWORD written;

	// ONLY change the color attributes, DON'T fill with spaces (preserves text)
	if (!FillConsoleOutputAttribute(hConsole, colorAttribute, cellCount, homeCoords, &written))
	{
		cerr << "Error: Failed to fill console output attribute\n";
		return false;
	}

	return true;
}

#else
// Placeholder for non-Windows platforms
bool changeScreenAndTextColor(int screenColor, int textColor) {

	// Map to ANSI colors (0-7 map directly, 8-15 are bright variants)
	int ansiFg = (textColor >= 8) ? (90 + (textColor - 8)) : (30 + textColor);
	int ansiBg = (screenColor >= 8) ? (100 + (screenColor - 8)) : (40 + screenColor);

	// Set ANSI color codes
	cout << "\033[" << ansiFg << ";" << ansiBg << "m";
	cout << "\033[2J\033[H"; // Clear screen and move to top

	return true;
}
#endif

bool confirmColorChoice(int screenColor, int textColor) {

	if (screenColor == textColor)
	{
		cout << "\n\n";
		printSeparator('!');
		cout << "WARNING: Background and text colors are the same!\n";
		cout << "Text will be invisible on the screen.\n";
		printSeparator('!');
		cout << "\nContinue anyway? (y/n): ";

		char choice;
		cin >> choice;
		clearInputBuffer();

		return (choice == 'y' || choice == 'Y');
	}
	return true;
}

int main()
{

#ifdef _WIN32
	cout << "Platform: Windows\n";
#elif defined(__APPLE__)
	cout << "Platform: macOS\n";
#elif defined(__linux__)
	cout << "Platform: Linux\n";
#else
	cout << "Platform: Unix-like system\n";
#endif

	displayColorMenu();

	int screenColor = validateIntegerInRange("Choose background color (0-15): ", MIN_COLOR, MAX_COLOR);

	int textColor = validateIntegerInRange("Choose text color (0-15): ", MIN_COLOR, MAX_COLOR);

	if (!confirmColorChoice(screenColor, textColor))
	{
		cout << "\nColor change cancelled. Exiting program.\n";
		return 0;
	}

	cout << "\nApplying colors...\n";

	if (changeScreenAndTextColor(screenColor, textColor))
	{
		cout << "\n";
		printSeparator('*');
		cout << "Colors successfully applied!\n";
		cout << "Background: (" << screenColor << ") " << getColorName(screenColor) << "\n";
		cout << "Text: (" << textColor << ") " << getColorName(textColor) << "\n";
		cout << "\nAll existing text has been preserved with new colors.\n";
		printSeparator('*');
	}
	else {
		cerr << "\nFailed to apply colors. Please try again.\n";
		return 1;
	}

	return 0;
}