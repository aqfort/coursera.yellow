#include "test.h"
#include "phone_number.h"

using namespace std;

void TestAll() {
    TestRunner runner;
    runner.RunTest(Test1, "Test1");
    runner.RunTest(Test2, "Test2");
    runner.RunTest(Test3, "Test3");
    runner.RunTest(Test4, "Test4");
    // runner.RunTest(Test5, "Test5");
    // runner.RunTest(Test6, "Test6");
    runner.RunTest(Test7, "Test7");
}

void Test1() {
    PhoneNumber number("+7-495-111-22-33");
    AssertEqual(number.GetCountryCode(), "7", "country code");
    AssertEqual(number.GetCityCode(), "495", "city code");
    AssertEqual(number.GetLocalNumber(), "111-22-33", "local number");
    AssertEqual(number.GetInternationalNumber(), "+7-495-111-22-33", "international number");
}

void Test2() {
    PhoneNumber number("+7-495-1112233");
    AssertEqual(number.GetCountryCode(), "7", "country code");
    AssertEqual(number.GetCityCode(), "495", "city code");
    AssertEqual(number.GetLocalNumber(), "1112233", "local number");
    AssertEqual(number.GetInternationalNumber(), "+7-495-1112233", "international number");
}

void Test3() {
    PhoneNumber number("+323-22-460002");
    AssertEqual(number.GetCountryCode(), "323", "country code");
    AssertEqual(number.GetCityCode(), "22", "city code");
    AssertEqual(number.GetLocalNumber(), "460002", "local number");
    AssertEqual(number.GetInternationalNumber(), "+323-22-460002", "international number");
}

void Test4() {
    PhoneNumber number("+1-2-coursera-cpp");
    AssertEqual(number.GetCountryCode(), "1", "country code");
    AssertEqual(number.GetCityCode(), "2", "city code");
    AssertEqual(number.GetLocalNumber(), "coursera-cpp", "local number");
    AssertEqual(number.GetInternationalNumber(), "+1-2-coursera-cpp", "international number");
}

void Test5() {
    PhoneNumber number("1-2-333");
}

void Test6() {
    PhoneNumber number("+7-1233");
}

void Test7() {
    
}





void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

TestRunner::~TestRunner() {
    if (fail_count > 0) {
        cerr << fail_count << " unit tests failed" << endl;
        exit(1);
    }
}
