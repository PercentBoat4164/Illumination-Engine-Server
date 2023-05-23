// Defines Methods for Interacting with a Simple Flag Resource

#pragma once

#include <string>
using namespace std;

// Defines a constant that can be used to declare all Flag Functions
// Makes Function Definitions Cleaner and More Readable
#define flagdef template <class T>

// Defines Constructor for Flag To Store an Initial Value and Pass Resource Name and BundleID to Shared Resource Class
flagdef Flag<T>::Flag(T init, string name, int bundleID) : SharedResource(name, bundleID){
    setFlag(init);
}

// Implements getFlag() API: Returns Current Flag Data
flagdef T Flag<T>::getFlag() {
    return data;
}

// Implements setFlag() API: Sets the Flag Value to the Data Specified
flagdef void Flag<T>::setFlag(T newflag) {
    data = newflag;
}