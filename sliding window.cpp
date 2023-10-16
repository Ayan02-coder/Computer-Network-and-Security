#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;

const int WINDOW_SIZE = 4;
const int MAX_PACKETS = 20;
const int TIMEOUT = 5;

int main() {
    srand(time(NULL));

    vector<int> packets(MAX_PACKETS);
    for (int i = 0; i < MAX_PACKETS; i++) {
        packets[i] = i;
    }

    int next_seq_num = 0;
    int base = 0;
    int expected_seq_num = 0;

    while (expected_seq_num < MAX_PACKETS) {
        if (next_seq_num < base + WINDOW_SIZE && next_seq_num < MAX_PACKETS) {
            cout << "Sending packet " << next_seq_num << endl;
            next_seq_num++;
        }

        int rand_num = rand() % 10;
        if (rand_num < 3) {
            cout << "Packet loss, sequence number = " << base << endl;
        } else {
            int ack_num;
            cout << "Enter received ACK number: ";
            cin >> ack_num;

            if (ack_num >= base && ack_num < next_seq_num) {
                base = ack_num + 1;
                cout << "Received ACK " << ack_num << ", new base = " << base << endl;
            } else {
                cout << "ACK out of range, ignoring..." << endl;
            }
        }

        if (base == expected_seq_num) {
            cout << "All packets up to " << expected_seq_num << " have been received." << endl;
            expected_seq_num++;
        }
    }

    return 0;
}
