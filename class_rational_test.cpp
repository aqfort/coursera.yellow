//template
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <map>

using namespace std;





//gcd: only positive numbers
int gcd(int a, int b) {
    while (true) {
        a = a % b;
        if (a == 0) {
            if (b < 0)
                b *= -1;
            return b;
        }
        b = b % a;
        if (b == 0) {
            if (a < 0)
                a *= -1;
            return a;
        }
    }
}

//rational numbers class
class Rational {
public:
    //default constructor
    Rational() {
        NUMER = 0;
        DENOM = 1;
    }

    //constructor
    Rational(const int &numerator, const int &denominator) {
        const int temp = gcd(numerator, denominator);
        NUMER = numerator / temp;
        DENOM = denominator / temp;
        if (DENOM < 0) {
            NUMER = -NUMER;
            DENOM = -DENOM;
        }
    }

    //to identify numerator
    int Numerator() const {
        return NUMER;
    }

    //to identify denominator
    int Denominator() const {
        return DENOM;
    }

    //additional part, not sure that it works
    //assignment operator
    //also '=' doesn't work outside class even with friend prefix
    Rational &operator=(const Rational &number) {
        if (this == &number) {
            return *this;
        }
        NUMER = number.Numerator();
        DENOM = number.Denominator();
        return *this; //this -- pointer to current object
    }

    friend istream &operator>>(istream &in, Rational &temp);

private:
    int NUMER;
    int DENOM;
};

ostream &operator<<(ostream &out, const Rational &number) {
    out << number.Numerator() << '/' << number.Denominator();
    return out;
}

istream &operator>>(istream &in, Rational &temp) {
    int numer(0), denom(1);
    char symbol;
    in >> numer >> symbol >> denom;
    if (in && symbol == '/') {
        temp = Rational(numer, denom);
    }
    return in;
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()};
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

bool operator==(const Rational &lhs, const Rational &rhs) {
    return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}

bool operator<(const Rational &lhs, const Rational &rhs) {
    return (lhs - rhs).Numerator() < 0;
}





//
//unit tests
//





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

void Test1();
void Test2();
void Test3();
void Test4();
void Test5();





int main() {
    TestAll();

    return 0;
}





void TestAll() {
    TestRunner runner;
    runner.RunTest(Test1, "Test1");
    runner.RunTest(Test2, "Test2");
    runner.RunTest(Test3, "Test3");
    runner.RunTest(Test4, "Test4");
    runner.RunTest(Test5, "Test5");
}

void Test1() {
    {
        const Rational r(3, 10);
        Assert(r.Numerator() == 3 && r.Denominator() == 10, "Rational(3, 10) != 3/10");
    }

    {
        const Rational r(8, 12);
        Assert(r.Numerator() == 2 && r.Denominator() == 3, "Rational(8, 12) != 2/3");
    }

    {
        const Rational r(-4, 6);
        Assert(r.Numerator() == -2 && r.Denominator() == 3, "Rational(-4, 6) != -2/3");
    }

    {
        const Rational r(4, -6);
        Assert(r.Numerator() == -2 && r.Denominator() == 3, "Rational(4, -6) != -2/3");
    }

    {
        const Rational r(0, 15);
        Assert(r.Numerator() == 0 && r.Denominator() == 1, "Rational(0, 15) != 0/1");
    }

    {
        const Rational defaultConstructed;
        Assert(defaultConstructed.Numerator() == 0 && defaultConstructed.Denominator() == 1, "Rational() != 0/1");
    }
}

void Test2() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        Assert(equal, "4/6 != 2/3");
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        Assert(equal, "2/3 + 4/3 != 2");
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        Assert(equal, "5/7 - 2/9 != 31/63");
    }
}

void Test3() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        Assert(equal, "2/3 * 4/3 != 8/9");
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        Assert(equal, "5/4 / 15/8 != 2/3");
    }
}

void Test4() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        AssertEqual(output.str(), "-3/4", "Rational(-6, 8) should be written as \"-3/4\"");
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        
        stringstream description;
        description << "5/7 is incorrectly read as " << r;

        Assert(equal, description.str());
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);

        stringstream description;
        description << "Multiple values are read incorrectly: " << r1 << " " << r2;

        Assert(correct, description.str());

        description.clear();

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);

        description << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2;

        Assert(correct, description.str());
    }
}

void Test5() {
    {
        const set<Rational> rs = {{1, 2},
                                  {1, 25},
                                  {3, 4},
                                  {3, 4},
                                  {1, 2}};

        AssertEqual(rs.size(), 3, "Wrong amount of items in the set");

        vector<Rational> v;
        v.reserve(rs.size());
        for (auto x : rs) {
            v.push_back(x);
        }

        AssertEqual(v, vector<Rational>{{1, 25}, {1, 2}, {3, 4}}, "Rationals comparison works incorrectly");
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        AssertEqual(count.size(), 2, "Wrong amount of items in the map");
    }
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
