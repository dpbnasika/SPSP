// Subscriber.cpp
#include "../include/Subscriber.h"

Subscriber::Subscriber(const std::string& name) : name(name) {
    // Initialization if needed
}

Subscriber::~Subscriber() {
    // Clean up resources if needed
}

void Subscriber::receiveMessage(const std::string& message) {
    std::cout << "Subscriber [" << name << "] received message: " << message << std::endl;
}
