#pragma once

#include "date.h"

#include <unordered_set>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>



using namespace std;



class Database {
public:
	Database() = default;

	void Add(
		const Date& date,
		const string& event
	);

	void Print(ostream& stream) const;

	template <typename Predicate>
	int RemoveIf(const Predicate& predicate) {
		int res = 0;

		map<Date, vector<string>> New_Data_;
		map<Date, unordered_set<string>> New_No_Repeat_;

		for (auto& item : Data_) { //const doesn't work
			auto bound = stable_partition(
				item.second.begin(),
				item.second.end(),
				[predicate, item] (const auto& event) {
					return predicate(item.first, event);
				}
			);

			int temp_res = item.second.size();

			if (bound == item.second.end()) {
				res += temp_res;
			} else {
				New_Data_[item.first] = vector<string> (bound, item.second.end());
				New_No_Repeat_[item.first] = unordered_set<string> (bound, item.second.end());

				res += temp_res - New_Data_.at(item.first).size();
			}
		}

		Data_ = New_Data_;
		No_Repeat_ = New_No_Repeat_;

		return res;
	}

	template <typename Predicate>
	vector<pair<Date, string>> FindIf(const Predicate& predicate) const {
		vector<pair<Date, string>> res;
		map<Date, vector<string>> temp;

		for (const auto& item : Data_) {
			vector<string> temp_events;
			copy_if(
				item.second.begin(),
				item.second.end(),
				back_inserter(temp_events),
				[predicate, item] (const auto& event) {
					return predicate(item.first, event);
				}
			);

			if (temp_events.size() > 0) {
				temp[item.first] = temp_events;
			}
		}

		for (const auto& item : temp) {
			for (const auto& event : item.second) {
				res.emplace_back(make_pair(item.first, event));
			}
		}

		return res;
	}

	pair<Date, string> Last(const Date& date) const;

private:
	map<Date, vector<string>> Data_;
	map<Date, unordered_set<string>> No_Repeat_;
};

ostream& operator<<(ostream& stream, const pair<Date, string>& pair);
ostream& operator<<(ostream& stream, const pair<Date, vector<string>>& pair);

bool operator<(const pair<Date, string>& left, const pair<Date, string>& right);
bool operator==(const pair<Date, string>& left, const pair<Date, string>& right);
