#include <iostream>
#include <list>
using namespace std;

int main() {


    int Temperature[5] = { 18, 22, 26, 15, 30 };
    int TotalCost = 0;
    int HeatingCost = 0, CoolingCost = 0;
    int size = sizeof(Temperature) / sizeof(Temperature[0]);
    bool isNeedsHeating = false, isNeedsCooling = false;

    cout << "Temperature readings: [";
    for (int i = 0; i < size; i++)
    {
        if (Temperature[i] < 20 && isNeedsHeating == false)
        {
            isNeedsHeating = true;
        }
        if (Temperature[i] > 25 && isNeedsCooling == false)
        {
            isNeedsCooling = true;
        }
        cout << Temperature[i];
        if (i < size - 1)
        {
            cout << ", ";
        }

    }
    cout << "]\n";

    if (isNeedsHeating)
    {
        HeatingCost += 25;
    }

    if (isNeedsCooling)
    {
        CoolingCost += 35;
    }

    TotalCost = HeatingCost + CoolingCost;

    cout << "Heating cost: $" << HeatingCost << " (for readings below 20C)" << endl;
    cout << "Cooling cost: $" << CoolingCost << " (for readings above 25C)" << endl;
    cout << "Total cost: $" << TotalCost << endl;

    return 0;
}
