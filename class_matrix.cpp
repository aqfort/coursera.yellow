#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//----- ----- ----- ----- ----- ----- ----- ----- ----- -----

class Matrix {
public:
    Matrix() {
        ROWS = 0;
        COLS = 0;
        BuildMatrix();
    }

    Matrix(const int &new_ROWS, const int &new_COLS) {
        AreSizeArgsNegative(new_ROWS, new_COLS);
        ROWS = new_ROWS;
        COLS = new_COLS;
        BuildMatrix();
    }

    int GetNumRows() const {
        return ROWS;
    }

    int GetNumColumns() const {
        return COLS;
    }

    void Reset(const int &new_ROWS, const int &new_COLS) {
        AreSizeArgsNegative(new_ROWS, new_COLS);
        ROWS = new_ROWS;
        COLS = new_COLS;
        BuildMatrix();
    }

    int At(const int &row, const int &col) const {
        AreSizeArgsNegative(row, col);
        AreSizeArgsOutOfRange(row, col);
        return DATA.at(row).at(col);
    }

    int &At(const int &row, const int &col) {
        AreSizeArgsNegative(row, col);
        AreSizeArgsOutOfRange(row, col);
        return DATA.at(row).at(col);
    };

    friend bool operator==(const Matrix &lhs, const Matrix &rhs);
    friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);

private:
    int ROWS;   //number of rows of matrix
    int COLS;   //number of columns of matrix
    vector<vector<int>> DATA;   //data of matrix

    void AreSizeArgsNegative(const int &row, const int &col) const {
        if (row < 0 || col < 0) {
            throw out_of_range("arguments are negative");
        }
    }

    void AreSizeArgsOutOfRange(const int &row, const int &col) const {
        if (row > ROWS || col > COLS) {
            throw out_of_range("arguments are out of range");
        }
    }

    void BuildMatrix() {
        DATA.clear();
        DATA.resize(ROWS);
        for (int row = 0; row < ROWS; row++) {
            DATA[row].resize(COLS);
        }
    }

    bool AreMatrixSizesEqual(const Matrix &matrix) const {
        return (ROWS == matrix.GetNumRows() && 
                COLS == matrix.GetNumColumns());
    }
};

istream &operator>>(istream &in, Matrix &matrix) {
    int new_ROWS(0), new_COLS(0);
    in >> new_ROWS >> new_COLS;
    matrix.Reset(new_ROWS, new_COLS);
    for (int row = 0; row < new_ROWS; row++) {
        for (int element = 0; element < new_COLS; element++) {
            in >> matrix.At(row, element);
        }
    }
    return in;
}

ostream &operator<<(ostream &out, const Matrix &matrix) {
    out << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;
    for (int row = 0; row < matrix.GetNumRows(); row++) {
        for (int element = 0; element < matrix.GetNumColumns(); element++) {
            out << matrix.At(row, element) << ' ';
        }
        if ((row + 1) < matrix.GetNumRows()) {
            out << endl;
        }
    }
    return out;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
    if (!lhs.AreMatrixSizesEqual(rhs)) {
        return false;
    }
    for (int row = 0; row < lhs.GetNumRows(); row++) {
        for (int element = 0; element < lhs.GetNumColumns(); element++) {
            if (lhs.At(row, element) != rhs.At(row, element)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    if (!lhs.AreMatrixSizesEqual(rhs)) {
        throw invalid_argument("different sizes");
    }
    Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
    for (int row = 0; row < lhs.GetNumRows(); row++) {
        for (int element = 0; element < lhs.GetNumColumns(); element++) {
            result.At(row, element) = lhs.At(row, element) + rhs.At(row, element);
        }
    }
    return result;
}

//----- ----- ----- ----- ----- ----- ----- ----- ----- -----

int main() {
    Matrix one, two;
    //two.Reset(3, -3);

    cin >> one;

    cin >> two;

    //if (one == two) {
    //    cout << "YES\n";
    //} else {
    //    cout << "NO\n";
    //}

    cout << one + two << endl;

    return 0;
}