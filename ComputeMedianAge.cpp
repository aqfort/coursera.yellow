#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

void PrintStats(vector<Person> persons);

bool All(const Person& person);
bool Female(const Person& person);
bool Male(const Person& person);
bool FemaleEmployed(const Person& person);
bool FemaleUnemployed(const Person& person);
bool MaleEmployed(const Person& person);
bool MaleUnemployed(const Person& person);

struct FunctionWithComment {
  bool (*foo)(const Person& person);
  string comment;
};

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

void PrintStats(vector<Person> persons) {
  vector<Person>::iterator bound;

  vector<FunctionWithComment> list = {
    {All, ""},
    {Female, " for females"},
    {Male , " for males"},
    {FemaleEmployed , " for employed females"},
    {FemaleUnemployed , " for unemployed females"},
    {MaleEmployed , " for employed males"},
    {MaleUnemployed , " for unemployed males"}
  };

  for (const auto& i : list) {
    bound = partition(persons.begin(), persons.end(), i.foo);
    cout << "Median age" << i.comment << " = " << ComputeMedianAge(persons.begin(), bound) << endl;
  }
}

bool All(const Person& person) {
  return true;
}
bool Female(const Person& person) {
  return person.gender == Gender::FEMALE;
}
bool Male(const Person& person) {
  return person.gender == Gender::MALE;
}
bool FemaleEmployed(const Person& person) {
  return (person.gender == Gender::FEMALE && person.is_employed == true);
}
bool FemaleUnemployed(const Person& person) {
  return (person.gender == Gender::FEMALE && person.is_employed == false);
}
bool MaleEmployed(const Person& person) {
  return (person.gender == Gender::MALE && person.is_employed == true);
}
bool MaleUnemployed(const Person& person) {
  return (person.gender == Gender::MALE && person.is_employed == false);
}
