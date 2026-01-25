#include <iostream>
#include <string>   
#include <unordered_set>
#include <algorithm>
using namespace std;

string toUpperCase(const string& str) {

    string Result = str;

    transform(Result.begin(), Result.end(), Result.begin(),
        [](unsigned char c) {return toupper(c); });

    return Result;
}

int main() {

    int CustomersAge;
    string MovieRating;
    unordered_set<string> ValidMovieRating = { "G", "PG", "PG-13", "R", "NC-17" };

    cout << "Please enter your age: ";
    while (!(cin >> CustomersAge) || !(CustomersAge >= 0 && CustomersAge <= 120))
    {
        cout << "Invalid input! Please enter a valid number from 0 to 120 : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true)
    {
        cout << "Please enter a movie rating (G, PG, PG-13, R, NC-17): ";
        getline(cin, MovieRating);

        // Convert the input to uppercase for case-insensitive comparison
        MovieRating = toUpperCase(MovieRating);

        if (ValidMovieRating.find(MovieRating) != ValidMovieRating.end())
        {
            break;
        }
        else
        {
            cout << "\nInvalid rating entered. ";
        }
    };



    return 0;
}