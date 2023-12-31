#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
using namespace std;

bool IPtoH(const char* ip) {
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(ip, NULL, &hints, &result);
    if (status != 0) {
        cerr << "Error in getaddrinfo: " << gai_strerror(status) << endl;
        return false;
    }

    for (struct addrinfo* p = result; p != nullptr; p = p->ai_next) {
        char host[NI_MAXHOST];
        status = getnameinfo(p->ai_addr, p->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NAMEREQD);
        if (status == 0) {
            cout << "IP Address: " << ip << " => Hostname: " << host << endl;
        }
    }

    freeaddrinfo(result);
    return true;
}

bool HtoIP(const char* hostname) {
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(hostname, NULL, &hints, &result);
    if (status != 0) {
        cerr << "Error in getaddrinfo: " << gai_strerror(status) << endl;
        return false;
    }

    for (struct addrinfo* p = result; p != nullptr; p = p->ai_next) {
        char ipstr[INET6_ADDRSTRLEN];
        void* addr;
        if (p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        cout << "Hostname: " << hostname << " => IP Address: " << ipstr << endl;
    }

    freeaddrinfo(result);
    return true;
}

int main() {
    int choice;

    while (true) {
        cout << "1. IP to Hostname \n";
        cout << "2. Hostname to IP \n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char ip[100];
            cout << "Enter IP address: ";
            cin >> ip;
            IPtoH(ip);
        } else if (choice == 2) {
            char hostname[100];
            cout << "Enter hostname: ";
            cin >> hostname;
            HtoIP(hostname);
        } else if (choice == 3) {
            cout << "Exiting program.\n";
            break;
        } else {
            cerr << "Invalid choice." << endl;
        }
    }

    return 0;
}




/*
    
output
on terminal





dsl@dsl-OptiPlex-3090:~$ g++ DNS.cpp
dsl@dsl-OptiPlex-3090:~$ ./a.out
1. IP to Hostname
2. Hostname to IP
3. Exit
Enter your choice: 1
Enter IP address: 8.8.8.8
IP Address: 8.8.8.8 => Hostname: dns.google
1. IP to Hostname
2. Hostname to IP
3. Exit
Enter your choice: 2
Enter hostname: www.cloudflare.com
Hostname: www.cloudflare.com => IP Address: 104.16.124.96
Hostname: www.cloudflare.com => IP Address: 104.16.123.96
Hostname: www.cloudflare.com => IP Address: 2606:4700::6810:7c60
Hostname: www.cloudflare.com => IP Address: 2606:4700::6810:7b60
1. IP to Hostname
2. Hostname to IP
3. Exit
Enter your choice:

*/
