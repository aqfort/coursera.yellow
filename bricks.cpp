#include <iostream>
#include <limits>

using namespace std;

int main() { //calculate the weight of all bricks with the same density
    uint32_t N(0);
    uint16_t R(0); //why uint8_t doesn't work properly??? (even if R \in [0; 100])
    uint16_t W(0), H(0), D(0);
    uint64_t Result(0);

    //(u)int8_t seems to be converted to (unsigned) char
    //cout << static_cast<int>(numeric_limits<int8_t>::max()) << endl;

    cin >> N >> R;

    while (N > 0) {
        cin >> W >> H >> D;
        Result += static_cast<uint64_t>(W) *
                  static_cast<uint64_t>(H) *
                  static_cast<uint64_t>(D) *
                  static_cast<uint64_t>(R);
        N--;
        //cout << "W = " << static_cast<uint64_t>(W) << ' '
        //     << "H = " << static_cast<uint64_t>(H) << ' '
        //     << "D = " << static_cast<uint64_t>(D) << ' '
        //     << "R = " << static_cast<uint64_t>(R) << endl;
        //cout << "loop: " << N << endl;
    }

    cout << Result << endl;

    return 0;
}