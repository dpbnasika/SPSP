// main_subscriber.cpp
#include "../include/Subscriber.h"
#include "../include/Broker.h"

int main() {
    Subscriber subscriber1("Subscriber1");
    Subscriber subscriber2("Subscriber2");
    Broker& broker = Broker::getInstance();

    broker.addSubscriber("topic1", &subscriber1);
    broker.addSubscriber("topic2", &subscriber2);

    // Keep the broker running to handle messages
    broker.run();

    return 0;
}
