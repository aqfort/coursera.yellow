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

void TestAll();

void TestUsual();
void TestOneRoot();
void TestNoRoots();
void TestLinearEquation();
void TestConstant();





int GetDistinctRealRootCount(double a, double b, double c) {
    double D = 0;
    D = b * b - 4 * a * c;
    if (D > 0) {
        return 2;
    } else if (D == 0) {
        return 1;
    } else {
        return 0;
    }
} // Wrong realisation





int main() {
    TestAll();

    return 0;
}





void TestAll() {
    TestRunner runner;
    runner.RunTest(TestUsual, "TestUsual");
    runner.RunTest(TestOneRoot, "TestOneRoot");
    runner.RunTest(TestNoRoots, "TestNoRoots");
    runner.RunTest(TestLinearEquation, "TestLinearEquation");
    runner.RunTest(TestConstant, "TestConstant");
}

void TestUsual() {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(-10, 10);

    double a, b, c;
    int result;

    for (size_t i = 0; i < 100; i++) {
        a = distribution(generator);
        b = distribution(generator);
        c = distribution(generator);

        result = GetDistinctRealRootCount(a, b, c);

        Assert(result >= 0 && result <= 2, "Quadratic equation has only 0, 1 or 2 real roots.");
    }
    
}

void TestOneRoot() {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(-10, 10);

    double x, p, q;
    int result;

    for (size_t i = 0; i < 100; i++) {
        x = distribution(generator);
        p = -(x + x);
        q = x * x;

        result = GetDistinctRealRootCount(1, p, q);

        stringstream description;
        description << showpos << "x^2" << p << "x" << q << "= 0 has 1 real root.";

        AssertEqual(result, 1, description.str());
    }
    
}

void TestNoRoots() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0,
        "x^2+1 = 0 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0,
        "x^2+3x+4 = 0 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0,
        "x^2-2x+10 = 0 has 0 real roots.");
}

void TestLinearEquation() {
    AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1,
        "2x+1 = 0 has 1 real root.");
    AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1,
        "-x = 0 has 1 real root.");
    AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1,
        "120x - 10 = 0 has 1 real root.");
}

void TestConstant() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
        "c = 0, where c = 1 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
        "c = 0, where c = -10 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
        "c = 0, where c = 189238910 has 0 real roots.");
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
