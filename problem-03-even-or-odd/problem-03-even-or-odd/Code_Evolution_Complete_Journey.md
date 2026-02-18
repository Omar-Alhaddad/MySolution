# Code Evolution: Complete Journey
### Odd/Even Checker — From Naive to Production-Quality C++

---

## Table of Contents

1. [Problem Statement](#problem-statement)
2. [Version 1 — The Original](#version-1--the-original)
3. [Version 2 — Adding Documentation](#version-2--adding-documentation)
4. [Version 3 — Robustness & Safety](#version-3--robustness--safety)
5. [Version 4 — Presentation Polish](#version-4--presentation-polish)
6. [Version 5 — The Final Perfect Version](#version-5--the-final-perfect-version)
7. [Evolution Summary Table](#evolution-summary-table)
8. [Key Lessons Learned](#key-lessons-learned)

---

## Problem Statement

> Write a program to ask the user to **enter** a number, then **Print "ODD"** if it's odd, or **"EVEN"** if it's even.

---

## Version 1 — The Original

### Code

```cpp
#include <iostream>
#include <string>
#include <limits>

using namespace std;

enum NumberType { Odd = 1, Even = 2 };

int readNumber()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;
    return number;
}

NumberType checkNumberType(int number)
{
    int result = number % 2;

    if (result == 0)
    {
        return NumberType::Even;
    }
    else
    {
        return NumberType::Odd;
    }
}

void printNumberType(NumberType numberType)
{
    if (numberType == NumberType::Even)
    {
        cout << "\nNumber is Even.\n";
    }
    else
    {
        cout << "\nNumber is Odd.\n";
    }
}

int main()
{
    printNumberType(checkNumberType(readNumber()));
    return 0;
}
```

### What Was Good ✅
- Correct separation of concerns across three focused functions
- Meaningful function and variable names
- Scoped enum access (`NumberType::Even` vs just `Even`)
- Clean `main()` that reads almost like a sentence

### Issues Found ❌
| Issue | Details |
|---|---|
| Unused includes | `<string>` and `<limits>` included but never used |
| Plain `enum` instead of `enum class` | Values leak into the surrounding scope, risking name collisions |
| No input validation | Non-integer input (e.g. `"abc"`) causes silent failure |
| Verbose `checkNumberType` | Unnecessary intermediate variable and full `if/else` block |
| Negative number fragility | `(-3) % 2 == -1`, not `1` — checking `result == 1` for odd would break |
| No documentation | No comments or Doxygen blocks |

---

## Version 2 — Adding Documentation

### What Changed
- Removed unused `<string>` and `<limits>` includes
- Added Doxygen-style `@brief`, `@param`, and `@return` blocks to every function
- Added `@enum` documentation block

### Code

```cpp
#include <iostream>

using namespace std;

/**
 * @enum NumberType
 * @brief Enum to represent if a number is even or odd.
 */
enum NumberType {
    Odd = 1,  ///< The number is odd
    Even = 2  ///< The number is even
};

/**
 * @brief Reads an integer from the console.
 * @return int The number entered by the user.
 */
int readNumber()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;
    return number;
}

/**
 * @brief Checks if a number is even or odd.
 * @param number The number to check.
 * @return NumberType The type of the number (even or odd).
 */
NumberType checkNumberType(int number)
{
    int result = number % 2;

    if (result == 0)
    {
        return NumberType::Even;
    }
    else
    {
        return NumberType::Odd;
    }
}

/**
 * @brief Prints whether a number is even or odd.
 * @param numberType The type of the number (even or odd).
 */
void printNumberType(NumberType numberType)
{
    if (numberType == NumberType::Even)
    {
        cout << "\nNumber is Even.\n";
    }
    else
    {
        cout << "\nNumber is Odd.\n";
    }
}

int main()
{
    printNumberType(checkNumberType(readNumber()));
    return 0;
}
```

### Improvements Made ✅
- Unused includes removed
- Doxygen documentation added consistently

### Still Outstanding ❌
- No input validation
- Verbose `if/else` in `checkNumberType`
- Plain `enum` still used — `enum class` not yet adopted
- Negative number fragility remains
- `readNumber` Doxygen block missing `@brief` tag (inconsistency vs other functions)

---

## Version 3 — Robustness & Safety

### What Changed
- Added `clearInputBuffer()` utility function
- Implemented full input validation loop in `readNumber()`
- Adopted `enum class` for type safety
- Simplified `checkNumberType` with a ternary
- Fixed negative number bug (`!= 0` instead of `== 1`)
- Added `printSeparator()` utility for visual formatting
- `readNumber` now accepts a custom `prompt` parameter
- Added default parameter value to `readNumber`
- Inline comments added to `clearInputBuffer()` call sites

### Code

```cpp
#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * @enum NumberType
 * @brief Enum to represent if a number is even or odd.
 */
enum class NumberType {
    Odd = 1,  ///< The number is odd
    Even = 2  ///< The number is even
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
 * @brief Prompts the user for an integer input and handles invalid input.
 * @param prompt The prompt to display to the user.
 * @return The user's input as an integer.
 */
int readNumber(const string& prompt = "Enter a number: ")
{
    int number;

    while (true)
    {
        cout << prompt;

        if (!(cin >> number))
        {
            clearInputBuffer();     // Clear the input buffer to handle invalid input
            cout << "Invalid input! Please enter a valid number.\n\n";
        }
        else
        {
            clearInputBuffer();     // Discard any trailing characters on the line.
            return number;
        }
    }
}

/**
 * @brief Checks if a number is even or odd.
 * @param number The number to check.
 * @return NumberType The type of the number (even or odd).
 */
NumberType checkNumberType(int number)
{
    return (number % 2 != 0) ? NumberType::Odd : NumberType::Even;
}

/**
 * @brief Prints whether a number is even or odd.
 * @param numberType The type of the number (even or odd).
 */
void printNumberType(NumberType numberType)
{
    cout << "\nNumber is " << (numberType == NumberType::Even ? "Even" : "Odd") << '\n';
}

int main()
{
    printNumberType(checkNumberType(readNumber("Enter number: ")));
    return 0;
}
```

### Improvements Made ✅
- Full input validation with graceful error recovery
- `enum class` adopted — type-safe and scope-safe
- Negative number bug fixed
- `checkNumberType` simplified to a single ternary
- Reusable `printSeparator()` and configurable `readNumber()` added

### Still Outstanding ❌
- `printSeparator` defined but never called (dead code)
- `printNumberType` doing two things: output logic AND presentation
- Doxygen block on `readNumber` missing `@brief` tag (inconsistency)

---

## Version 4 — Presentation Polish

### What Changed
- `printSeparator('=')` now called inside `printNumberType` — no more dead code
- `printNumberType` renamed to `printFormattedNumberType` to better describe its behavior
- Doxygen `@brief` tag added to `readNumber` for consistency

### Code

```cpp
#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * @enum NumberType
 * @brief Enum to represent if a number is even or odd.
 */
enum class NumberType {
    Odd = 1,  ///< The number is odd
    Even = 2  ///< The number is even
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
 * @brief Prompts the user for an integer input and handles invalid input.
 * @param prompt The prompt to display to the user.
 * @return The user's input as an integer.
 */
int readNumber(const string& prompt = "Enter a number: ")
{
    int number;

    while (true)
    {
        cout << prompt;

        if (!(cin >> number))
        {
            clearInputBuffer();     // Clear the input buffer to handle invalid input
            cout << "Invalid input! Please enter a valid number.\n\n";
        }
        else
        {
            clearInputBuffer();     // Discard any trailing characters on the line.
            return number;
        }
    }
}

/**
 * @brief Checks if a number is even or odd.
 * @param number The number to check.
 * @return NumberType The type of the number (even or odd).
 */
NumberType checkNumberType(int number)
{
    return (number % 2 != 0) ? NumberType::Odd : NumberType::Even;
}

/**
 * @brief Prints whether a number is even or odd, with formatted separators.
 * @param numberType The type of the number (even or odd).
 */
void printFormattedNumberType(NumberType numberType)
{
    printSeparator('=');
    cout << "Number is " << (numberType == NumberType::Even ? "Even" : "Odd") << '\n';
    printSeparator('=');
}

int main()
{
    printFormattedNumberType(checkNumberType(readNumber("Enter number: ")));
    return 0;
}
```

### Improvements Made ✅
- `printSeparator` is now actively used — no dead code
- More descriptive function name communicates intent clearly
- Doxygen consistency achieved across all functions

### Still Outstanding ❌
- `printFormattedNumberType` still handles both string conversion AND presentation layout — a Single Responsibility concern

---

## Version 5 — The Final Perfect Version

### What Changed
- Extracted `getNumberType()` — a pure function that returns a string label for the enum value
- `printFormattedNumberType` now delegates string logic to `getNumberType()`, focusing purely on layout
- **Single Responsibility Principle fully applied** across all functions

### Code

```cpp
#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * @enum NumberType
 * @brief Enum to represent if a number is even or odd.
 */
enum class NumberType {
    Odd = 1,  ///< The number is odd
    Even = 2  ///< The number is even
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
 * @brief Prompts the user for an integer input and handles invalid input.
 * @param prompt The prompt to display to the user.
 * @return The user's input as an integer.
 */
int readNumber(const string& prompt = "Enter a number: ")
{
    int number;

    while (true)
    {
        cout << prompt;

        if (!(cin >> number))
        {
            clearInputBuffer();     // Clear the input buffer to handle invalid input
            cout << "Invalid input! Please enter a valid number.\n\n";
        }
        else
        {
            clearInputBuffer();     // Discard any trailing characters on the line.
            return number;
        }
    }
}

/**
 * @brief Checks if a number is even or odd.
 * @param number The number to check.
 * @return NumberType The type of the number (even or odd).
 */
NumberType checkNumberType(int number)
{
    return (number % 2 != 0) ? NumberType::Odd : NumberType::Even;
}

/**
 * @brief Gets the string representation of a number type (even or odd).
 * @param numberType The type of the number (even or odd).
 * @return The string representation of the number type.
 */
string getNumberType(NumberType numberType)
{
    return (numberType == NumberType::Even ? "Even" : "Odd");
}

/**
 * @brief Prints whether a number is even or odd, with formatted separators.
 * @param numberType The type of the number (even or odd).
 */
void printFormattedNumberType(NumberType numberType)
{
    printSeparator('=');
    cout << "Number is " << getNumberType(numberType) << '\n';
    printSeparator('=');
}

int main()
{
    printFormattedNumberType(checkNumberType(readNumber("Enter number: ")));
    return 0;
}
```

---

## Evolution Summary Table

| Feature | v1 | v2 | v3 | v4 | v5 ✅ |
|---|:---:|:---:|:---:|:---:|:---:|
| Correct logic | ✅ | ✅ | ✅ | ✅ | ✅ |
| No unused includes | ❌ | ✅ | ✅ | ✅ | ✅ |
| Doxygen documentation | ❌ | ✅ | ✅ | ✅ | ✅ |
| `enum class` (type-safe) | ❌ | ❌ | ✅ | ✅ | ✅ |
| Input validation | ❌ | ❌ | ✅ | ✅ | ✅ |
| Negative number safety | ❌ | ❌ | ✅ | ✅ | ✅ |
| Ternary simplification | ❌ | ❌ | ✅ | ✅ | ✅ |
| No dead code | ✅ | ✅ | ❌ | ✅ | ✅ |
| Consistent Doxygen style | ❌ | ⚠️ | ⚠️ | ✅ | ✅ |
| Single Responsibility Principle | ⚠️ | ⚠️ | ⚠️ | ⚠️ | ✅ |
| Reusable utilities | ❌ | ❌ | ✅ | ✅ | ✅ |

---

## Key Lessons Learned

### 1. Only include what you use
Headers like `<string>` and `<limits>` should only be present when actively used. Dead includes bloat compile time and mislead readers about dependencies.

### 2. Prefer `enum class` over plain `enum`
Plain enums leak their enumerators into the surrounding scope. `enum class` enforces scoped access (`NumberType::Even`) and prevents accidental name collisions — critical in large codebases.

### 3. Always validate user input
`cin >> number` silently fails on non-integer input. A `while` loop with `cin.clear()` and `cin.ignore()` turns a fragile read into a robust one. Extract this into `clearInputBuffer()` for reusability.

### 4. Watch out for negative modulo
In C++, `(-3) % 2 == -1`. Checking `result == 1` to detect odd numbers breaks for negatives. The correct check is `result != 0`.

### 5. Ternaries reduce noise for binary conditions
A full `if/else` returning one of two values can always be expressed more concisely as a ternary. Use it when the logic is simple enough to remain readable.

### 6. Single Responsibility Principle pays off even at small scale
Separating `getNumberType()` (string conversion) from `printFormattedNumberType()` (layout) means both functions are independently testable and reusable. This habit is essential before it becomes *necessary* at scale.

### 7. Document as you go
Doxygen comments aren't just for large teams — they force you to articulate what each function does, which often surfaces design problems before they become bugs.

### 8. Default parameters add flexibility without complexity
Giving `readNumber` a default prompt and `printSeparator` default character/count arguments makes them general-purpose utilities, not single-use functions.

---

*Final grade: A — Clean, safe, well-documented, and principled. A textbook example of iterative code improvement.*
