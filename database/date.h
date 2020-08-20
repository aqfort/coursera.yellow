#pragma once

using namespace std;

class Date {
public:
    Date(
        const int& new_year,
        const int& new_month,
        const int& new_day);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

private:
    int Year;
    int Month;
    int Day;
};

istream& operator>>(istream& stream, Date& date);
ostream& operator<<(ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);

Date ParseDateFromString(const string &string_input);
Date ParseDate(istream& stream);
