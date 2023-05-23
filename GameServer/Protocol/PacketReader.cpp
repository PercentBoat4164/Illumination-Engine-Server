// conifer0us 5/11/23
// Defines a Set of Functions that Break Down Different Packet Types from The Socket, Turns them into Easily Readable
// structures, and passes the structure information onto Packet Handling Functions

#include <cstdlib>
#include "Protocol.h"

// Gets Packet Metadata from a Socket Buffer
static PacketMeta_P getPacketMetaData(char sockbuf[4096]) {
    auto metadata = (PacketMeta_P) malloc(sizeof(PacketMeta));

    id uid = *(id*) sockbuf;
    int restype = sockbuf[8];
    int mode = sockbuf[9];

    // Ensures User ID is not 0 (reserved for main server commands)
    if (uid != 0) {
        metadata->restype = restype;
        metadata->mode = mode;
        metadata->uid = uid;
    }
    else {
        free(metadata);
        metadata = nullptr;
    }

    return metadata;
}

// Parses A Generic Packet that the Socket Received
bool PacketReader::parsePacket(char sockbuf[4096]) {
    PacketMeta_P metadata = getPacketMetaData(sockbuf);
    FlagRead_P flagdata = nullptr;

    if (metadata== nullptr) {
        return false;
    }

    switch (metadata->restype) {
        // Passes Flag Data Along to Proper Read and Write Calls if Properly Received
        case FLAG:
            flagdata = (FlagRead*) malloc(sizeof(FlagRead));
            if (metadata->mode == READ) {
                flagdata->meta = metadata;
                readFlag(flagdata, sockbuf);
                return true;
            }
            free(flagdata);
            return false;
        default:
            return false;
    }
}

// Code that Runs When Flag Read Packet is Received From the Client
void PacketReader::readFlag(FlagRead_P flagdata, char sockbuf[4096]) {
    return;
}