#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "LinkedList.h"
#include "Stack.h"
#include "Order.h"

using namespace std;

class Customer {
public:
    string id;
    string name;
    string phone;
    string address;
    Stack<Order> orderHistory; // Stack for history (LIFO - most recent first)

    Customer(string id, string name, string phone, string addr)
        : id(id), name(name), phone(phone), address(addr) {}

    Customer() : id(""), name(""), phone(""), address("") {}

    void addOrderToHistory(Order order) {
        orderHistory.push(order);
    }

    bool operator==(const Customer& other) const {
        return id == other.id;
    }

    friend ostream& operator<<(ostream& os, const Customer& c) {
        os << "[" << c.id << "] " << c.name << " (" << c.phone << ")";
        return os;
    }
};

#endif
