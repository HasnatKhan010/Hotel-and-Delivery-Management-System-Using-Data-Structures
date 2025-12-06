#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "Order.h"
#include "Queue.h"
#include "Display.h"

using namespace std;

class OrderManager {
private:
    Queue<Order> activeOrders;
    LinkedList<Order> allOrders; // For history/analytics

public:
    void placeOrder(Order order) {
        Display::printSystemLog("Using Queue::enqueue() to add order to active list...");
        activeOrders.enqueue(order);
        Display::printSystemLog("Using LinkedList::insertTail() to log order history...");
        allOrders.insertTail(order);
        Display::printSuccess("Order Placed Successfully! ID: " + order.orderID);
    }

    Order getNextOrder() {
        if (!activeOrders.isEmpty()) {
            Display::printSystemLog("Dequeuing Order from Active Queue...");
            Order o = activeOrders.front();
            activeOrders.dequeue();
            return o;
        }
        return Order();
    }

    void displayActiveOrders() {
        Display::printHeader("Active Orders");
        // Queue doesn't support traversal easily without dequeuing.
        // For display, we might need a different structure or just peek front.
        if (activeOrders.isEmpty()) {
            cout << "No active orders.\n";
        } else {
            cout << "Next Order: " << activeOrders.front() << "\n";
            cout << "(Total Active: " << activeOrders.size() << ")\n";
        }
    }
};

#endif
