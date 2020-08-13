#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border);
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
	auto it = numbers.lower_bound(border);
	if (it == numbers.begin()) {
		return it;
	}
	if (it == numbers.end()) {
		return prev(it);
	}
	return (border - *prev(it) <= *it - border) ? prev(it) : it;
}