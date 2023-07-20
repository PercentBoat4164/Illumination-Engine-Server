#include "Protocol/PacketReader.hpp"
#include "ResourceDelegator.hpp"

#include <arpa/inet.h>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>

// Global Options
#define HOST "127.0.0.1"
#define PORT 8887
#define ALLOWADDRPORTREUSE 0
#define CONNECTIONBACKLOG 10

int main() {
    int reuse = ALLOWADDRPORTREUSE;
    struct sockaddr_in address{};

    auto res = ResourceDelegator();
    auto protocol = PacketReader(res);

    // Get Address Length
    int sockaddr_length = sizeof(address);

    // Defines Socket to Communicate Over IPv4 with TCP
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
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
    address.sin_addr.s_addr = inet_addr(HOST);
    address.sin_port = htons(PORT);

    // Attempt to Bind to Port and Address Specified Previously
    int bindstatus = bind(sockfd, reinterpret_cast<sockaddr *>(&address), sizeof(address));
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

    char sockbuffer[4096];

    // Accepts a Connection on the Socket
    int socket = accept4(sockfd, reinterpret_cast<sockaddr *>(&address),
                         reinterpret_cast<socklen_t *>(&sockaddr_length), SOCK_CLOEXEC);
    if (socket < 0) {
        perror("Socket could not accept packet");
        exit(EXIT_FAILURE);
    };

    // Main Socket Reading Loop (continuously reads from socket as quickly as possible)
    // Still Researching Multithreading for Multiple Simultaneous Connections
    while (true) {
        // Waits for Socket to Receive Data and Puts Socket Data in the sockbuffer
        recv(socket, static_cast<char *>(sockbuffer), sizeof(sockbuffer), MSG_WAITFORONE);

        protocol.parsePacket(static_cast<char *>(sockbuffer), sockfd);
    }
}