#include <iostream>

#include "sum_reverse_sort.h"

using namespace std;

int main() {
    int a, b, c;
    string line;
    vector<int> array;

    a = 5;
    b = -6;

    line = "hello friend";

    array = {5, 6, 4, 7, 3, 2, 9, 8, 0, 1};

    cout << "a + b = " << Sum(a, b) << endl;

    cout << line << " -> " << Reverse(line) << endl;

    cout << "array:";
    for (size_t i = 0; i < array.size(); i++) {
        cout << ' ' << array.at(i);
    }
    cout << endl;

    Sort(array);

    cout << "sorted array:";
        for (size_t i = 0; i < array.size(); i++) {
        cout << ' ' << array.at(i);
    }

    return 0;
}