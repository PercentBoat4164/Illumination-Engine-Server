#include "SharedResource.hpp"

// Sets resource and bundle ID from arguments, if provided permission mapping is empty, the mapping is set to the
// default for that particular shared resource
SharedResource::SharedResource(int bundleID, int resourceID, std::map<m_opCodes, int> *opCodePermissionMapping) :
    m_resourceID(resourceID), m_bundleID(bundleID), m_opCodePermissionMapping(*opCodePermissionMapping) {}

int SharedResource::getResourceID() const {
    return m_resourceID;
}

int SharedResource::getBundleID() const {
    return m_bundleID;
}

bool SharedResource::userHasPermission(id userID, m_opCodes accessMode) {
    if (!m_opCodePermissionMapping.contains(accessMode)) {
        return true;
    }

    int requiredpermission = m_opCodePermissionMapping[accessMode];

    return this->getPermissionLevel(userID) >= requiredpermission;
}

int SharedResource::getPermissionLevel(id userID) {
    if (!m_userPermissionMapping.contains(userID)) {
        return 0;
    }
    return m_userPermissionMapping[userID];
}

void SharedResource::setPermissionLevel(id targetUserID, int newPermissionLevel) {
    m_userPermissionMapping[targetUserID] = newPermissionLevel;
}

void SharedResource::processPacket(SharedResource::m_opCodes accessMode, void *packetData, int packetOwnerSocket) {};