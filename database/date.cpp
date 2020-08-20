#include "date.h"

#include <stdexcept>
#include <tuple>
#include <iomanip>

using namespace std;

Date::Date(
    const int& new_year,
    const int& new_month,
    const int& new_day
) {
    if (new_month < 1 || new_month > 12) {
        throw runtime_error("Month value is invalid: " + to_string(new_month));
    } else if (new_day < 1 || new_day > 31) {
        throw runtime_error("Day value is invalid: " + to_string(new_day));
    }

    Year = new_year;
    Month = new_month;
    Day = new_day;
}

int Date::GetYear() const {
    return Year;
}

int Date::GetMonth() const {
    return Month;
}

int Date::GetDay() const {
    return Day;
}



Date ParseDateFromString(const string &string_input) {
    istringstream string_stream(string_input);
    bool flag = true;

    int new_year(0);
    int new_month(0);
    int new_day(0);

    flag = flag && (string_stream >> new_year);
    flag = flag && (string_stream.peek() == '-');
    string_stream.ignore(1);

    flag = flag && (string_stream >> new_month);
    flag = flag && (string_stream.peek() == '-');
    string_stream.ignore(1);

    flag = flag && (string_stream >> new_day);
    flag = flag && (string_stream.eof());

    if (!flag) {
        throw runtime_error("Wrong date format: " + string_input);
    }

    return Date(new_year, new_month, new_day);
}

Date ParseDate(istream& is) {
    Date result(0, 0, 0);
    is >> result;
    return result;
}

istream& operator>>(istream& stream, Date& date) {
    string string_input;
    stream >> string_input;
    date = ParseDateFromString(string_input);
    return stream;
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0') << setw(4) << date.GetYear() << '-'
        << setfill('0') << setw(2) << date.GetMonth() << '-'
        << setfill('0') << setw(2) << date.GetDay();
    return stream;
}



bool operator<(const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) < make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator==(const Date &lhs, const Date &rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) == make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) != make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>(const Date &lhs, const Date &rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) > make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
