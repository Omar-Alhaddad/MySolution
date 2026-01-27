/******************************************************************************
 * Project: Arab World Explorer
 * Description: A C++ console application that provides comprehensive
 *              information about the 22 Arab League member countries
 * Features: Country lookup, population data, cultural information, ISO codes
 * Author: [Omar Al-haddad]
 * Date: January 2026
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <iomanip>
#include <windows.h>
using namespace std;

constexpr int MIN_INPUT = 1;          // First valid country ID
constexpr int MAX_INPUT = 22;         // Total number of Arab countries
constexpr int TOTAL_COUNTRIES = 23;   // Including "Unknown" at index 0
constexpr int SEPARATOR_LENGTH = 60;  // Length of separator lines

enum class ArabCountry : int {
	Unknown = 0, Yemen, Algeria, Bahrain, Comoros, Djibouti, Egypt, Iraq, Jordan, Kuwait, Lebanon, Libya, Mauritania,
	Morocco, Oman, Palestine, Qatar, SaudiArabia, Somalia, Sudan, Syria, Tunisia, UnitedArabEmirates
};

static_assert(static_cast<int>(ArabCountry::UnitedArabEmirates) == MAX_INPUT,
	"Enum count must match MAX_INPUT");

struct CountryInfo
{
	string name;		   // Country name
	string capital;		   // Capital city
	string currency;       // Currency used like USD, EUR, etc.
	string continent;      // Continent where the country is located
	string flag;           // Emoji flag
	ArabCountry id = ArabCountry::Unknown; // Enum ID
	long long population;  // Population of the country
	string language;       // Official language
	string phoneCode;      // International phone code
};

inline void printSeparator(char fillChar = '-', size_t length = SEPARATOR_LENGTH) {

	cout << string(length, fillChar) << endl;
}

void clearInputBuffer() {

	cin.clear();
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

int validateCountryID(const string& prompt, int minValue, int maxValue) {

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

			cout << "Invalid country number! Number must be between " << minValue << " and " << maxValue << "\n\n";
		}
		else
		{
			clearInputBuffer();
			return number;
		}
	}
}

void displayCountryMenu() {

	printSeparator('=');
	cout << "              ARAB COUNTRIES MENU\n";
	printSeparator('=');

	cout << "\nPlease choose a country number:\n\n";
	cout << "  COUNTRIES (1-11):              COUNTRIES (12-22):\n";
	cout << "  ----------------              -----------------\n";
	cout << "  (1)  Yemen                    (12) Mauritania\n";
	cout << "  (2)  Algeria                  (13) Morocco\n";
	cout << "  (3)  Bahrain                  (14) Oman\n";
	cout << "  (4)  Comoros                  (15) Palestine\n";
	cout << "  (5)  Djibouti                 (16) Qatar\n";
	cout << "  (6)  Egypt                    (17) Saudi Arabia\n";
	cout << "  (7)  Iraq                     (18) Somalia\n";
	cout << "  (8)  Jordan                   (19) Sudan\n";
	cout << "  (9)  Kuwait                   (20) Syria\n";
	cout << "  (10) Lebanon                  (21) Tunisia\n";
	cout << "  (11) Libya                    (22) United Arab Emirates\n";

	printSeparator('=');
}

static const CountryInfo& getCountryInfo(int countryID) {

	static const CountryInfo arabCountries[TOTAL_COUNTRIES] = {

	{ "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", ArabCountry::Unknown, 0, "Unknown", "0" },
	{ "Yemen", "Sana'a", "YER", "Asia", "🇾🇪", ArabCountry::Yemen, 42400000, "Arabic", "+967" },
	{ "Algeria", "Algiers", "DZD", "Africa", "🇩🇿", ArabCountry::Algeria, 47800000, "Arabic, Tamazight", "+213" },
	{ "Bahrain", "Manama", "BHD", "Asia", "🇧🇭", ArabCountry::Bahrain, 1660000, "Arabic", "+973" },
	{ "Comoros", "Moroni", "KMF", "Africa", "🇰🇲", ArabCountry::Comoros, 890000, "Comorian, Arabic, French", "+269" },
	{ "Djibouti", "Djibouti City", "DJF", "Africa", "🇩🇯", ArabCountry::Djibouti, 1200000, "Arabic, French", "+253" },
	{ "Egypt", "Cairo", "EGP", "Africa", "🇪🇬", ArabCountry::Egypt, 119400000, "Arabic", "+20" },
	{ "Iraq", "Baghdad", "IQD", "Asia", "🇮🇶", ArabCountry::Iraq, 47600000, "Arabic, Kurdish", "+964" },
	{ "Jordan", "Amman", "JOD", "Asia", "🇯🇴", ArabCountry::Jordan, 11500000, "Arabic", "+962" },
	{ "Kuwait", "Kuwait City", "KWD", "Asia", "🇰🇼", ArabCountry::Kuwait, 5100000, "Arabic", "+965" },
	{ "Lebanon", "Beirut", "LBP", "Asia", "🇱🇧", ArabCountry::Lebanon, 5900000, "Arabic", "+961" },
	{ "Libya", "Tripoli", "LYD", "Africa", "🇱🇾", ArabCountry::Libya, 7500000, "Arabic", "+218" },
	{ "Mauritania", "Nouakchott", "MRU", "Africa", "🇲🇷", ArabCountry::Mauritania, 5400000, "Arabic", "+222" },
	{ "Morocco", "Rabat", "MAD", "Africa", "🇲🇦", ArabCountry::Morocco, 38600000, "Arabic, Amazigh", "+212" },
	{ "Oman", "Muscat", "OMR", "Asia", "🇴🇲", ArabCountry::Oman, 5600000, "Arabic", "+968" },
	{ "Palestine", "Jerusalem", "ILS", "Asia", "🇵🇸", ArabCountry::Palestine, 5560000, "Arabic", "+970" },
	{ "Qatar", "Doha", "QAR", "Asia", "🇶🇦", ArabCountry::Qatar, 3200000, "Arabic", "+974" },
	{ "Saudi Arabia", "Riyadh", "SAR", "Asia", "🇸🇦", ArabCountry::SaudiArabia, 35000000, "Arabic", "+966" },
	{ "Somalia", "Mogadishu", "SOS", "Africa", "🇸🇴", ArabCountry::Somalia, 20000000, "Somali, Arabic", "+252" },
	{ "Sudan", "Khartoum", "SDG", "Africa", "🇸🇩", ArabCountry::Sudan, 52300000, "Arabic, English", "+249" },
	{ "Syria", "Damascus", "SYP", "Asia", "🇸🇾", ArabCountry::Syria, 26100000, "Arabic", "+963" },
	{ "Tunisia", "Tunis", "TND", "Africa", "🇹🇳", ArabCountry::Tunisia, 12400000, "Arabic", "+216" },
	{ "United Arab Emirates", "Abu Dhabi", "AED", "Asia", "🇦🇪", ArabCountry::UnitedArabEmirates, 11350000, "Arabic", "+971" }
	};

	return (countryID >= 1 && countryID <= 22) ? arabCountries[countryID] : arabCountries[0];
}

static string_view getCountryISO(ArabCountry countryID) {

	switch (countryID)
	{
	case ArabCountry::Yemen:               return "887";
	case ArabCountry::Algeria:             return "012";
	case ArabCountry::Bahrain:             return "048";
	case ArabCountry::Comoros:             return "174";
	case ArabCountry::Djibouti:            return "262";
	case ArabCountry::Egypt:               return "818";
	case ArabCountry::Iraq:                return "368";
	case ArabCountry::Jordan:              return "400";
	case ArabCountry::Kuwait:              return "414";
	case ArabCountry::Lebanon:             return "422";
	case ArabCountry::Libya:               return "434";
	case ArabCountry::Mauritania:          return "478";
	case ArabCountry::Morocco:             return "504";
	case ArabCountry::Oman:                return "512";
	case ArabCountry::Palestine:           return "275";
	case ArabCountry::Qatar:               return "634";
	case ArabCountry::SaudiArabia:         return "682";
	case ArabCountry::Somalia:             return "706";
	case ArabCountry::Sudan:               return "729";
	case ArabCountry::Syria:               return "760";
	case ArabCountry::Tunisia:             return "788";
	case ArabCountry::UnitedArabEmirates:  return "784";
	default:                               return "000"; // Invalid / Unknown
	}
}

string formatValue(double value, const char* suffix) {

	ostringstream oss;

	oss << fixed << setprecision(2) << value;

	string result = oss.str();

	// Remove unnecessary trailing zeros
	if (result.substr(result.size() - 3) == ".00")
	{
		result.erase(result.size() - 3);
	}
	else if (result.back() == '0')
	{
		result.pop_back();
	}

	return result + suffix;
}

string formatPopulation(long long population) {

	if (population >= 1000000000)
	{
		double value = population / 1e9;
		return formatValue(value, "B");
	}
	else if (population >= 1000000)
	{
		double value = population / 1e6;
		return formatValue(value, "M");
	}
	else if (population >= 1000)
	{
		double value = population / 1e3;
		return formatValue(value, "K");
	}

	// If no unit matched (population < 1000)
	return to_string(population);
}

string formatLanguage(const string& langStr) {

	if (langStr.empty() || langStr == "Unknown")
	{
		return "Official Language: Unknown";
	}

	string prefix = (langStr.find(',') != string::npos) ? "Official Languages: " : "Official Language: ";

	return  prefix + langStr;
}

void printCountryInfo(const CountryInfo& country) {

	printSeparator('*');
	cout << "Country Information: \n";
	printSeparator('-');
	cout << left;  // Left-align for better readability
	cout << setw(20) << "Country ID: " << static_cast<int>(country.id) << "\n";
	cout << setw(20) << "Country Name: " << country.name << " " << country.flag << "\n";
	cout << setw(20) << "Capital City: " << country.capital << "\n";
	cout << setw(20) << "Country Currency: " << country.currency << "\n";
	cout << setw(20) << "Continent: " << country.continent << "\n";
	cout << formatLanguage(country.language) << "\n";
	cout << setw(20) << "Phone Code: " << country.phoneCode << "\n";
	cout << setw(20) << "Population: " << formatPopulation(country.population) << "\n";
	cout << setw(20) << "ISO Code: " << getCountryISO(country.id) << endl;
	printSeparator('-');
}

int main()
{
	// Program read a country number from the user and display information about the selected Arab country.
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#else
	std::locale::global(std::locale(""));
#endif

	displayCountryMenu();

	int countryID = validateCountryID("Enter your country ID (1-22): ", MIN_INPUT, MAX_INPUT);

	const CountryInfo& country = getCountryInfo(countryID);

	printCountryInfo(country);

	return 0;
}