#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

template <typename First, typename Second>
ostream& operator << (ostream& out, const pair<First, Second>& p);

template <typename T>
ostream& operator << (ostream& out, const vector<T>& v);

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m);

template <typename Collection>
string Join(const Collection& c, char d);

template <typename T>
T Sqr(const T& i);

template <typename T>
vector<T> Sqr(const vector<T>& v);

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p);

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);

int main() {
    vector<double> v = {1.4, 2, 3};
    cout << v << endl;
    map<int, double> m = {{1, 2.5}, {3, 4}};
    cout << m << endl;
    vector<vector<int>> vv = {{1, 2}, {3, 4}};
    cout << vv << endl;

    cout << Sqr(m) << endl;
    return 0;
}

template <typename T>
T Sqr(const T& i) {
    return i * i;
}

template <typename T>
vector<T> Sqr(const vector<T>& v) {
    vector<T> res;
    for(const auto& i : v) {
        res.emplace_back(Sqr(i));
    }
    return res;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
    pair<First, Second> res;
    res.first = Sqr(p.first);
    res.second = Sqr(p.second);
    return res;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
    map<Key, Value> res;
    for(const auto& i : m) {
        res[i.first] = Sqr(i.second);
    }
    return res;
}

template <typename Collection>
string Join(const Collection& c, char d) {
    stringstream ss;
    bool first = true;
    for(const auto& i : c) {
        if (!first) {
            ss << d;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template <typename First, typename Second>
ostream& operator << (ostream& out, const pair<First, Second>& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
ostream& operator << (ostream& out, const vector<T>& v) {
    return out << '[' << Join(v, ',') << ']';
}

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m) {
    return out << '{' << Join(m, ',') << '}';
}
