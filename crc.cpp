#include <iostream>
#include <bitset>
#include <string>

using namespace std;

string crc(string message, string generator) {
    int m = message.length();
    int n = generator.length();

    string dividend = message + string(n - 1, '0');
    string remainder = dividend.substr(0, n);

    for (int i = 0; i < m; i++) {
        if (remainder[0] == '1') {
            for (int j = 1; j < n; j++) {
                remainder[j - 1] = ((remainder[j] == generator[j]) ? '0' : '1');
            }
        } else {
            for (int j = 1; j < n; j++) {
                remainder[j - 1] = remainder[j];
            }
        }
        remainder[n - 1] = dividend[i + n];
    }

    return message + remainder.substr(1);
}

int main() {
    string message, generator;
    cout << "Enter the message: ";
    cin >> message;
    cout << "Enter the generator: ";
    cin >> generator;

    string encoded_message = crc(message, generator);
    cout << "Encoded message: " << encoded_message << endl;

    return 0;
}
