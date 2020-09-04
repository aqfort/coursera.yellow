#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;





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





bool IsPalindrom(const string &word) {
    string word_reversed = word;
    reverse(word_reversed.begin(), word_reversed.end());
    return word_reversed == word;
}

// vector<string> PalindromFilter(vector<string> words, int minLength) {
//     vector<string> result;
//     for(auto temp : words) {
//         if(IsPalindrom(temp) && temp.size() >= minLength)
//             result.push_back(temp);
//     }
//     return result;
// }





void TestAll();

void Test1();
void Test2();
void Test3();





int main() {
    TestAll();

    // vector<string> words = {"abacaba", "aba", "weew", "bro", "code"};
    // words = PalindromFilter(words, 4);
    // for(auto word : words)
    //     cout << word << ' ';

    return 0;
}





void TestAll() {
    TestRunner runner;
    runner.RunTest(Test1, "Test1");
    runner.RunTest(Test2, "Test2");
    runner.RunTest(Test3, "Test3");
}

void Test1() {
    Assert(IsPalindrom(""), "empty");
    Assert(IsPalindrom("!"), "!");
    Assert(IsPalindrom("h"), "h");
    Assert(IsPalindrom("T"), "T");
    Assert(IsPalindrom(" "), " ");
    Assert(IsPalindrom("%"), "%");
}

void Test2() {
    Assert(IsPalindrom("SOS"), "SOS");
    Assert(IsPalindrom("madam"), "madam");
    Assert(IsPalindrom("level"), "level");
    Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
    Assert(IsPalindrom("kek kek"), "kek kek");
    Assert(IsPalindrom("k o# l #o k"), "k o# l #o k");
    Assert(IsPalindrom("!@#$%^%$#@!"), "!@#$%^%$#@!");
    Assert(IsPalindrom("ASDFGHjkllkjHGFDSA"), "ASDFGHjkllkjHGFDSA");
    Assert(IsPalindrom(""), "");
    Assert(IsPalindrom(""), "");
    Assert(IsPalindrom(""), "");
}

void Test3() {
    Assert(!IsPalindrom("cat"), "cat");
    Assert(!IsPalindrom("kekl"), "kekl");
    Assert(!IsPalindrom("olol"), "olol");
    Assert(!IsPalindrom("*9"), "*9");
    Assert(!IsPalindrom("+= as"), "+= as");
    Assert(!IsPalindrom("kek "), "kek ");
    Assert(!IsPalindrom(" kek"), " kek");
    Assert(!IsPalindrom("assSOSss"), "assSOSss");
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
