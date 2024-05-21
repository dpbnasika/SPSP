#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <mqueue.h>

class Publisher {
public:
    Publisher();
    ~Publisher();

    void sendMessage(const std::string& topic, const std::string& message);

private:
    mqd_t mq;
};

#endif // PUBLISHER_H
