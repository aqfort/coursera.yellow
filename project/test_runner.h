#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>



using namespace std;



template <typename Collection>
string Join(const Collection& c, char d);

//template <typename First, typename Second>
//ostream& operator << (ostream& out, const pair<First, Second>& p);

template <typename T>
ostream& operator << (ostream& out, const vector<T>& v);

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m);

template <typename T>
ostream& operator << (ostream& out, const set<T>& s);

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint);

void Assert(bool b, const string& hint);

class TestRunner {
public:
	TestRunner();

	~TestRunner();

	template<class TestFunction>
	void RunTest(TestFunction test, const string& test_name);

private:
	int fail_count = 0;
};





// void TestAll();

// void Test1();
// void Test2();
// void Test3();
// void Test4();
// void Test5();
// void Test6();
// void Test7();





template <typename Collection>
string Join(const Collection& c, const string& d) {
	stringstream ss;
	bool first = true;
	for (const auto& i : c) {
		if (!first) {
			ss << d << ' ';
		}
		first = false;
		ss << i;
	}
	return ss.str();
}

// template <typename First, typename Second>
// ostream& operator << (ostream& out, const pair<First, Second>& p) {
// 	return out << '(' << p.first << ", " << p.second << ')';
// }

template <typename T>
ostream& operator << (ostream& out, const vector<T>& v) {
	return out << '[' << Join(v, ", ") << ']';
}

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m) {
	return out << '{' << Join(m, ", ") << '}';
}

template <typename T>
ostream& operator << (ostream& out, const set<T>& s) {
	return out << '{' << Join(s, ", ") << '}';
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " --- hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

template<class TestFunction>
void TestRunner::RunTest(TestFunction test, const string& test_name) {
	try {
		test();
		cerr << test_name << " OK" << endl;
	} catch (exception& e) {
		++fail_count;
		cerr << test_name << " fail: " << e.what() << endl;
	} catch (...) {
		++fail_count;
		cerr << "Unknown exception caught" << endl;
	}
}
