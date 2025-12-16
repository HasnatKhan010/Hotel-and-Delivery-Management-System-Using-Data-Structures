#ifndef DELIVERYMANAGER_H
#define DELIVERYMANAGER_H

#include "DeliveryAgent.h"
#include "LinkedList.h"
#include "Display.h"

using namespace std;

class DeliveryManager {
private:
    LinkedList<DeliveryAgent> agents;

public:
    void addAgent(string id, string name, string phone) {
        DeliveryAgent da(id, name, phone);
        agents.insertTail(da);
        Display::printSuccess("Agent Added: " + name);
    }

    DeliveryAgent* getAvailableAgent() {
        Display::printSystemLog("Searching LinkedList for available agent...");
        Node<DeliveryAgent>* temp = agents.getHead();
        while (temp) {
            if (temp->data.isAvailable) {
                Display::printSystemLog("Available agent found.");
                return &(temp->data);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void assignAgent(Order order) {
        DeliveryAgent* agent = getAvailableAgent();
        if (agent) {
            agent->assignOrder(order);
            Display::printSuccess("Order assigned to agent: " + agent->name);
        } else {
            Display::printError("No delivery agents available!");
        }
    }

    void displayAgents() {
        Display::printHeader("Delivery Agents");
        agents.display();
    }
};

#endif
