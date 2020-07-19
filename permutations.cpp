#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    vector<int> numbers;

    cin >> N;

    for (int i = 1; i <= N; i++) {
        numbers.emplace_back(i);
    }

    sort(numbers.rbegin(), numbers.rend());

    do {
        for (const auto& i : numbers) {
            cout << i << ' ';
        }
        cout << endl;
    } while (prev_permutation(numbers.begin(), numbers.end()));

    return 0;
}