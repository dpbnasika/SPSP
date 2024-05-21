#include "../include/Publisher.h"
#include <cstring>
#include <iostream>
#include <csignal>
#include <unistd.h>

Publisher::Publisher() {
    mq = mq_open("/broker_mq", O_WRONLY);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }
}

Publisher::~Publisher() {
    mq_close(mq);
}

void Publisher::sendMessage(const std::string& topic, const std::string& message) {
    std::string fullMessage = topic + ":" + message;
    if (mq_send(mq, fullMessage.c_str(), fullMessage.size() + 1, 0) == -1) {
        perror("mq_send");
    }
}