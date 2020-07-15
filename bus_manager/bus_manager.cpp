#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for(const auto& stop : stops) {
        stops_to_buses[stop].emplace_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse result;
    result.buses.clear();
    if(stops_to_buses.count(stop) != 0) {
        result.buses = stops_to_buses.at(stop);
    }
    return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse result;
    result.bus.clear();
    result.stops.clear();
    result.stops_with_interchanges.clear();
    if(buses_to_stops.count(bus) != 0) {
        result.bus = bus;
        result.stops = buses_to_stops.at(bus);
        for(const auto& stop : buses_to_stops.at(bus)) {
            if(stops_to_buses.at(stop).size() != 1) {
                for(const auto& other_bus : stops_to_buses.at(stop)) {
                    if(bus != other_bus) {
                        result.stops_with_interchanges[stop].emplace_back(other_bus);
                    }
                }
            }
        }
    }
    return result;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse result;
    result.buses_to_stops.clear();
    if(!buses_to_stops.empty()) {
        result.buses_to_stops = buses_to_stops;
    }
    return result;
}
