#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "Customer.h"
#include "LinkedList.h"
#include "Display.h"
#include <string>

using namespace std;

// Using LinkedList instead of HashTable for simpler implementation
class CustomerManager {
private:
    LinkedList<Customer> customers;

public:
    void registerCustomer(string id, string name, string phone, string address) {
        Display::printSystemLog("LinkedList: Adding customer at tail");
        Customer newCustomer(id, name, phone, address);
        customers.insertTail(newCustomer);
        Display::printSuccess("Customer Registered: " + name);
    }

    Customer* login(string phone) {
        Display::printSystemLog("LinkedList: Searching for phone " + phone);
        Node<Customer>* temp = customers.getHead();
        while (temp) {
            if (temp->data.phone == phone) {
                Display::printSuccess("Customer found!");
                return new Customer(temp->data);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void displayAll() {
        Display::printHeader("All Customers");
        customers.display();
    }
};

#endif
