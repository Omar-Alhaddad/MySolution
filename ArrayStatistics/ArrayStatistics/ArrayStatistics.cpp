
#include <iostream>
#include <string>
#include <limits>

using namespace std;

constexpr int MIN_INPUT = 1;
constexpr int MAX_INPUT = 100;

void printSeparator(char fillChar = '-', int length = 50) {

	cout << string(length, fillChar) << '\n';
}

void clearInputBuffer() {

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int validatePositiveNumber(const string& prompt, int minValue, int maxValue = INT_MAX) {

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

			cout << "Invalid input! Number must be between " << minValue << " and " << maxValue << "\n\n";
		}
		else
		{
			clearInputBuffer();
			return number;
		}
	}
}

void readArrayData(int arr[100], int& length) {

	length = validatePositiveNumber("How many numbers do you want to enter (1 - 100): ", MIN_INPUT, MAX_INPUT);

	for (int i = 0; i < length; i++)
	{
		arr[i] = validatePositiveNumber("Enter number " + to_string(i + 1) + " : ", MIN_INPUT);
	}
}

void printArrayData(const int arr[100], int length) {

	for (int i = 0; i < length; i++)
	{
		cout << "Number [" << i + 1 << "] : " << arr[i] << '\n';
	}
}

int calculateArraySum(const int arr[100], int length) {

	int sum = 0;

	for (int i = 0; i < length; i++)
	{
		sum += arr[i];
	}

	return sum;
}

float calculateArrayAverage(const int arr[100], int length) {

	if (length == 0) return 0.0f;

	return static_cast<float>(calculateArraySum(arr, length)) / length;
}

int main()
{
	int arr[100], length = 0;

	readArrayData(arr, length);

	printArrayData(arr, length);

	printSeparator('*');

	cout << "Sum = " << calculateArraySum(arr, length) << '\n';
	cout << "Average = " << calculateArrayAverage(arr, length) << '\n';

	return 0;
}