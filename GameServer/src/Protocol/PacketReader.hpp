#pragma once

// Includes A Resource Handler that the Protocol Handler will Use to Create and Access Resources in Memory
#include "ResourceDelegator.hpp"

typedef std::uint64_t id;

// Simple Static Class used to Parse Socket Data for Packet Information
// Will Pass Packet Data Along to Appropriate Functions when Received
class PacketReader {
public:
    // Creates the Packet Reader with Interface to Access Local Interfaces
    explicit PacketReader(ResourceDelegator& res);

    // Returns true if Packet is Parsed Successfully
    // Returns false otherwise
    // Will Pass Information Through the Chain until Response is Sent to given fd
    void parsePacket(char sockbuf[4096], int respfd);
private:
    ResourceDelegator res;
};