#include "database.h"

using namespace std;

void Database::Add(
    const Date& date,
    const string& event
) {
    auto check = No_Repeat_[date].size();
    No_Repeat_[date].emplace(event);

    if (No_Repeat_.at(date).size() > check) {
        Data_[date].emplace_back(event);
    }
}

void Database::Print(ostream& stream) const {
    for (const auto& item : Data_) {
        for (const auto& i : item.second) {
            stream << item.first << " " << i << endl;
        }
    }
}

pair<Date, string> Database::Last(const Date& date) const {
    auto bound = Data_.upper_bound(date);

    bound--;

    return make_pair(bound->first, bound->second.back());
}





ostream& operator<<(ostream& stream, const pair<Date, string>& pair) {
    stream << pair.first << " " << pair.second;
    return stream;
}

ostream& operator<<(ostream& stream, const pair<Date, vector<string>>& pair) {
    for (const auto& item : pair.second) {
        stream << pair.first << " " << item << endl;
    }
    return stream;
}

bool operator<(const pair<Date, string>& left, const pair<Date, string>& right) {
	return left.first < right.first;
}


bool operator==(const pair<Date, string>& left, const pair<Date, string>& right) {
	return left.first == right.first && right.second == left.second;
}
