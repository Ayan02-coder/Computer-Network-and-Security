#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

const int WINDOW_SIZE = 4; // Window size for Selective Repeat
const int MAX_PACKETS = 10; // Total number of packets to send

// Simulate a packet structure
struct Packet {
    int sequenceNumber;
    std::string data;
};

void sender(std::vector<Packet>& packets, std::vector<bool>& sent, int& base, int& nextSeqNum) {
    while (base < MAX_PACKETS) {
        // Send packets within the window
        for (int i = nextSeqNum; i < nextSeqNum + WINDOW_SIZE && i < MAX_PACKETS; ++i) {
            Packet packet = {i, "Data for Packet " + std::to_string(i)};
            packets[i] = packet;
            sent[i] = false;
            std::cout << "Sender: Sending Packet " << i << std::endl;
        }

        // Simulate a delay for packet transmission
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Simulate acknowledgments received
        for (int i = base; i < MAX_PACKETS; ++i) {
            if (!sent[i]) {
                std::cout << "Sender: Received acknowledgment for Packet " << i << std::endl;
                sent[i] = true;
            }
        }
    }
}

void receiver(std::vector<Packet>& packets, std::vector<bool>& received, int& base, int& nextSeqNum) {
    while (base < MAX_PACKETS) {
        for (int i = base; i < nextSeqNum + WINDOW_SIZE && i < MAX_PACKETS; ++i) {
            if (!received[i]) {
                // Simulate packet reception
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                std::cout << "Receiver: Received Packet " << i << std::endl;

                // Simulate acknowledgment transmission
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                std::cout << "Receiver: Sending acknowledgment for Packet " << i << std::endl;

                received[i] = true;

                if (i == base) {
                    // Slide the window
                    while (base < MAX_PACKETS && received[base]) {
                        base++;
                    }
                    nextSeqNum = base;
                }
            }
        }
    }
}

int main() {
    int base = 0;
    int nextSeqNum = 0;

    std::vector<Packet> packets(MAX_PACKETS);
    std::vector<bool> sent(MAX_PACKETS, false);
    std::vector<bool> received(MAX_PACKETS, false);

    std::thread senderThread(sender, std::ref(packets), std::ref(sent), std::ref(base), std::ref(nextSeqNum));
    std::thread receiverThread(receiver, std::ref(packets), std::ref(received), std::ref(base), std::ref(nextSeqNum));

    senderThread.join();
    receiverThread.join();

    return 0;
}
