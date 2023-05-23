// Lays out Definitions for Resource Types (These Resource Types will be wrapped by permission libraries and other methods
// to form Shared Resources, which can be operated on by a network call

#pragma once

# include <string>
# include <map>
# include <list>

using namespace std;

// Defines Simple Class for Handling Resource Information (Resource Name and Bundle ID)
// All Resoucre Types (Flag, Map, etc.) inherit from this
class SharedResource {
public:
    explicit SharedResource(string resName, int bundleID = 0);
    int getBundleID() const;
    string getResName() const;
private:
    int bundleid;
    string resname;
};

// Template Class for Flag Shared Resource Type
// Defines API Features: getFlag, setFlag
template<typename T>
class Flag : public SharedResource {
public:
    // Constructor with Common Resource Information and Initial Flag Value
    Flag(T init, string resname ,int bundleID = 0);

    // Gets the current value of the Flag
    T getFlag();

    //Sets the current value of the Flag
    void setFlag(T newflag);
protected:
    T data;
};

// Template Class for Map Shared Resource Type
// Defines API Features: Get, Restore, Insert, Update
// Defines Addition Function for getting State Number
template<typename K, typename V>
class Map : public SharedResource {
public:
    // Constructs a Map Resource with a Name and Bundle ID
    Map(string resname, int bundleID);

    // Gets the value for a certain Key in the Map
    V getVal(K key);

    // Returns the Entire Map
    map<K,V> restore();

    // Returns the Current State Number of the Map
    int currentState();

    // Inserts a Key/Value Pair into the Map
    void insert(K key, V val);

    // Gets a Set of Map Updates that have happened since the map has been at a certain previous state
    map<K,V> update(int oldstate);

    // Prints the Current State of the Map (Alonside an update from the specified state)
    void printmap(int prevstate = 0);

private:
    int currentstate;
    map<K,V> state;

    // Tracks the Old States in the format (statenum, next_state_update_key, next_state_update_val)
    list<tuple<int, K, V>> statetracker;
};

// Include Template Class Member Definitions Inline to avoid Linking Errors
// Flag inline function definitions
#include "Flag.inl"

// Map inline function definitions
#include "Map.inl"