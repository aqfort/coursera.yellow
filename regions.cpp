#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

//Write the FindMaxRepetitionCount function that accepts
//a base of regions and determines which maximum number
//of repetitions it contains. Two records (objects of Region type)
//are considered different if they differ by at least one field.

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

bool operator<(const Region &lhs, const Region &rhs) {
    auto tuple_lhs = tie(lhs.std_name,
                         lhs.parent_std_name,
                         lhs.names,
                         lhs.population);
    auto tuple_rhs = tie(rhs.std_name,
                         rhs.parent_std_name,
                         rhs.names,
                         rhs.population);
    return tuple_lhs < tuple_rhs;
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    int result(0);
    map<Region, int> regions_without_repeatition;
    for (const auto &item : regions) {
        regions_without_repeatition[item]++;
        if (regions_without_repeatition[item] > result) {
            result = regions_without_repeatition[item];
        }
    }
    return result;
}

int main() {
    cout << FindMaxRepetitionCount({
        {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
        },
        {
               "Russia",
               "Eurasia",
               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
               89
        },
        {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
        },
        {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
               89
        },
        {
               "Russia",
               "Eurasia",
               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
               89
        },
    }) << endl;

    cout << FindMaxRepetitionCount({
        {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},      {Lang::IT, "Mosca"}},
               89
        },
        {
               "Russia",
               "Eurasia",
               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"},      {Lang::IT, "Russia"}},
               89
        },
        {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
               89
        },
        {
               "Moscow",
               "Toulouse",
               {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},      {Lang::IT, "Mosca"}},
               89
        },
        {
               "Moscow",
               "Russia",
               {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},      {Lang::IT, "Mosca"}},
               31
        },
    }) << endl;

    return 0;
}