#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(
        const string& name = "_%noname%_",
        const string& profession = "_%jobless%_"
    ) :
        Name(name),
        Profession(profession) {}

    virtual void Walk(
        const string& destination
    ) const {
        Act();
        cout << "walks to: " << destination << endl;
        DuringWalk();
    };

    // alternative way of realisation of VisitPlaces
    // it's more logical because VisitPlaces can be used
    // only for people, so it should be a method of Person class

    virtual void VisitPlaces(
        const vector<string>& places
    ) const {
        for (const auto& place : places) {
            Walk(place);
        }
    }

    virtual string GetName() const {
        return Name;
    }

    virtual string GetProfession() const {
        return Profession;
    }

protected:
    virtual void Act() const {
        cout << Profession << ": " << Name << " ";
    }

    virtual void DuringWalk() const {}

private:
    const string Name;
    const string Profession;
};





class Student : public Person {
public:
    Student(
        const string& name,
        const string& favouriteSong
    ) :
        Person(name, "Student"),
        FavouriteSong(favouriteSong) {}

    void Learn() const {
        Act();
        cout << "learns" << endl;
    }

    void SingSong() const {
        Act();
        cout << "sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;

    virtual void DuringWalk() const override {
        SingSong();
    }
};





class Teacher : public Person {
public:
    Teacher(
        const string& name,
        const string& subject
    ) :
        Person(name, "Teacher"),
        Subject(subject) {}

    void Teach() const {
        Act();
        cout << "teaches: " << Subject << endl;
    }

private:
    const string Subject;
};





class Policeman : public Person {
public:
    Policeman(
        const string& name
    ) :
        Person(name, "Policeman") {}

    void Check(
        const Person& person
    ) const {
        Act();
        cout << "checks " <<
            person.GetProfession() << ". "<<
            person.GetProfession() << "'s name is: " <<
            person.GetName() << endl;
    }
};





// there is VisitPlaces method above
// in Person class (more logical)

void VisitPlaces(
    const Person& person,
    const vector<string>& places
) {
    for (const auto& place : places) {
        person.Walk(place);
    }
}





int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    // Person noname;
    // noname.Walk("_%nowhere%_");

    //VisitPlaces(t, {"Moscow", "London"});
    t.VisitPlaces({"Moscow", "London"});

    p.Check(s);

    //VisitPlaces(s, {"Moscow", "London"});
    s.VisitPlaces({"Moscow", "London"});

    return 0;
}
