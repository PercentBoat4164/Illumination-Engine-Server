// Defines Methods for a Simple Flag Shared Resource
#pragma once

#include "../SharedResource.hpp"
#include "SharedFlag.hpp"

// Defines Constructor for Flag To Store an Initial Value and Pass Resource Name and BundleID to Shared Resource Class
template<typename T> SharedFlag<T>::SharedFlag(T initialValue, int bundleID, int resourceID,
                               std::map<m_opCodes, int> opCodePermissionMapping):
                               SharedResource(bundleID, resourceID, opCodePermissionMapping){
    setFlag(initialValue);
}

// Implements getFlag() API: Returns Current Flag Data
template<typename T> T SharedFlag<T>::getFlagValue() {
    return m_flagValue;
}

// Implements setFlag() API: Sets the Flag Value to the Data Specified
template<typename T> void SharedFlag<T>::setFlagValue(T newflag) {
    m_flagValue = newflag;
}