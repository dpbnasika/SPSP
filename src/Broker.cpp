// Broker.cpp
#include "../include/Broker.h"
#include "../include/Subscriber.h"
#include <cstring>
#include <iostream>

Broker::Broker() : running(true) {
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;

    mq = mq_open("/broker_mq", O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    messageHandlerThread = std::thread(&Broker::handleMessages, this);
}

Broker::~Broker() {
    running = false;
    mq_close(mq);
    mq_unlink("/broker_mq");
    messageHandlerThread.join();
}

void Broker::addSubscriber(const std::string& topic, Subscriber* subscriber) {
    if (subscriptions.find(topic) == subscriptions.end()) {
        subscriptions[topic] = std::vector<Subscriber*>();
    }
    subscriptions[topic].push_back(subscriber);
}

void Broker::removeSubscriber(const std::string& topic, Subscriber* subscriber) {
    if (subscriptions.find(topic) != subscriptions.end()) {
        auto& subscribers = subscriptions[topic];
        subscribers.erase(subscribers.begin(), subscribers.end());
    }
}

void Broker::run() {
    // This will keep the main thread alive while the message handler runs
    messageHandlerThread.join();
}

void Broker::handleMessages() {
    char buffer[256];
    while (running) {
        ssize_t bytes_read = mq_receive(mq, buffer, 256, nullptr);
        if (bytes_read >= 0) {
            buffer[bytes_read] = '\0';
            std::string message(buffer);
            std::string topic = message.substr(0, message.find(':'));
            std::string msg = message.substr(message.find(':') + 1);

            if (subscriptions.find(topic) != subscriptions.end()) {
                const auto& subscribers = subscriptions[topic];
                for (auto subscriber : subscribers) {
                    subscriber->receiveMessage(msg);
                }
            }
        }
    }
}
