#include <iostream>
using namespace std;

int main()
{
    // Fibonacci series : the sum of two elements defines the next
    int a = 0, b = 1, temp, n, count = 0;

    cout << "Fibonacci Series to Number: ";
    cin >> n;

    cout << a << "\n";
    count++;

    while (count < n) {
        cout << b << "\n";
        temp = b;
        b = a + b;
        a = temp;
        count++;
    }

    return 0;
}