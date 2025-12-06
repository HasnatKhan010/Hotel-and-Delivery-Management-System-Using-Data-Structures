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

