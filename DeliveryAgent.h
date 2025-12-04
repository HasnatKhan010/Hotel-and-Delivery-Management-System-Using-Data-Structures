#ifndef DELIVERYAGENT_H
#define DELIVERYAGENT_H

#include <string>
#include "Order.h"

using namespace std;

class DeliveryAgent {
public:
    string id;
    string name;
    string phone;
    bool isAvailable;
    Order currentOrder;

    DeliveryAgent(string id, string name, string phone)
        : id(id), name(name), phone(phone), isAvailable(true) {}

    DeliveryAgent() : id(""), name(""), phone(""), isAvailable(true) {}

    void assignOrder(Order order) {
        currentOrder = order;
        isAvailable = false;
    }
    void completeDelivery() {
        isAvailable = true;
        currentOrder = Order(); // Reset
    }
