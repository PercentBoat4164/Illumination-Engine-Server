#pragma once

#include "../SharedResource.hpp"

// Template Class for Flag Shared Resource Type
// Defines API Features: getFlag, setFlag
template<typename T>
class SharedFlag : public SharedResource {
public:
    enum class m_opCodes {
        GetValue,
        SetValue
    };

    // Constructor with Common Resource Information and Initial Flag Value
    SharedFlag(T initialValue, int bundleID, int resourceID, std::map<m_opCodes, int> opCodePermissionMapping);

    // Gets the current value of the Flag
    T getFlagValue();

    //Sets the current value of the Flag
    void setFlagValue(T newflag);
private:
    T m_flagValue;
};