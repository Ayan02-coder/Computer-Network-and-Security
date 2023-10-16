#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

const int WINDOW_SIZE = 4;
const int MAX_PACKETS = 10;

void sender(std::vector<int>& frames) {
    int base = 0;
    int nextSeqNum = 0;

    while (base < MAX_PACKETS) {
        for (int i = base; i < std::min(base + WINDOW_SIZE, MAX_PACKETS); ++i) {
            std::cout << "Sender: Sending frame " << i << std::endl;
            frames[i] = i;

            // Simulate network delay
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            if (i == nextSeqNum) {
                nextSeqNum++;
            }
        }

        // Simulate acknowledgment delay
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (rand() % 2 == 0) {
            std::cout << "Sender: Timeout occurred, resending frames in the window." << std::endl;
            nextSeqNum = base;
        } else {
            base = nextSeqNum;
        }
    }
}

void receiver(std::vector<int>& frames) {
    int expectedSeqNum = 0;

    while (expectedSeqNum < MAX_PACKETS) {
        if (rand() % 2 == 0) {
            std::cout << "Receiver: Frame " << expectedSeqNum << " received." << std::endl;
            expectedSeqNum++;
        } else {
            std::cout << "Receiver: Frame " << expectedSeqNum << " lost or corrupted." << std::endl;
        }

        // Simulate acknowledgment delay
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
    std::vector<int> frames(MAX_PACKETS, -1);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::thread senderThread(sender, std::ref(frames));
    std::thread receiverThread(receiver, std::ref(frames));

    senderThread.join();
    receiverThread.join();

    return 0;
}
