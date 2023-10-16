#include <iostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    // Prompt the user for input
    std::cout << "Enter an IP address or a domain name: ";
    std::string input;
    std::cin >> input;

    // Check if the input is an IP address or a domain name
    struct sockaddr_in sa;
    int result_ip = inet_pton(AF_INET, input.c_str(), &(sa.sin_addr));

    if (result_ip == 1) {
        // Input is an IP address, perform reverse DNS lookup
        struct hostent* host;
        host = gethostbyaddr(&(sa.sin_addr), sizeof(sa.sin_addr), AF_INET);
        
        if (host != NULL) {
            std::cout << "URI: " << host->h_name << std::endl;
        } else {
            std::cerr << "Reverse DNS lookup failed." << std::endl;
        }
    } else {
        // Input is a domain name, perform DNS lookup
        struct hostent* host;
        host = gethostbyname(input.c_str());
        
        if (host != NULL) {
            std::cout << "IP Address: " << inet_ntoa(*(struct in_addr*)host->h_addr_list[0]) << std::endl;
        } else {
            std::cerr << "DNS lookup failed." << std::endl;
        }
    }

    return 0;
}
    