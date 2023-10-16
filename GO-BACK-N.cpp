#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

int main() {
    srand(time(NULL));

    int window_size = 4;
    int sequence_number = 0;
    int next_sequence_number = 0;
    int ack_number = 0;
    int timeout = 3;

    while (true) {
        // simulate packet transmission
        sleep(1);

        // simulate packet loss
        if (rand() % 10 < 3) {
            cout << "Packet loss, sequence number: " << sequence_number << endl;
            continue;
        }

        // simulate packet corruption
        if (rand() % 10 < 3) {
            cout << "Packet corruption, sequence number: " << sequence_number << endl;
            continue;
        }

        // simulate ACK loss
        if (rand() % 10 < 3) {
            cout << "ACK loss, ACK number: " << ack_number << endl;
            continue;
        }

        // simulate ACK corruption
        if (rand() % 10 < 3) {
            cout << "ACK corruption, ACK number: " << ack_number << endl;
            continue;
        }

        // simulate timeout
        if (rand() % 10 < 3) {
            cout << "Timeout, sequence number: " << sequence_number << endl;
            next_sequence_number = sequence_number;
            continue;
        }

        // simulate successful transmission
        cout << "Packet sent, sequence number: " << sequence_number << endl;

        // update sequence number
        sequence_number++;

        // update next sequence number
        if (sequence_number == next_sequence_number + window_size) {
            next_sequence_number = sequence_number;
        }

        // simulate ACK reception
        if (sequence_number == ack_number + 1) {
            cout << "ACK received, ACK number: " << ack_number << endl;
            ack_number++;
        }
    }

    return 0;
}
