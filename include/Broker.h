#ifndef BROKER_H
#define BROKER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <mqueue.h>
#include <thread>
#include <atomic>

class Subscriber;

class Broker {
public:
    static Broker& getInstance() {
        static Broker instance;
        return instance;
    }

    void addSubscriber(const std::string& topic, Subscriber* subscriber);
    void removeSubscriber(const std::string& topic, Subscriber* subscriber);
    void run();

private:
    Broker();
    ~Broker();

    void handleMessages();
    std::unordered_map<std::string, std::vector<Subscriber*>> subscriptions;
    std::atomic<bool> running;
    mqd_t mq;
    std::thread messageHandlerThread;
};

#endif // BROKER_H
