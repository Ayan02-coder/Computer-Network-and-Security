#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

const int WINDOW_SIZE = 4;  // Window size for Go-Back-N
const int MAX_PACKETS = 10;  // Total number of packets to send

// Simulate a packet structure
struct Packet {
    int sequenceNumber;
    std::string data;
};

void sender(std::vector<Packet>& packets, int& base, int& nextSeqNum) {
    while (base < MAX_PACKETS) {
        // Send packets within the window
        for (int i = nextSeqNum; i < nextSeqNum + WINDOW_SIZE && i < MAX_PACKETS; ++i) {
            Packet packet = {i, "Data for Packet " + std::to_string(i)};
            packets[i] = packet;
            std::cout << "Sender: Sending Packet " << i << std::endl;
        }

        // Simulate a delay for packet transmission
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Simulate acknowledgments received
        for (int i = base; i < nextSeqNum; ++i) {
            std::cout << "Sender: Received acknowledgment for Packet " << i << std::endl;
            base++;
        }
    }
}

void receiver(int& expectedSeqNum, int& ack) {
    while (expectedSeqNum < MAX_PACKETS) {
        // Simulate packet reception
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        std::cout << "Receiver: Received Packet " << expectedSeqNum << std::endl;

        // Simulate acknowledgment transmission
        ack = expectedSeqNum;

        expectedSeqNum++;
    }
}

int main() {
    int base = 0;
    int nextSeqNum = 0;
    int expectedSeqNum = 0;
    int ack = -1;

    std::vector<Packet> packets(MAX_PACKETS);

    std::thread senderThread(sender, std::ref(packets), std::ref(base), std::ref(nextSeqNum));
    std::thread receiverThread(receiver, std::ref(expectedSeqNum), std::ref(ack));

    senderThread.join();
    receiverThread.join();

    return 0;
}
