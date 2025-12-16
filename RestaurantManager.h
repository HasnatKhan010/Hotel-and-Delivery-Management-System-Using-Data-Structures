#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include "Restaurant.h"
#include "LinkedList.h"
#include "Display.h"

using namespace std;

class RestaurantManager {
private:
    LinkedList<Restaurant> restaurants;

public:
    void addRestaurant(string id, string name, string cat, double rating) {
        Restaurant r(id, name, cat, rating);
        restaurants.insertTail(r);
        Display::printSystemLog("Added Restaurant to LinkedList.");
        Display::printSuccess("Restaurant Added: " + name);
    }

    Restaurant* getRestaurant(string id) {
        Display::printSystemLog("Traversing LinkedList to find Restaurant...");
        Node<Restaurant>* temp = restaurants.getHead();
        while (temp) {
            if (temp->data.id == id) {
                Display::printSystemLog("Restaurant found.");
                return &(temp->data); // Return pointer to actual object in list
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void displayAll() const {
        Display::printHeader("Available Restaurants");
        Display::printSystemLog("Iterating through LinkedList to display all restaurants...");
        restaurants.display();
    }

    LinkedList<Restaurant>& getAllRestaurants() {
        return restaurants;
    }

    // Simple search by category
    void searchByCategory(string cat) {
        Display::printHeader("Restaurants in " + cat);
        Display::printSystemLog("Linear Search in LinkedList for category match...");
        Node<Restaurant>* temp = restaurants.getHead();
        bool found = false;
        while (temp) {
            if (temp->data.category == cat) {
                cout << temp->data << "\n";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) Display::printError("No restaurants found in this category.");
    }
};

#endif
