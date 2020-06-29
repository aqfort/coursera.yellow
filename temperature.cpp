#include <iostream>
#include <vector>

//The temperature values observed for N consecutive days are given.
//Find the numbers of days (in numbering from zero)
//with a temperature value above the arithmetic average for all N days.

int main() {
    uint32_t Quantity = 0;
    int32_t OneTemperature = 0;
    int64_t Average = 0;

    std::cin >> Quantity;

    std::vector<int32_t> Temperature;

    for (uint32_t item = 0;
         item < Quantity;
         item++) {
        std::cin >> OneTemperature;
        Average += OneTemperature;
        Temperature.emplace_back(OneTemperature);
    }

    //std::cout << "Sum of arguments: " << Average << std::endl;

    Average /= static_cast<int64_t>(Quantity);

    //std::cout << "The average: " << Average << std::endl;

    std::vector<uint32_t> Result;

    for (uint32_t item = 0;
         item < static_cast<uint32_t>(Temperature.size());
         item++) {
        if (Average < static_cast<int64_t>(Temperature.at(item))) {
            Result.emplace_back(item);
        }
    }

    std::cout << Result.size() << std::endl;

    for (const auto &item : Result) {
        std::cout << item << ' ';
    }

    std::cout << std::endl;

    return 0;
}