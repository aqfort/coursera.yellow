#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.buses.empty()) {
        os << "No stop";
    } else {
        for(const auto& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.bus.empty()) {
        os << "No bus";
    } else {
        bool first = true;
        for(const auto& stop : r.stops) {
            if(!first) {
                os << endl;
            }
            first = false;
            os << "Stop " << stop << ": ";
            if(r.stops_with_interchanges.count(stop) == 0) {
                os << "no interchange";
            } else {
                for(const auto& other_bus : r.stops_with_interchanges.at(stop)) {
                    os << other_bus << " ";
                }
            }
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if(r.buses_to_stops.empty()) {
        os << "No buses";
    } else {
        bool first = true;
        for(const auto& bus_item : r.buses_to_stops) {
            if(!first) {
                os << endl;
            }
            first = false;
            os << "Bus " << bus_item.first << ": ";
            for(const auto& stop : bus_item.second) {
                os << stop << " ";
            }
        }
    }
    return os;
}
