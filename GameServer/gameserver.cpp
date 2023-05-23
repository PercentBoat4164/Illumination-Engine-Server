#include "Resources.h"
#include "Protocol.h"

#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

// Global Options Set Here
#define HOST "127.0.0.1"
#define PORT 8887
#define ALLOWADDRPORTREUSE 0
#define CONNECTIONBACKLOG 10

using namespace std;

int main() {
    int reuse = ALLOWADDRPORTREUSE;
    struct sockaddr_in address{};

    // Get Address Length
    int sockaddr_length = sizeof(address);

    // Defines Socket to Communicate Over IPv4 with TCP
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("Failed to Create Socket");
        exit(EXIT_FAILURE);
    };

    // Configure Socket with Proper Options; Decides to allow port or address reuse based on variable set above
    int opt = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuse, sizeof(reuse));
    if (opt < 0) {
        perror("Failed to Set Socket Options");
        exit(EXIT_FAILURE);
    };

    // Configure Bind Options (sets hostname and port with the options set before)
    // AF-INET Specifies IPv4 Communication
    address.sin_family = AF_INET;
    address.sin_addr.s_addr =  inet_addr(HOST);
    address.sin_port = htons(PORT);

    // Attempt to Bind to Port and Address Specified Previously
    int bindstatus = bind(sockfd, (struct sockaddr*) &address, sizeof(address));
    if (bindstatus < 0) {
        perror("Failed to Bind Socket");
        exit(EXIT_FAILURE);
    };

    // Attempts to Listen on the Address and Port Configured Previously
    int listenstatus = listen(sockfd, CONNECTIONBACKLOG);
    if (listenstatus < 0) {
        perror("Socket could not start listening");
        exit(EXIT_FAILURE);
    };

    // Defines a Single Character Buffer for sending Simple Status Responses
    char statbuffer[1] = {0};

    int socket;
    char sockbuffer[4096];

    // Accepts a Connection on the Socket
    socket = accept(sockfd, (struct sockaddr*) &address, (socklen_t*) &sockaddr_length);
    if (socket < 0) {
        perror("Socket could not accept packet");
        exit(EXIT_FAILURE);
    };

    // Main Socket Reading Loop (continuously reads from socket as quickly as possible)
    // Still Researching Multithreading for Multiple Simultaneous Connections
    while (true) {
        // Waits for Socket to Receive Data and Puts Socket Data in the sockbuffer
        recv(socket, sockbuffer, sizeof(sockbuffer), MSG_WAITFORONE);

        bool stat = PacketReader::parsePacket(sockbuffer);

        // Sends Socket Buffer Back if PacketReader Successfully Parses Packet
        if (stat) send(socket, sockbuffer, 1, MSG_CONFIRM);

        // Sends a Single 0 if Packet Fails to Parse
        else send(socket, statbuffer, 1, MSG_CONFIRM);
    }
}

void shutdown(int socketfd) {
    close(socketfd);
    shutdown(socketfd, SHUT_RDWR);
}