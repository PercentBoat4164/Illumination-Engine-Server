#pragma once

#include "SharedMap.hpp"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>

// Constant mapdef statement that is necessary to define all Map Functions
// Makes function definitions much cleaner and more readable
#define tdef template <typename K, typename V>

// Implements Map Constructor (Sets State Map to empty and state number to 0)
tdef SharedMap<K,V>::SharedMap(int bundleID, int resourceID, std::map<m_opCodes, int> *opCodePermissionMapping) :
    SharedResource(resourceID, bundleID, opCodePermissionMapping),
    m_prevStateTracker({}), m_mapState({}), m_currentStateNumber(0) {};

// Implements getVal API: Returns the Piece of Data that is attached to the specified Key in the Map
tdef V SharedMap<K,V>::getVal(K key) {
    return m_mapState[key];
}

// Implements getStateNum API: Returns the Current State Number that is Kept Track of by the Map
tdef int SharedMap<K,V>::getCurrentStateNumber() {
    return m_currentStateNumber;
}

tdef std::map<K,V> SharedMap<K,V>::getFullMap() {
    return m_mapState;
}

tdef void SharedMap<K,V>::insertPair(K key, V val) {
    // Use Lambda Expression to Remove Element From Previous State List if Previous element Contains the Same Key
    // (Do Not store multiple update clauses for the same value)
    m_prevStateTracker.remove_if([&] (std::tuple<int, K, V> elem) -> bool {
        return get<1>(elem) == key;
    });

    // Adds Current State, Key and Value Pair to the End of the State Tracker
    // Also Increments State Number (Postfix)
    m_prevStateTracker.push_back(make_tuple(m_currentStateNumber++, key, val));

    m_mapState[key] = val;
}

// Implements update API: Returns a map of keys and values that have been changed since last access
tdef std::map<K,V> SharedMap<K,V>::updateMap(int oldstate) {
    if (m_prevStateTracker.empty()) return {};

    std::map<K,V> updatedInfo;

    auto marker = m_prevStateTracker.rbegin();

    // Iterates Through State List Starting at the End (ending at the start)
    do {
        // If the State is Equal to or Newer than the Current State, add Key Value Pair to the Updated Hash Table
        if (get<0>(*marker) >= oldstate) updatedInfo[get<1>(*marker)] = get<2>(*marker);

        marker++;
    } while (marker!=m_prevStateTracker.rend());

    return updatedInfo;
}