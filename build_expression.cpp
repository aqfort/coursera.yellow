#include <iostream>
#include <deque>

using namespace std;

void Operator(
    deque<string>& result,
    const string& symbol,
    const string& ex_symbol,
    const int& x);

void Brackets(deque<string>& result);

void Print(deque<string>& result);

int main() {
    int x, N;
    string symbol, ex_symbol = "*";
    deque<string> result;

    cin >> x >> N;
    result.emplace_back(to_string(x));

    for (int i = 0; i < N; i++) {
        cin >> symbol >> x;
        Operator(result, symbol, ex_symbol, x);
        ex_symbol = symbol;
    }

    Print(result);

    cout << endl;

    return 0;
}

void Operator(
    deque<string>& result,
    const string& symbol,
    const string& ex_symbol,
    const int& x) {
    bool need_brackets = false;
    if (ex_symbol == "+" || ex_symbol == "-") {
        if (symbol == "*" || symbol == "/") {
            need_brackets = true;
        }
    }

    if (need_brackets) {
        Brackets(result);
    }

    result.emplace_back(" ");
    result.emplace_back(symbol);
    result.emplace_back(" ");
    result.emplace_back(to_string(x));
}

void Brackets(deque<string>& result) {
    result.emplace_front("(");
    result.emplace_back(")");
}

void Print(deque<string>& result) {
    while (!result.empty()) {
        cout << result.front();
        result.pop_front();
    }
}
