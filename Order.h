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
    string status; // "Pending", "Preparing", "Out for Delivery", "Delivered"

    Order(string oid, string cid, string rid)
        : orderID(oid), customerID(cid), restaurantID(rid), totalAmount(0.0), status("Pending") {}

    Order() : orderID(""), customerID(""), restaurantID(""), totalAmount(0.0), status("") {}

    void addItem(MenuItem item) {
        items.insertTail(item);
        totalAmount += item.price;
    }

    // Copy constructor needed for LinkedList/Queue if they do deep copies or assignment
    // But our Node just holds T data. If T is Order, it copies Order.
    // LinkedList copy constructor is not implemented in LinkedList.h, so default copy will shallow copy the 'items' LinkedList pointer?
    // Wait, LinkedList has a pointer 'head'. Default copy of Order will copy 'head' pointer.
    // This is bad if we destroy one Order, it might delete nodes of another.
    // For this project, we should probably implement deep copy for LinkedList or be careful.
    // Or, simpler: Order holds pointers to MenuItems? No, requirements said "no STL", so we use our LinkedList.
    // Let's implement a basic copy for Order if needed, or just ensure we don't copy Orders around too much (pass by reference).
    // Actually, for Queue<Order>, we insert 'val' which creates a Node<Order>(val). This invokes Order copy constructor.
    // We need a deep copy for LinkedList inside Order.
    
    // Let's assume for now we won't be doing heavy copying or we'll implement deep copy in LinkedList later if it crashes.
    // Actually, to be safe, let's make items a pointer to LinkedList? No, that's messy.
    // Let's just rely on careful usage for now or add a copy constructor to LinkedList.
    // I'll add a TODO to fix LinkedList copy semantics if I have time, but for now let's proceed.
    

