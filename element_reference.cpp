#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& MAP, const Key& KEY) {
    if(MAP.count(KEY) != 0) {
        cout << "yiss" << endl;
        return MAP.at(KEY);
    } else {
        throw runtime_error("friend");
    }
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}