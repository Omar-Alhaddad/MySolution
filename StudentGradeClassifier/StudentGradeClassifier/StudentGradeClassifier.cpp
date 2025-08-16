#include <iostream>
#include<limits>
using namespace std;

int main() {

    int StudentGrade;


    cout << "Please enter your grade: ";

    while (!(cin >> StudentGrade) || !(StudentGrade >= 0 && StudentGrade <= 100))
    {
        cout << "Invalid input! Please enter a valid number from 0 to 100 : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (StudentGrade >= 90)
    {
        cout << "Grade: A\n";
    }
    else if (StudentGrade >= 80)
    {
        cout << "Grade: B\n";
    }
    else if (StudentGrade >= 70)
    {
        cout << "Grade: C\n";
    }
    else if (StudentGrade >= 60)
    {
        cout << "Grade: D\n";
    }
    else
    {
        cout << "Grade: F\n";
    }

    return 0;
}