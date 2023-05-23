#include "Resources.h"
#include <string>

// Generic Class For a Resource that Stores a Resource Name and Bundle ID
SharedResource::SharedResource(string resName, int bundleID) {
    bundleid = bundleID;
    resname = std::move(resName);
}

string SharedResource::getResName() const{
    return resname;
}

int SharedResource::getBundleID() const {
    return bundleid;
}