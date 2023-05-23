#pragma once

#include <map>
#include <string>
#include <list>
#include <tuple>
#include <iostream>

// Constant mapdef statement that is necessary to define all Map Functions
// Makes function definitions much cleaner and more readable
#define mapdef template <typename K, typename V>

// Implements Map Constructor (Sets State Map to empty and state number to 0)
mapdef Map<K,V>::Map(string resname, int bundleID) : SharedResource(resname, bundleID) {
    currentstate = 0;
    state = {};
    statetracker = {};
};

// Implements getVal API: Returns the Piece of Data that is attached to the specified Key in the Map
mapdef V Map<K,V>::getVal(K key) {
    return state[key];
}

// Implements getStateNum API: Returns the Current State Number that is Kept Track of by the Map
mapdef int Map<K,V>::currentState() {
    return currentstate;
}

mapdef std::map<K,V> Map<K,V>::restore() {
    return state;
}

mapdef void Map<K,V>::insert(K key, V val) {
    // Use Lambda Expression to Remove Element From Previous State List if Previous element Contains the Same Key
    // (Do Not store multiple update clauses for the same value)
    statetracker.remove_if([&] (tuple<int, K, V> elem) -> bool {
        return get<1>(elem) == key;
    });

    // Adds Current State, Key and Value Pair to the End of the State Tracker
    // Also Increments State Number (Postfix)
    statetracker.push_back(make_tuple(currentstate++, key, val));

    state[key] = val;
}

// Implements update API: Returns a map of keys and values that have been changed since last access
mapdef std::map<K,V> Map<K,V>::update(int oldstate) {
    if (statetracker.empty()) return {};

    map<K,V> updatedInfo;

    auto marker = statetracker.rbegin();

    // Iterates Through State List Starting at the End (ending at the start)
    do {
        // If the State is Equal to or Newer than the Current State, add Key Value Pair to the Updated Hash Table
        if (get<0>(*marker) >= oldstate) updatedInfo[get<1>(*marker)] = get<2>(*marker);

        marker++;
    } while (marker!=statetracker.rend());

    return updatedInfo;
}

// Helper Method for Printing Out Map State (Only works on Str -> int maps for testing purposes)
mapdef void Map<K,V>::printmap(int prevstate) {
    for (auto& t : state)
        std::cout << string(t.first) << ": "
                  << to_string(t.second) << "\n";

    std::cout << "\n";

    for (tuple<int, K,V> t : statetracker) {
        std::cout << to_string(get<0>(t)) << ": " << string(get<1>(t)) << ", " << to_string(get<2>(t)) << "\n";
    }

    std::cout << "\n";

    for (auto& t : update(prevstate))
        std::cout << string(t.first) << ": " << to_string(t.second) << "\n";
};