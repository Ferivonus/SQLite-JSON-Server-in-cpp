#include "Server.h"
#include <iostream>
#include <cstdlib>   // For atoi
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")  // Link with Ws2_32.lib

int find_available_port(int preferred_port) {
    WSADATA wsaData;
    SOCKET sockfd;
    sockaddr_in addr{};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return -1;
    }

    for (int port = preferred_port; port <= 65535; ++port) {
        sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sockfd == INVALID_SOCKET) {
            std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return -1;
        }

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) == 0) {
            closesocket(sockfd);
            WSACleanup();
            return port;  // Found an available port
        }

        closesocket(sockfd);
    }

    WSACleanup();
    return -1;  // No available port found
}

int main(int argc, char* argv[]) {
    int port = 8080;  // Default port

    if (argc == 2) {
        port = std::atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Invalid port number. Using default: 8080" << std::endl;
            port = 8080;
        }
    }

    int available_port = find_available_port(port);
    if (available_port == -1) {
        std::cerr << "No available port found. Exiting." << std::endl;
        return 1;
    }

    std::cout << "Starting server on port: " << available_port << std::endl;
    Server server(available_port);
    server.start();

    return 0;
}
