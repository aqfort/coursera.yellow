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
    return is;
}

struct BusesForStopResponse {
    // РќР°РїРѕР»РЅРёС‚Рµ РїРѕР»СЏРјРё СЌС‚Сѓ СЃС‚СЂСѓРєС‚СѓСЂСѓ
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
    return os;
}

struct StopsForBusResponse {
    // РќР°РїРѕР»РЅРёС‚Рµ РїРѕР»СЏРјРё СЌС‚Сѓ СЃС‚СЂСѓРєС‚СѓСЂСѓ
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
    return os;
}

struct AllBusesResponse {
    // РќР°РїРѕР»РЅРёС‚Рµ РїРѕР»СЏРјРё СЌС‚Сѓ СЃС‚СЂСѓРєС‚СѓСЂСѓ
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
    }

    AllBusesResponse GetAllBuses() const {
        // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РјРµС‚РѕРґ
    }
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