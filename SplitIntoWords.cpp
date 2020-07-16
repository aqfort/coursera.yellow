#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s);

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
           cout << "/";
        }
        cout << *it;
    }
    cout << endl;
    
    return 0;
}

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    string temp;

    auto begin = s.begin();
    auto end = s.begin();

    do {
        end = find_if(begin, s.end(), [] (const char& symbol) {return symbol == ' ';});

        for (auto i = begin; i < end; i++) {
            temp += *i;
        }

        result.emplace_back(temp);
        temp.clear();

        begin = end;
        begin++;

    } while (end != s.end());
    

    return result;
}
