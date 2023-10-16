#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int WINDOW_SIZE = 4;
const int TIMEOUT = 3;

int main() {
    srand(time(NULL));

    int frame_to_send = 0;
    int ack_expected = 0;
    int frame_expected = 0;
    int nbuffered = 0;
    int next_frame_to_send = 0;
    int ack_timer = 0;

    bool arrived[WINDOW_SIZE] = {false};
    bool no_nak = true;

    while (true) {
        if ((nbuffered < WINDOW_SIZE) && no_nak) {
            cout << "Sending Frame: " << next_frame_to_send << endl;
            nbuffered++;
            frame_to_send = next_frame_to_send;
            next_frame_to_send = (next_frame_to_send + 1) % (2 * WINDOW_SIZE);
            sleep(1);
        }

        if (ack_timer >= TIMEOUT) {
            cout << "Timeout Occured for Frame: " << ack_expected << endl;
            no_nak = true;
            next_frame_to_send = ack_expected;
            nbuffered = 0;
            for (int i = 0; i < WINDOW_SIZE; i++) {
                if (arrived[i]) {
                    nbuffered++;
                    ack_expected = (ack_expected + 1) % (2 * WINDOW_SIZE);
                } else {
                    break;
                }
            }
            ack_timer = 0;
        }

        int rand_num = rand() % 10;
        if (rand_num == 0) {
            cout << "Frame " << frame_expected << " Lost" << endl;
            continue;
        }

        if (frame_expected == frame_to_send) {
            nbuffered--;
            frame_expected = (frame_expected + 1) % (2 * WINDOW_SIZE);
            no_nak = true;
        }

        while (arrived[ack_expected % WINDOW_SIZE]) {
            nbuffered--;
            ack_expected = (ack_expected + 1) % (2 * WINDOW_SIZE);
            ack_timer = 0;
            no_nak = true;
        }

        if (frame_expected != frame_to_send) {
            no_nak = false;
        }

        ack_timer++;
    }

    return 0;
}
