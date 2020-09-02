#include "test_runner.h"



void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}



TestRunner::TestRunner() {
	fail_count = 0;
}



TestRunner::~TestRunner() {
	if (fail_count > 0) {
		cerr << fail_count << " unit tests failed" << endl;
		exit(1);
	}
}

// void TestAll() {
// 	TestRunner runner;
// 	runner.RunTest(Test1, "Test1");
// }
