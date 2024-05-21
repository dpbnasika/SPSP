// Subscriber.h
#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <string>
#include <iostream>

class Subscriber {
public:
    Subscriber(const std::string& name);
    ~Subscriber();

    void receiveMessage(const std::string& message);

private:
    std::string name;
};

#endif // SUBSCRIBER_H
