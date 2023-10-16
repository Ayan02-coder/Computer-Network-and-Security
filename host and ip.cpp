

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <limits>

using namespace std;

int main() {
    string host;
    int choice;

    cout << "1. Enter Host Name\n2. Enter IP address\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter host name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, host);

        struct hostent *he;
        struct in_addr **addr_list;

        if ((he = gethostbyname(host.c_str())) == NULL) {
            cout << "Could not find " << host << endl;
            return 1;
        }

        addr_list = (struct in_addr **) he->h_addr_list;

        for (int i = 0; addr_list[i] != NULL; i++) {
            cout << "IP address: " << inet_ntoa(*addr_list[i]) << endl;
            cout << "Host name: " << he->h_name << endl;
            cout << "Host name and IP address: " << inet_ntoa(*addr_list[i]) << " " << he->h_name << endl;
        }
    } else {
        cout << "Enter IP address: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, host);

        struct hostent *he;
        struct in_addr addr;

        if (inet_pton(AF_INET, host.c_str(), &addr) != 1) {
            cout << "Invalid IP address: " << host << endl;
            return 1;
        }

        he = gethostbyaddr(&addr, sizeof(addr), AF_INET);

        if (he == NULL) {
            cout << "Could not find host for IP address: " << host << endl;
            return 1;
        }

        cout << "Host name: " << he->h_name << endl;
    }

    return 0;
}