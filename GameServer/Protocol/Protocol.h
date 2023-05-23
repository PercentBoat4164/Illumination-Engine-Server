// conifer0us 5/11
#pragma once

// Header for PacketReader that Defines Multiple Key Protocol Structs and Packet Parsing Functions

// Pointer Types for Convenience (Bless Prof. Stuart)
typedef struct PacketMeta* PacketMeta_P;
typedef struct FlagRead* FlagRead_P;

// Defines an Unsigned long long integer as an ID
typedef unsigned long long int id;

// Defines An Enum to Tell the Difference Between Resources of Different Types
enum ResTypes {
    FLAG,
};

// Define Valid Modes of Operation on Shared Resource Types
enum FlagMode {
    READ,
    WRITE,
};

// Defines a Packet Metadata Structure of information that can be expected from the server
// Contains a User ID for the person sending the packet and an int to determine type of packet
// Contains a integer to Represent the resource type
// User ID is inherited from the Main Server (or sent directly if desired)
struct PacketMeta {
    id uid;
    int restype;
    int mode;
};

// Flag Struct for Read Operations
// Contains a Pointer to newdata (expected to be the same type as the flag resource)
struct FlagRead {
    PacketMeta_P meta;
};

// Simple Static Class used to Parse Socket Data for Packet Information
// Will Pass Packet Data Along to Appropriate Functions when Received
class PacketReader {
public:
    // Returns true if Packet is Parsed Successfully
    // Returns false otherwise
    // Will Alter Buffer in Place to Specify Message to Send
    static bool parsePacket(char sockbuf[4096]);

private:
    // Called Upon Receiving a Flag Read Packet
    static void readFlag(FlagRead_P flagdata, char sockbuf[4096]);
};