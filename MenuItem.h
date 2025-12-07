#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <iostream>

using namespace std;

class MenuItem {
public:
    string id;
    string name;
    double price;
    double rating;
    string category;

    MenuItem(string id, string name, double price, string cat, double rating = 0.0)
        : id(id), name(name), price(price), rating(rating), category(cat) {}

    MenuItem() : id(""), name(""), price(0.0), rating(0.0), category("") {}

    // Overload operators for comparison (needed for sorting/searching/BST)
    bool operator<(const MenuItem& other) const {
        return price < other.price; // Default sort by price? Or maybe name?
    }

    bool operator>(const MenuItem& other) const {
        return price > other.price;
    }

    bool operator==(const MenuItem& other) const {
        return id == other.id;
    }

    friend ostream& operator<<(ostream& os, const MenuItem& item) {
        os << "[" << item.id << "] " << item.name << " ($" << item.price << ") - " << item.rating << "*";
        return os;
    }
};

#endif
