#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include "LinkedList.h"
#include "Queue.h"
#include "MenuItem.h"
#include "Order.h"

using namespace std;

class Restaurant {
public:
    string id;
    string name;
    string category;
    double rating;
    LinkedList<MenuItem> menu;
    Queue<Order> pendingOrders;

    Restaurant(string id, string name, string cat, double rating = 0.0)
        : id(id), name(name), category(cat), rating(rating) {}

    Restaurant() : id(""), name(""), category(""), rating(0.0) {}

    void addMenuItem(MenuItem item) {
        menu.insertTail(item);
    }

    void addOrder(Order order) {
        pendingOrders.enqueue(order);
    }

    Order processNextOrder() {
        if (!pendingOrders.isEmpty()) {
            Order o = pendingOrders.front();
            pendingOrders.dequeue();
            return o;
        }
        return Order();
    }

    bool operator==(const Restaurant& other) const {
        return id == other.id;
    }

    friend ostream& operator<<(ostream& os, const Restaurant& r) {
        os << "[" << r.id << "] " << r.name << " (" << r.category << ") - " << r.rating << "*";
        return os;
    }
};

#endif
