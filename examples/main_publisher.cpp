#include "../include/Publisher.h"
#include <chrono>
#include <thread>

int main() {
    Publisher publisher;
    int counter = 1;

    // Continuously send messages
    while (true) {
        publisher.sendMessage("topic1", "Hello from Publisher to topic1, message number " + std::to_string(counter));
        publisher.sendMessage("topic2", "Hello from Publisher to topic2, message number " + std::to_string(counter));
        counter++;

        // Sleep for 1 second before sending the next message
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
