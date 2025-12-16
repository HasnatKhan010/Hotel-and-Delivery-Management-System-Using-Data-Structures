#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "LinkedList.h"
#include "MenuItem.h"

using namespace std;

class Order {
public:
    string orderID;
    string customerID;
    string restaurantID;
    LinkedList<MenuItem> items;
    double totalAmount;
    string status;

    Order(string oid, string cid, string rid)
        : orderID(oid), customerID(cid), restaurantID(rid), totalAmount(0.0), status("Pending") {}

    Order() : orderID(""), customerID(""), restaurantID(""), totalAmount(0.0), status("") {}

    void addItem(MenuItem item) {
        items.insertTail(item);
        totalAmount += item.price;
    }

    bool operator==(const Order& other) const {
        return orderID == other.orderID;
    }

    friend ostream& operator<<(ostream& os, const Order& order) {
        os << "Order " << order.orderID << " [" << order.status << "] Total: Rs." << order.totalAmount;
        return os;
    }
};

#endif
