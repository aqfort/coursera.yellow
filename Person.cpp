#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <random>

using namespace std;





template <typename First, typename Second>
ostream& operator << (ostream& out, const pair<First, Second>& p);

template <typename T>
ostream& operator << (ostream& out, const vector<T>& v);

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m);

template <typename Collection>
string Join(const Collection& c, char d);





template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint);

void Assert(bool b, const string& hint);

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name);

    ~TestRunner();

private:
    int fail_count = 0;
};





class Person {
public:
    void ChangeFirstName(const int& year, const string &first_name) {
        first_names[year] = first_name;
    }

    void ChangeLastName(const int& year, const string &last_name) {
        last_names[year] = last_name;
    }

    string GetFullName(const int& year) {
        if (first_names.empty() && last_names.empty())
            return "ERROR";

        pair<string, string> result = GetDataByYear(year);

        if (result.first.empty() && result.second.empty())
            return "Incognito";
        if (!result.first.empty() && !result.second.empty())
            return result.first + ' ' + result.second;
        if (!result.first.empty())
            return result.first + " with unknown last name";
        return result.second + " with unknown first name";
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;

    pair<string, string> GetDataByYear(const int& year) {
        auto it_1 = first_names.upper_bound(year);
        auto it_2 = last_names.upper_bound(year);
        string first_name, last_name;
        if (it_1 != first_names.begin()) {
            first_name = prev(it_1)->second;
        }
        if (it_2 != last_names.begin()) {
            last_name = prev(it_2)->second;
        }
        return make_pair(first_name, last_name);
    }
};





void TestAll();

void Test1();
void Test2();
void Test3();





int main() {
    TestAll();

    return 0;
}





void TestAll() {
    TestRunner runner;
    runner.RunTest(Test1, "Test1");
    runner.RunTest(Test2, "Test2");
    runner.RunTest(Test3, "Test3");
}

void Test1() {
    Person person;
    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeFirstName(1967, "Polina");

    AssertEqual(person.GetFullName(1964), "Incognito", "1964");
    AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name", "1966");
    AssertEqual(person.GetFullName(1990), "Polina Sergeeva", "1990");
}

void Test2() {
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    AssertEqual(person.GetFullName(1900), "Incognito", "1900");
    AssertEqual(person.GetFullName(1965), "Polina with unknown last name", "1965");
    AssertEqual(person.GetFullName(1990), "Polina Sergeeva", "1990");
}

void Test3() {
    Person person;
    person.ChangeLastName(1967, "Sergeeva");
    person.ChangeFirstName(1965, "Polina");

    person.ChangeFirstName(1970, "Appolinaria");

    AssertEqual(person.GetFullName(1969), "Polina Sergeeva", "1969 - change name");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva", "1970 - change name");

    person.ChangeLastName(1968, "Volkova");

    AssertEqual(person.GetFullName(1969), "Polina Volkova", "1969 - change surname");
    AssertEqual(person.GetFullName(1970), "Appolinaria Volkova", "1970 - change surname");
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

template <typename Collection>
string Join(const Collection& c, char d) {
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

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string& test_name) {
    try {
        func();
        cerr << test_name << " OK" << endl;
    } catch (exception& e) {
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
        ++fail_count;
        cerr << "Unknown exception caught" << endl;
    }
}

TestRunner::~TestRunner() {
    if (fail_count > 0) {
        cerr << fail_count << " unit tests failed" << endl;
        exit(1);
    }
}
