#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

#define PI 3.14

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
    Triangle(const double& a, const double& b, const double& c) : _a(a), _b(b), _c(c) {}

    virtual string Name() const override {
        return _name;
    }

    virtual double Perimeter() const override {
        return _a + _b + _c;
    }

    virtual double Area() const override {
        double p = Perimeter() / 2.0;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }

private:
    const string _name = "TRIANGLE";
    const double _a, _b, _c;
};

class Rect : public Figure {
public:
    Rect(const double& a, const double& b) : _a(a), _b(b) {}

    virtual string Name() const override {
        return _name;
    }

    virtual double Perimeter() const override {
        return (_a + _b) * 2;
    }

    virtual double Area() const override {
        return _a * _b;
    }

private:
    const string _name = "RECT";
    const double _a, _b;
};

class Circle : public Figure {
public:
    Circle(const double& r) : _r(r) {}

    virtual string Name() const override {
        return _name;
    }

    virtual double Perimeter() const override {
        return 2.0 * PI * _r;
    }

    virtual double Area() const override {
        return PI * _r * _r;
    }

private:
    const string _name = "CIRCLE";
    const double _r;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string name;
    is >> name;
    if (name == "TRIANGLE") {
        double a, b, c;
        is >> a >> b >> c;
        Triangle triangle(a, b, c);
        return make_shared<Triangle>(triangle);
    } else if (name == "RECT") {
        double a, b;
        is >> a >> b;
        Rect rect(a, b);
        return make_shared<Rect>(rect);
    } else if (name == "CIRCLE") {
        double r;
        is >> r;
        Circle circle(r);
        return make_shared<Circle>(circle);
    }
    throw invalid_argument("figurename");
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
