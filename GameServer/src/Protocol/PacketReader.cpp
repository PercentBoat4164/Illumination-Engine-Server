// Defines a Set of Functions that Break Down Different Packet Types from The Socket, Turns them into Easily Readable
// structures, and passes the structure information onto Packet Handling Functions

#include "PacketORM/Base.pb.h"
#include "PacketReader.hpp"
#include "ResourceDelegator.hpp"

// Sets Up PacketReader with the ResHandler used by gameserver.cpp
PacketReader::PacketReader(ResourceDelegator& res) {
    this->res = res;
}

// Parses A Generic Packet that the Socket Received
void PacketReader::parsePacket(char sockbuf[4096], int respfd) {

}