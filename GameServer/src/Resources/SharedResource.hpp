#pragma once

# include <list>
# include <map>
# include <string>

typedef std::uint64_t id;

// Defines Simple Class for Handling Shared Resource Information and Packet Processing
class SharedResource {
public:
    enum class m_opCodes : int;

    explicit SharedResource(int bundleID, int resourceID, std::map<m_opCodes, int> *opCodePermissionMapping = nullptr);

    int getBundleID() const;
    int getResourceID() const;

    virtual bool userHasPermission(id userID, m_opCodes accessMode);
    virtual int getPermissionLevel(id userID);

    virtual void setPermissionLevel(id targetUserID, int newPermissionLevel);

    virtual void processPacket(m_opCodes accessMode, void* packetData, int packetOwnerSocket);

private:
    int m_bundleID;
    int m_resourceID;
    std::map<id, int> m_userPermissionMapping;

    std::map<m_opCodes, int> m_opCodePermissionMapping;
};