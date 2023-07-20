#pragma once

#include "../SharedResource.hpp"

// Template Class for Map Shared Resource Type
// Defines API Features: Get, Restore, Insert, Update
// Defines Addition Function for getting State Number
template<typename K, typename V>
class SharedMap : public SharedResource {
public:
    enum class m_opCodes : int {GetValue = 0, SetValue = 1};
    static std::map<m_opCodes, int> m_defaultOpCodePermissionMapping {
            {m_opCodes::GetValue, 0},
            {m_opCodes::SetValue, 0}
    };

    // Constructs a Map Resource with a Name and Bundle ID
    explicit SharedMap(int bundleID, int resourceID, std::map<m_opCodes, int> *opCodePermissionMapping = nullptr);

    // Gets the value for a certain Key in the Map
    V getVal(K key);

    // Returns the Entire Map
    std::map<K,V> getFullMap();

    // Returns the Current State of the Map
    int getCurrentStateNumber();

    // Inserts a Key/Value Pair into the Map
    void insertPair(K key, V val);

    // Gets a Set of Map Updates that have happened since the map has been at a certain previous state
    std::map<K,V> updateMap(int lastUpdatedState);
private:
    int m_currentStateNumber;
    std::map<K,V> m_mapState;

    // Tracks the Old States in the format (statenum, next_state_update_key, next_state_update_val)
    std::list<std::tuple<int, K, V>> m_prevStateTracker;
};