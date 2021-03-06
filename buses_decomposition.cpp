#include <unordered_map>
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
    string operation_code;
    is >> operation_code;

    if(operation_code == "NEW_BUS") {

        q.type = QueryType::NewBus;
        int stop_count;
        is >> q.bus >> stop_count;
        q.stops.resize(stop_count);
        for(auto& stop : q.stops) {
            is >> stop;
        }

    } else if(operation_code == "BUSES_FOR_STOP") {

        q.type = QueryType::BusesForStop;
        is >> q.stop;

    } else if(operation_code == "STOPS_FOR_BUS") {

        q.type = QueryType::StopsForBus;
        is >> q.bus;

    } else if(operation_code == "ALL_BUSES") {

        q.type = QueryType::AllBuses;

    } else {

        throw runtime_error("QueryType");
        
    }

    return is;
}

struct BusesForStopResponse {
    // РќР°РїРѕР»РЅРёС‚Рµ РїРѕР»СЏРјРё СЌС‚Сѓ СЃС‚СЂСѓРєС‚СѓСЂСѓ
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
    if(r.buses.empty()) {
        os << "No stop";
    } else {
        for(const auto& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    // РќР°РїРѕР»РЅРёС‚Рµ РїРѕР»СЏРјРё СЌС‚Сѓ СЃС‚СЂСѓРєС‚СѓСЂСѓ
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_with_interchanges;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
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

struct AllBusesResponse {
    // РќР°РїРѕР»РЅРёС‚Рµ РїРѕР»СЏРјРё СЌС‚Сѓ СЃС‚СЂСѓРєС‚СѓСЂСѓ
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
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

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
        buses_to_stops[bus] = stops;
        for(const auto& stop : stops) {
            stops_to_buses[stop].emplace_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
        BusesForStopResponse result;
        result.buses.clear();
        if(stops_to_buses.count(stop) != 0) {
            result.buses = stops_to_buses.at(stop);
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
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

    AllBusesResponse GetAllBuses() const {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
        AllBusesResponse result;
        result.buses_to_stops.clear();
        if(!buses_to_stops.empty()) {
            result.buses_to_stops = buses_to_stops;
        }
        return result;
    }

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};

// РќРµ РјРµРЅСЏСЏ С‚РµР»Р° С„СѓРЅРєС†РёРё main, СЂРµР°Р»РёР·СѓР№С‚Рµ С„СѓРЅРєС†РёРё Рё РєР»Р°СЃСЃС‹ РІС‹С€Рµ

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}