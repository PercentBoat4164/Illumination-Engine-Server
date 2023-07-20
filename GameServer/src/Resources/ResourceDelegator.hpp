#pragma once

#include "SharedResource.hpp"
#include <list>
#include <map>
#include <random>

// Class for Manipulating and Accessing Flag Memory
// Also Indirectly Handles Permissions for Shared Resource Types
class ResourceDelegator {
public:
    // Constructor that Sets Up the Resource Bundle Store that the Game Server Uses
    ResourceDelegator();

    bool createNewBundle(int bundleType, int bundleID = -1);

    bool deleteBundle(int bundleID);

    SharedResource *getResource(int bundleID, int resID);

private:
    std::map<int, std::map<int, SharedResource*>*> *m_resourceBundles;

    std::mt19937 m_randomNumberGenerator;
    std::uniform_int_distribution<int> m_bundleIDGenerator;
};