#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

int main() {
    // vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_end - range_begin < 3) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto range_length = (range_end - range_begin) / 3;

    MergeSort(elements.begin(), elements.begin() + range_length);
    MergeSort(elements.begin() + range_length, elements.begin() + 2 * range_length);
    MergeSort(elements.begin() + 2 * range_length, elements.end());

    vector<typename RandomIt::value_type> temp;

    merge(elements.begin(), elements.begin() + range_length, elements.begin() + range_length, elements.begin() + 2 * range_length, back_inserter(temp));

    merge(temp.begin(), temp.end(), elements.begin() + 2 * range_length, elements.end(), range_begin);

    // MergeSort(range_begin, range_begin + range_length);
    // MergeSort(range_begin + range_length, range_begin + 2 * range_length);
    // MergeSort(range_begin + 2 * range_length, range_end);

    // merge(range_begin, range_begin + range_length,
    //       range_begin + range_length, range_begin + 2 * range_length,
    //       elements.begin());

    // merge(elements.begin(), elements.begin() + 2 * range_length, elements.begin() + 2 * range_length, elements.end(), range_begin);
}
