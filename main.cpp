#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "CustomerManager.h"
#include "RestaurantManager.h"
#include "OrderManager.h"
#include "DeliveryManager.h"
#include "Display.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "MST.h"
#include "IslamabadMap.h"
#include "BST.h"
#include "AVL.h"
#include "Sorting.h"
#include "Searching.h"

using namespace std;

// +==========================================================================+
// |                        GLOBAL MANAGERS & DATA STRUCTURES                 |
// +==========================================================================+

CustomerManager cm;           // [LinkedList] Customer storage
RestaurantManager rm;         // [LinkedList] Restaurant storage
OrderManager om;              // [Queue] Order processing
DeliveryManager dm;           // [LinkedList] Delivery agents
Graph islamabadMap(15);       // [Graph - Adjacency List] City map
BST<double> ratingBST;        // [BST] Restaurant ratings
AVL<int> priceAVL;            // [AVL Tree] Menu prices

// Arrays for Sorting/Searching demos
double allRatings[10];
int ratingCount = 0;
int allPrices[20];
int priceCount = 0;

// Function declarations
void loadSampleData();
void mainMenu();
void customerPortal();
void restaurantPortal();
void driverPortal();
void graphAlgorithms();
void dsaPlayground();
void dsDocumentation();

void pause() {
    cout << "\n";
    Display::setColor(Display::GRAY);
    cout << " Press Enter to continue...";
    Display::resetColor();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printDS(const string& ds, const string& operation) {
    Display::setColor(Display::LIGHT_YELLOW);
    cout << " >> [" << ds << "] " << operation << "\n";
    Display::resetColor();
}

void printBanner(const string& title) {
    Display::setColor(Display::LIGHT_CYAN);
    cout << "\n";
    cout << " +==============================================================+\n";
    cout << " |  " << title;
    for (size_t i = title.length(); i < 60; i++) cout << " ";
    cout << "|\n";
    cout << " +==============================================================+\n";
    Display::resetColor();
}

// +============================================================================+
// |                                  MAIN                                      |
// +============================================================================+

int main() {
    srand(time(0));
    Display::clearScreen();
    Display::printAsciiArt();
    
    Display::setColor(Display::LIGHT_MAGENTA);
    cout << "        * ISLAMABAD FOOD DELIVERY SYSTEM *\n";
    cout << "        ==================================\n\n";
    Display::resetColor();
    
    Display::loadingAnimation("Initializing Data Structures");
    loadSampleData();
    pause();
    
    mainMenu();
    return 0;
}

// +==========================================================================+
// |                           LOAD SAMPLE DATA                               |
// +==========================================================================+

void loadSampleData() {
    printBanner("LOADING SAMPLE DATA");
    
    // =======================================================================
    // CUSTOMERS [LinkedList]
    // =======================================================================
    printDS("LinkedList", "Initializing customer storage...");
    cm.registerCustomer("C001", "Ahmed Khan", "0300-1111111", "F-6");
    cm.registerCustomer("C002", "Sara Ali", "0301-2222222", "G-8");
    cm.registerCustomer("C003", "Hassan Malik", "0302-3333333", "F-7");
    cm.registerCustomer("C004", "Fatima Zahra", "0303-4444444", "I-8");
    cm.registerCustomer("C005", "Omar Farooq", "0304-5555555", "G-10");
    
    // =======================================================================
    // RESTAURANTS [LinkedList] with Menu Items
    // =======================================================================
    printDS("LinkedList", "Initializing restaurant storage...");
    
    rm.addRestaurant("R001", "Monal Express", "Pakistani", 4.5);
    Restaurant* r1 = rm.getRestaurant("R001");
    if (r1) {
        r1->addMenuItem(MenuItem("M01", "Chicken Karahi", 850, "Main"));
        r1->addMenuItem(MenuItem("M02", "Seekh Kebab", 450, "BBQ"));
        r1->addMenuItem(MenuItem("M03", "Chapli Kebab", 400, "BBQ"));
        allPrices[priceCount++] = 850;
        allPrices[priceCount++] = 450;
        allPrices[priceCount++] = 400;
    }
    allRatings[ratingCount++] = 4.5;
    
    rm.addRestaurant("R002", "Zameen Restaurant", "Continental", 4.7);
    Restaurant* r2 = rm.getRestaurant("R002");
    if (r2) {
        r2->addMenuItem(MenuItem("M04", "Grilled Steak", 1500, "Main"));
        r2->addMenuItem(MenuItem("M05", "Pasta Alfredo", 950, "Italian"));
        r2->addMenuItem(MenuItem("M06", "Caesar Salad", 650, "Salad"));
        allPrices[priceCount++] = 1500;
        allPrices[priceCount++] = 950;
        allPrices[priceCount++] = 650;
    }
    allRatings[ratingCount++] = 4.7;
    
    rm.addRestaurant("R003", "Savour Foods", "Pakistani", 4.3);
    Restaurant* r3 = rm.getRestaurant("R003");
    if (r3) {
        r3->addMenuItem(MenuItem("M07", "Pulao", 280, "Rice"));
        r3->addMenuItem(MenuItem("M08", "Chicken Tikka", 350, "BBQ"));
        allPrices[priceCount++] = 280;
        allPrices[priceCount++] = 350;
    }
    allRatings[ratingCount++] = 4.3;
    
    rm.addRestaurant("R004", "KFC", "Fast Food", 4.0);
    Restaurant* r4 = rm.getRestaurant("R004");
    if (r4) {
        r4->addMenuItem(MenuItem("M09", "Zinger Burger", 550, "Burger"));
        r4->addMenuItem(MenuItem("M10", "Fries Large", 250, "Side"));
        r4->addMenuItem(MenuItem("M11", "Coleslaw", 150, "Side"));
        allPrices[priceCount++] = 550;
        allPrices[priceCount++] = 250;
        allPrices[priceCount++] = 150;
    }
    allRatings[ratingCount++] = 4.0;
    
    rm.addRestaurant("R005", "OPTP", "Fast Food", 4.4);
    Restaurant* r5 = rm.getRestaurant("R005");
    if (r5) {
        r5->addMenuItem(MenuItem("M12", "Loaded Fries", 450, "Fries"));
        r5->addMenuItem(MenuItem("M13", "Chicken Wings", 550, "Wings"));
        allPrices[priceCount++] = 450;
        allPrices[priceCount++] = 550;
    }
    allRatings[ratingCount++] = 4.4;
    
    // =======================================================================
    // BST & AVL [Tree Data Structures]
    // =======================================================================
    printDS("BST", "Inserting restaurant ratings into Binary Search Tree...");
    for (int i = 0; i < ratingCount; i++) {
        ratingBST.insert(allRatings[i]);
    }
    
    printDS("AVL Tree", "Inserting menu prices into AVL Tree (auto-balancing)...");
    for (int i = 0; i < priceCount; i++) {
        priceAVL.insert(allPrices[i]);
    }
    
    // =======================================================================
    // DELIVERY AGENTS [LinkedList]
    // =======================================================================
    printDS("LinkedList", "Registering delivery drivers...");
    dm.addAgent("D001", "Rizwan Ahmed", "0311-1111111");
    dm.addAgent("D002", "Bilal Khan", "0312-2222222");
    dm.addAgent("D003", "Usman Ali", "0313-3333333");
    dm.addAgent("D004", "Imran Shah", "0314-4444444");
    dm.addAgent("D005", "Kamran Akmal", "0315-5555555");
    
    // =======================================================================
    // GRAPH [Adjacency List] - Islamabad Road Network
    // =======================================================================
    printDS("Graph", "Building Islamabad road network (15 sectors)...");
    
    // Sector connections with distances (km)
    islamabadMap.addEdge(0, 1, 3);   // F-6 <-> F-7
    islamabadMap.addEdge(0, 4, 4);   // F-6 <-> G-6
    islamabadMap.addEdge(0, 11, 5);  // F-6 <-> E-7
    islamabadMap.addEdge(1, 2, 3);   // F-7 <-> F-8
    islamabadMap.addEdge(1, 5, 5);   // F-7 <-> G-8
    islamabadMap.addEdge(2, 3, 4);   // F-8 <-> F-10
    islamabadMap.addEdge(2, 5, 3);   // F-8 <-> G-8
    islamabadMap.addEdge(2, 13, 4);  // F-8 <-> H-8
    islamabadMap.addEdge(3, 7, 4);   // F-10 <-> G-10
    islamabadMap.addEdge(4, 5, 4);   // G-6 <-> G-8
    islamabadMap.addEdge(5, 6, 3);   // G-8 <-> G-9
    islamabadMap.addEdge(5, 13, 5);  // G-8 <-> H-8
    islamabadMap.addEdge(6, 7, 4);   // G-9 <-> G-10
    islamabadMap.addEdge(6, 14, 3);  // G-9 <-> H-9
    islamabadMap.addEdge(7, 8, 3);   // G-10 <-> G-11
    islamabadMap.addEdge(7, 10, 5);  // G-10 <-> I-10
    islamabadMap.addEdge(8, 12, 6);  // G-11 <-> E-11
    islamabadMap.addEdge(9, 10, 4);  // I-8 <-> I-10
    islamabadMap.addEdge(9, 13, 3);  // I-8 <-> H-8
    islamabadMap.addEdge(10, 14, 5); // I-10 <-> H-9
    islamabadMap.addEdge(11, 12, 7); // E-7 <-> E-11
    islamabadMap.addEdge(13, 14, 3); // H-8 <-> H-9
    
    Display::printSuccess("All data structures initialized successfully!");
}

// +==========================================================================+
// |                                MAIN MENU                                 |
// +==========================================================================+

void mainMenu() {
    int choice;
    do {
        Display::clearScreen();
        Display::printAsciiArt();
        
        printBanner("MAIN MENU - SELECT PORTAL");
        
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "\n +-------------------------------------------------------------+\n";
        cout << " | DATA STRUCTURES USED IN THIS SYSTEM:                        |\n";
        cout << " | * LinkedList  * Stack  * Queue  * BST  * AVL                |\n";
        cout << " | * Graph  * Heap  * Merge Sort  * Quick Sort                 |\n";
        cout << " | * Linear Search  * Binary Search  * Dijkstra  * MST         |\n";
        cout << " +-------------------------------------------------------------+\n\n";
        Display::resetColor();
        
        Display::setColor(Display::LIGHT_GREEN);
        cout << " [1] ";
        Display::resetColor();
        cout << "Customer Portal (Order Food)\n";
        
        Display::setColor(Display::LIGHT_GREEN);
        cout << " [2] ";
        Display::resetColor();
        cout << "Restaurant Portal (Manage Menu)\n";
        
        Display::setColor(Display::LIGHT_GREEN);
        cout << " [3] ";
        Display::resetColor();
        cout << "Driver Portal (Deliveries)\n";
        
        Display::setColor(Display::LIGHT_GREEN);
        cout << " [4] ";
        Display::resetColor();
        cout << "Graph Algorithms (Dijkstra/MST)\n";
        
        Display::setColor(Display::LIGHT_GREEN);
        cout << " [5] ";
        Display::resetColor();
        cout << "DSA Playground (Trees/Sort/Search)\n";
        
        Display::setColor(Display::LIGHT_MAGENTA);
        cout << " [6] ";
        Display::resetColor();
        cout << "Data Structures Guide (All DS + Examples)\n";
        
        Display::setColor(Display::LIGHT_RED);
        cout << " [0] ";
        Display::resetColor();
        cout << "Exit System\n";
        
        Display::printLine();
        cout << " Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: customerPortal(); break;
            case 2: restaurantPortal(); break;
            case 3: driverPortal(); break;
            case 4: graphAlgorithms(); break;
            case 5: dsaPlayground(); break;
            case 6: dsDocumentation(); break;
            case 0: 
                Display::printSuccess("Thank you for using Islamabad Food Delivery!"); 
                break;
            default: 
                Display::printError("Invalid choice! Please enter 0-6");
                pause();
        }
    } while (choice != 0);
}

// +==========================================================================+
// |                            CUSTOMER PORTAL                               |
// +==========================================================================+

void customerPortal() {
    Customer* currentCustomer = nullptr;
    int choice;
    
    do {
        Display::clearScreen();
        printBanner("CUSTOMER PORTAL");
        
        if (currentCustomer) {
            Display::setColor(Display::LIGHT_GREEN);
            cout << " * Logged in as: " << currentCustomer->name;
            cout << " | Sector: " << currentCustomer->address << "\n\n";
            Display::resetColor();
            
            cout << " [1] Browse Restaurants [LinkedList Traversal]\n";
            cout << " [2] Place Order [Queue Enqueue]\n";
            cout << " [3] View Order History [Stack Peek]\n";
            cout << " [4] View Islamabad Map [ASCII Display]\n";
            cout << " [5] Find Nearest Restaurant [Binary Search]\n";
            cout << " [6] Sort Restaurants by Rating [Merge Sort]\n";
            cout << " [7] Logout\n";
        } else {
            cout << " [1] Login [LinkedList Search]\n";
            cout << " [2] Register [LinkedList Insert]\n";
        }
        cout << " [0] Back to Main Menu\n";
        
        Display::printLine();
        cout << " Enter choice: ";
        cin >> choice;
        
        if (!currentCustomer) {
            if (choice == 1) {
                string phone;
                printDS("LinkedList", "Searching for customer by phone...");
                cout << " Enter Phone (e.g., 0300-1111111): ";
                cin >> phone;
                currentCustomer = cm.login(phone);
                if (!currentCustomer) {
                    Display::printError("Customer not found!");
                } else {
                    Display::printSuccess("Welcome back, " + currentCustomer->name + "!");
                }
                pause();
            } else if (choice == 2) {
                printDS("LinkedList", "Adding new customer at tail...");
                string id, name, phone, addr;
                cout << " Enter ID: "; cin >> id;
                cout << " Enter Name: "; cin.ignore(); getline(cin, name);
                cout << " Enter Phone: "; cin >> phone;
                cout << " Enter Sector (F-6, G-8, etc.): "; cin >> addr;
                cm.registerCustomer(id, name, phone, addr);
                pause();
            }
        } else {
            if (choice == 1) {
                // Browse Restaurants
                printDS("LinkedList", "Traversing restaurant list from head to tail...");
                LinkedList<Restaurant>& rests = rm.getAllRestaurants();
                Node<Restaurant>* temp = rests.getHead();
                int idx = 1;
                cout << "\n";
                while (temp) {
                    Display::setColor(Display::LIGHT_CYAN);
                    cout << " [" << idx++ << "] ";
                    Display::resetColor();
                    cout << temp->data.name << " | " << temp->data.category;
                    cout << " | Rating: " << temp->data.rating << "*\n";
                    temp = temp->next;
                }
                pause();
            } else if (choice == 2) {
                // Place Order
                LinkedList<Restaurant>& rests = rm.getAllRestaurants();
                Node<Restaurant>* temp = rests.getHead();
                int idx = 1;
                cout << "\n Select Restaurant:\n";
                while (temp) {
                    cout << " [" << idx++ << "] " << temp->data.name << "\n";
                    temp = temp->next;
                }
                
                int rChoice;
                cout << " Choice: "; cin >> rChoice;
                
                if (rChoice > 0 && rChoice < idx) {
                    Restaurant* rest = rm.getRestaurant(rests.get(rChoice-1).id);
                    if (rest) {
                        printDS("LinkedList", "Traversing menu items...");
                        Node<MenuItem>* m = rest->menu.getHead();
                        int mIdx = 1;
                        cout << "\n Menu:\n";
                        while (m) {
                            cout << " [" << mIdx++ << "] " << m->data.name;
                            cout << " - Rs." << m->data.price << "\n";
                            m = m->next;
                        }
                        
                        Order order("ORD" + to_string(rand()%10000), 
                                   currentCustomer->id, rest->id);
                        
                        while (true) {
                            int item;
                            cout << " Add item (0 to finish): "; cin >> item;
                            if (item == 0) break;
                            if (item > 0 && item < mIdx) {
                                printDS("LinkedList", "Adding item to order list...");
                                order.addItem(rest->menu.get(item-1));
                                Display::printSuccess("Added to cart!");
                            }
                        }
                        
                        if (order.totalAmount > 0) {
                            printDS("Queue", "Enqueuing order to global queue (FIFO)...");
                            om.placeOrder(order);
                            
                            printDS("Queue", "Enqueuing to restaurant pending queue...");
                            rest->addOrder(order);
                            
                            printDS("Stack", "Pushing order to customer history (LIFO)...");
                            currentCustomer->addOrderToHistory(order);
                            
                            Display::setColor(Display::LIGHT_GREEN);
                            cout << "\n +=======================================+\n";
                            cout << " |     ORDER PLACED SUCCESSFULLY!        |\n";
                            cout << " |     Total: Rs." << order.totalAmount;
                            cout << "                 |\n";
                            cout << " +=======================================+\n";
                            Display::resetColor();
                        }
                    }
                }
                pause();
            } else if (choice == 3) {
                // View History
                printDS("Stack", "Peek() - Viewing top element (most recent)...");
                cout << "\n";
                if (!currentCustomer->orderHistory.isEmpty()) {
                    Display::setColor(Display::LIGHT_CYAN);
                    cout << " +-----------------------------------------+\n";
                    cout << " |         MOST RECENT ORDER               |\n";
                    cout << " +-----------------------------------------+\n";
                    Display::resetColor();
                    cout << " | " << currentCustomer->orderHistory.peek() << "\n";
                    cout << " +-----------------------------------------+\n";
                } else {
                    Display::printError("Stack is empty - No orders yet!");
                }
                pause();
            } else if (choice == 4) {
                Display::clearScreen();
                printDS("ASCII Art", "Rendering Islamabad map...");
                IslamabadMap::displayMap(currentCustomer->address);
                cout << "\n Your Location: " << currentCustomer->address << " (highlighted)\n";
                pause();
            } else if (choice == 5) {
                // Binary Search for price
                printDS("Sorting", "First sorting prices using Quick Sort...");
                int sortedPrices[20];
                for (int i = 0; i < priceCount; i++) sortedPrices[i] = allPrices[i];
                Sorting<int>::quickSort(sortedPrices, priceCount);
                
                cout << " Sorted Prices: ";
                for (int i = 0; i < priceCount; i++) cout << sortedPrices[i] << " ";
                cout << "\n";
                
                int searchPrice;
                cout << " Enter price to search: ";
                cin >> searchPrice;
                
                printDS("Binary Search", "Searching in sorted array O(log n)...");
                int idx = Searching<int>::binarySearch(sortedPrices, priceCount, searchPrice);
                
                if (idx != -1) {
                    Display::printSuccess("Found at index " + to_string(idx));
                } else {
                    Display::printError("Price not found!");
                }
                pause();
            } else if (choice == 6) {
                // Sort restaurants by rating
                printDS("Array Copy", "Copying ratings to temporary array...");
                double tempRatings[10];
                for (int i = 0; i < ratingCount; i++) tempRatings[i] = allRatings[i];
                
                cout << " Original Ratings: ";
                for (int i = 0; i < ratingCount; i++) cout << tempRatings[i] << " ";
                cout << "\n";
                
                printDS("Merge Sort", "Divide & Conquer sorting O(n log n)...");
                Sorting<double>::mergeSort(tempRatings, ratingCount);
                
                cout << " Sorted Ratings:   ";
                for (int i = 0; i < ratingCount; i++) cout << tempRatings[i] << " ";
                cout << "\n";
                pause();
            } else if (choice == 7) {
                delete currentCustomer;
                currentCustomer = nullptr;
                Display::printSuccess("Logged out successfully!");
                pause();
            }
        }
    } while (choice != 0);
}

// +==========================================================================+
// |                            RESTAURANT PORTAL                             |
// +==========================================================================+

void restaurantPortal() {
    int choice;
    do {
        Display::clearScreen();
        printBanner("RESTAURANT PORTAL");
        
        cout << " [1] View All Restaurants [LinkedList Display]\n";
        cout << " [2] Manage Restaurant Menu [LinkedList Operations]\n";
        cout << " [3] Process Orders [Queue Dequeue]\n";
        cout << " [4] View Ratings in BST [Inorder Traversal]\n";
        cout << " [5] Search Rating in BST [BST Search]\n";
        cout << " [0] Back\n";
        
        Display::printLine();
        cout << " Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            printDS("LinkedList", "Traversing from head to tail...");
            rm.displayAll();
            pause();
        } else if (choice == 2) {
            LinkedList<Restaurant>& rests = rm.getAllRestaurants();
            Node<Restaurant>* temp = rests.getHead();
            int idx = 1;
            cout << "\n Select Restaurant:\n";
            while (temp) {
                cout << " [" << idx++ << "] " << temp->data.name << "\n";
                temp = temp->next;
            }
            
            int r;
            cout << " Choice: "; cin >> r;
            if (r > 0 && r < idx) {
                Restaurant* rest = rm.getRestaurant(rests.get(r-1).id);
                if (rest) {
                    printDS("LinkedList", "Displaying menu linked list...");
                    cout << "\n " << rest->name << " Menu:\n";
                    Node<MenuItem>* m = rest->menu.getHead();
                    int mIdx = 1;
                    while (m) {
                        cout << " [" << mIdx++ << "] " << m->data.name;
                        cout << " - Rs." << m->data.price << "\n";
                        m = m->next;
                    }
                }
            }
            pause();
        } else if (choice == 3) {
            printDS("Queue", "Dequeue() - Removing front element (FIFO)...");
            Order o = om.getNextOrder();
            if (o.totalAmount > 0) {
                Display::printSuccess("Processed: " + o.orderID);
            } else {
                Display::printError("Queue is empty!");
            }
            pause();
        } else if (choice == 4) {
            printDS("BST", "Inorder Traversal (Left-Root-Right) - gives sorted order...");
            cout << " Ratings in BST (sorted): ";
            ratingBST.display();
            pause();
        } else if (choice == 5) {
            double searchVal;
            cout << " Enter rating to search: ";
            cin >> searchVal;
            
            printDS("BST", "Searching recursively: compare, go left/right...");
            if (ratingBST.search(searchVal)) {
                Display::printSuccess("Rating " + to_string(searchVal) + " found in BST!");
            } else {
                Display::printError("Rating not found in BST!");
            }
            pause();
        }
    } while (choice != 0);
}

// +==========================================================================+
// |                              DRIVER PORTAL                               |
// +==========================================================================+

void driverPortal() {
    int choice;
    do {
        Display::clearScreen();
        printBanner("DRIVER PORTAL");
        
        cout << " [1] View All Drivers [LinkedList Display]\n";
        cout << " [2] Select Driver for Delivery [LinkedList Search]\n";
        cout << " [3] Pick Up Next Order [Queue Dequeue]\n";
        cout << " [4] Find Shortest Route [Dijkstra Algorithm]\n";
        cout << " [0] Back\n";
        
        Display::printLine();
        cout << " Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            printDS("LinkedList", "Displaying all delivery agents...");
            dm.displayAgents();
            pause();
        } else if (choice == 2) {
            printDS("LinkedList", "Searching for available driver...");
            cout << "\n Select Driver:\n";
            cout << " [1] Rizwan Ahmed\n";
            cout << " [2] Bilal Khan\n";
            cout << " [3] Usman Ali\n";
            cout << " [4] Imran Shah\n";
            cout << " [5] Kamran Akmal\n";
            
            int d;
            cout << " Choice: "; cin >> d;
            
            if (d >= 1 && d <= 5) {
                Display::printSuccess("Driver #" + to_string(d) + " assigned!");
            }
            pause();
        } else if (choice == 3) {
            printDS("Queue", "Dequeuing next order from global queue...");
            Order o = om.getNextOrder();
            if (o.totalAmount > 0) {
                Display::printSuccess("Picked up order: " + o.orderID);
                dm.assignAgent(o);
            } else {
                Display::printError("No orders in queue!");
            }
            pause();
        } else if (choice == 4) {
            Display::clearScreen();
            displaySectorList();
            
            int src, dest;
            cout << " Pickup Sector (0-14): "; cin >> src;
            cout << " Delivery Sector (0-14): "; cin >> dest;
            
            if (src >= 0 && src < 15 && dest >= 0 && dest < 15) {
                Dijkstra::findShortestPath(islamabadMap, src, dest);
            } else {
                Display::printError("Invalid sector numbers!");
            }
            pause();
        }
    } while (choice != 0);
}

// +==========================================================================+
// |                             GRAPH ALGORITHMS                             |
// +==========================================================================+

void graphAlgorithms() {
    int choice;
    do {
        Display::clearScreen();
        printBanner("GRAPH ALGORITHMS");
        
        cout << " [1] View Islamabad Map [ASCII Visualization]\n";
        cout << " [2] View Sector List [Array Display]\n";
        cout << " [3] Shortest Path [Dijkstra + Min-Heap]\n";
        cout << " [4] Delivery Network [Prim's MST]\n";
        cout << " [5] Delivery Network [Kruskal's MST + Union-Find]\n";
        cout << " [6] View Graph Structure [Adjacency List]\n";
        cout << " [0] Back\n";
        
        Display::printLine();
        cout << " Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            Display::clearScreen();
            IslamabadMap::displayMap();
            pause();
        } else if (choice == 2) {
            Display::clearScreen();
            displaySectorList();
            pause();
        } else if (choice == 3) {
            Display::clearScreen();
            displaySectorList();
            int src, dest;
            cout << " Source (0-14): "; cin >> src;
            cout << " Destination (0-14): "; cin >> dest;
            if (src >= 0 && src < 15 && dest >= 0 && dest < 15) {
                Dijkstra::findShortestPath(islamabadMap, src, dest);
            }
            pause();
        } else if (choice == 4) {
            Display::clearScreen();
            MST::prims(islamabadMap);
            pause();
        } else if (choice == 5) {
            Display::clearScreen();
            MST::kruskals(islamabadMap);
            pause();
        } else if (choice == 6) {
            Display::clearScreen();
            printDS("Graph", "Displaying adjacency list representation...");
            islamabadMap.display();
            pause();
        }
    } while (choice != 0);
}

// +==========================================================================+
// |                             DSA PLAYGROUND                               |
// +==========================================================================+

void dsaPlayground() {
    int choice;
    do {
        Display::clearScreen();
        printBanner("DSA PLAYGROUND - Learn Data Structures!");
        
        cout << " +--- TREES ---------------------------------------+\n";
        cout << " | [1] BST Demo - Insert, Search, Inorder          |\n";
        cout << " | [2] AVL Demo - Self-Balancing Tree              |\n";
        cout << " +-------------------------------------------------+\n";
        cout << " +--- SORTING (O(n log n)) ------------------------+\n";
        cout << " | [3] Merge Sort Demo - Divide & Conquer          |\n";
        cout << " | [4] Quick Sort Demo - Pivot Partition           |\n";
        cout << " +-------------------------------------------------+\n";
        cout << " +--- SEARCHING -----------------------------------+\n";
        cout << " | [5] Linear Search Demo - O(n)                   |\n";
        cout << " | [6] Binary Search Demo - O(log n)               |\n";
        cout << " +-------------------------------------------------+\n";
        cout << " +--- SORTING (O(n^2)) ----------------------------+\n";
        cout << " | [7] Bubble Sort Demo - Adjacent Swaps           |\n";
        cout << " | [8] Selection Sort Demo - Find Minimum          |\n";
        cout << " | [9] Insertion Sort Demo - Insert in Place       |\n";
        cout << " +-------------------------------------------------+\n";
        cout << " [0] Back\n";
        
        Display::printLine();
        cout << " Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            Display::clearScreen();
            printBanner("BINARY SEARCH TREE DEMO");
            
            printDS("BST", "Current ratings stored in BST...");
            cout << " Inorder (sorted): ";
            ratingBST.display();
            
            cout << "\n Insert new rating: ";
            double val;
            cin >> val;
            
            printDS("BST", "Inserting " + to_string(val) + " into BST...");
            ratingBST.insert(val);
            
            cout << " After insertion: ";
            ratingBST.display();
            pause();
        } else if (choice == 2) {
            Display::clearScreen();
            printBanner("AVL TREE DEMO (Self-Balancing)");
            
            printDS("AVL", "Current prices stored in AVL Tree...");
            cout << " Inorder (sorted): ";
            priceAVL.display();
            
            cout << "\n Insert new price: ";
            int val;
            cin >> val;
            
            printDS("AVL", "Inserting " + to_string(val) + " with auto-balancing...");
            priceAVL.insert(val);
            
            cout << " After insertion: ";
            priceAVL.display();
            pause();
        } else if (choice == 3) {
            Display::clearScreen();
            printBanner("MERGE SORT DEMO");
            
            int arr[] = {850, 450, 1500, 950, 280, 550, 200, 650};
            int n = 8;
            
            cout << " Original Array: ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            printDS("Merge Sort", "Divide array into halves recursively...");
            printDS("Merge Sort", "Merge sorted halves back together...");
            Sorting<int>::mergeSort(arr, n);
            
            cout << " Sorted Array:   ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            Display::printSuccess("Time Complexity: O(n log n)");
            pause();
        } else if (choice == 4) {
            Display::clearScreen();
            printBanner("QUICK SORT DEMO");
            
            int arr[] = {850, 450, 1500, 950, 280, 550, 200, 650};
            int n = 8;
            
            cout << " Original Array: ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            printDS("Quick Sort", "Choose pivot (last element)...");
            printDS("Quick Sort", "Partition: smaller left, larger right...");
            printDS("Quick Sort", "Recursively sort partitions...");
            Sorting<int>::quickSort(arr, n);
            
            cout << " Sorted Array:   ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            Display::printSuccess("Time Complexity: O(n log n) average");
            pause();
        } else if (choice == 5) {
            Display::clearScreen();
            printBanner("LINEAR SEARCH DEMO");
            
            int arr[] = {850, 450, 1500, 950, 280, 550, 200};
            int n = 7;
            
            cout << " Array: ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            int key;
            cout << " Enter value to search: ";
            cin >> key;
            
            printDS("Linear Search", "Checking each element from index 0...");
            int idx = Searching<int>::linearSearch(arr, n, key);
            
            if (idx != -1) {
                Display::printSuccess("Found at index " + to_string(idx));
            } else {
                Display::printError("Not found!");
            }
            Display::printSuccess("Time Complexity: O(n)");
            pause();
        } else if (choice == 6) {
            Display::clearScreen();
            printBanner("BINARY SEARCH DEMO");
            
            int arr[] = {200, 280, 450, 550, 850, 950, 1500};
            int n = 7;
            
            cout << " Sorted Array: ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            int key;
            cout << " Enter value to search: ";
            cin >> key;
            
            printDS("Binary Search", "Compare with middle element...");
            printDS("Binary Search", "If smaller, search left half...");
            printDS("Binary Search", "If larger, search right half...");
            int idx = Searching<int>::binarySearch(arr, n, key);
            
            if (idx != -1) {
                Display::printSuccess("Found at index " + to_string(idx));
            } else {
                Display::printError("Not found!");
            }
            Display::printSuccess("Time Complexity: O(log n)");
            pause();
        } else if (choice == 7) {
            // Bubble Sort
            Display::clearScreen();
            printBanner("BUBBLE SORT DEMO");
            
            int arr[] = {850, 450, 1500, 950, 280};
            int n = 5;
            
            cout << " Original: ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            printDS("Bubble Sort", "Compare adjacent elements...");
            printDS("Bubble Sort", "Swap if left > right...");
            printDS("Bubble Sort", "Largest bubbles to end...");
            Sorting<int>::bubbleSort(arr, n);
            
            cout << " Sorted:   ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            Display::printSuccess("Time Complexity: O(n^2)");
            pause();
        } else if (choice == 8) {
            // Selection Sort
            Display::clearScreen();
            printBanner("SELECTION SORT DEMO");
            
            int arr[] = {850, 450, 1500, 950, 280};
            int n = 5;
            
            cout << " Original: ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            printDS("Selection Sort", "Find minimum in unsorted portion...");
            printDS("Selection Sort", "Swap with first unsorted element...");
            printDS("Selection Sort", "Repeat for remaining elements...");
            Sorting<int>::selectionSort(arr, n);
            
            cout << " Sorted:   ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            Display::printSuccess("Time Complexity: O(n^2)");
            pause();
        } else if (choice == 9) {
            // Insertion Sort
            Display::clearScreen();
            printBanner("INSERTION SORT DEMO");
            
            int arr[] = {850, 450, 1500, 950, 280};
            int n = 5;
            
            cout << " Original: ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            
            printDS("Insertion Sort", "Take element from unsorted portion...");
            printDS("Insertion Sort", "Insert into correct position in sorted portion...");
            printDS("Insertion Sort", "Shift elements to make room...");
            Sorting<int>::insertionSort(arr, n);
            
            cout << " Sorted:   ";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";
            cout << "\n";
            Display::printSuccess("Time Complexity: O(n^2)");
            pause();
        }
    } while (choice != 0);
}

// +==========================================================================+
// |                      DATA STRUCTURES DOCUMENTATION                       |
// +==========================================================================+

void dsDocumentation() {
    int choice;
    do {
        Display::clearScreen();
        printBanner("DATA STRUCTURES GUIDE");
        
        Display::setColor(Display::LIGHT_YELLOW);
        cout << "\n +=============================================================+\n";
        cout << " |  Complete list of ALL Data Structures used in this project: |\n";
        cout << " +=============================================================+\n\n";
        Display::resetColor();
        
        cout << " +--- LINEAR STRUCTURES ---------------------------------------+\n";
        cout << " | [1]  LinkedList - Customers, Restaurants, Drivers           |\n";
        cout << " | [2]  Stack - Customer Order History (LIFO)                  |\n";
        cout << " | [3]  Queue - Order Processing (FIFO)                        |\n";
        cout << " +-------------------------------------------------------------+\n";
        cout << " +--- TREE STRUCTURES -----------------------------------------+\n";
        cout << " | [4]  Binary Search Tree (BST) - Restaurant Ratings          |\n";
        cout << " | [5]  AVL Tree - Menu Prices (Self-Balancing)                |\n";
        cout << " | [6]  Min-Heap - Priority Queue for Algorithms               |\n";
        cout << " +-------------------------------------------------------------+\n";
        cout << " +--- GRAPH STRUCTURES ----------------------------------------+\n";
        cout << " | [7]  Graph (Adjacency List) - Islamabad Road Network        |\n";
        cout << " +-------------------------------------------------------------+\n";
        cout << " +--- SORTING ALGORITHMS --------------------------------------+\n";
        cout << " | [8]  All Sorting Algorithms Comparison                      |\n";
        cout << " +-------------------------------------------------------------+\n";
        cout << " +--- SEARCHING ALGORITHMS ------------------------------------+\n";
        cout << " | [9]  All Searching Algorithms Comparison                    |\n";
        cout << " +-------------------------------------------------------------+\n";
        cout << " +--- GRAPH ALGORITHMS ----------------------------------------+\n";
        cout << " | [10] Dijkstra & MST Explanation                             |\n";
        cout << " +-------------------------------------------------------------+\n";
        cout << " [0] Back\n";
        
        Display::printLine();
        cout << " Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            Display::clearScreen();
            printBanner("LINKEDLIST");
            
            Display::setColor(Display::LIGHT_CYAN);
            cout << R"(
 +=======================================================================+
 |                           LINKED LIST                                 |
 +=======================================================================+
 |  DEFINITION: Linear data structure where elements (nodes) are         |
 |  connected via pointers. Each node contains data + next pointer.      |
 +=======================================================================+
 |  VISUAL:                                                              |
 |                                                                       |
 |    HEAD                                                               |
 |     |                                                                 |
 |     v                                                                 |
 |  +------+---+   +------+---+   +------+---+                           |
 |  | DATA | ->+-->| DATA | ->+-->| DATA | X |                           |
 |  +------+---+   +------+---+   +------+---+                           |
 |   Node 1         Node 2         Node 3 (NULL)                         |
 +=======================================================================+
 |  COMPLEXITY:                                                          |
 |  * Insert at Head: O(1)     * Insert at Tail: O(n)                    |
 |  * Delete: O(n)             * Search: O(n)                            |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * CustomerManager -> stores all customers in LinkedList              |
 |  * RestaurantManager -> stores all restaurants                        |
 |  * DeliveryManager  -> stores all delivery drivers                    |
 |  * Restaurant.menu  -> stores menu items                              |
 |  * Order.items      -> stores items in an order                       |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 2) {
            Display::clearScreen();
            printBanner("STACK");
            
            Display::setColor(Display::LIGHT_GREEN);
            cout << R"(
 +=======================================================================+
 |                               STACK                                   |
 +=======================================================================+
 |  DEFINITION: LIFO (Last-In-First-Out) structure.                      |
 |  Elements added and removed from the SAME end (TOP).                  |
 +=======================================================================+
 |  VISUAL:                                                              |
 |                                                                       |
 |         PUSH |     ^ POP                                              |
 |              v     |                                                  |
 |       +-----------------+                                             |
 |  TOP->|  Order #103     |  <- Most Recent (accessed first)            |
 |       +-----------------+                                             |
 |       |  Order #102     |                                             |
 |       +-----------------+                                             |
 |       |  Order #101     |  <- Oldest (accessed last)                  |
 |       +-----------------+                                             |
 +=======================================================================+
 |  OPERATIONS:                                                          |
 |  * push(item)  - Add to top: O(1)                                     |
 |  * pop()       - Remove from top: O(1)                                |
 |  * peek()      - View top without removing: O(1)                      |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * Customer.orderHistory -> Most recent order on top                  |
 |  * When customer views history, they see latest order first           |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 3) {
            Display::clearScreen();
            printBanner("QUEUE");
            
            Display::setColor(Display::LIGHT_YELLOW);
            cout << R"(
 +=======================================================================+
 |                               QUEUE                                   |
 +=======================================================================+
 |  DEFINITION: FIFO (First-In-First-Out) structure.                     |
 |  Elements added at REAR, removed from FRONT.                          |
 +=======================================================================+
 |  VISUAL:                                                              |
 |                                                                       |
 |  DEQUEUE <--+                                   +--> ENQUEUE          |
 |             |                                   |                     |
 |       +---------+---------+---------+---------+                       |
 |       | Order 1 | Order 2 | Order 3 | Order 4 |                       |
 |       +---------+---------+---------+---------+                       |
 |          ^                           ^                                |
 |        FRONT                        REAR                              |
 |      (Oldest)                     (Newest)                            |
 +=======================================================================+
 |  OPERATIONS:                                                          |
 |  * enqueue(item) - Add to rear: O(1)                                  |
 |  * dequeue()     - Remove from front: O(1)                            |
 |  * front()       - View front element: O(1)                           |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * OrderManager.activeOrders -> Global order queue                    |
 |  * Restaurant.pendingOrders  -> Per-restaurant queue                  |
 |  * Orders processed in the order they were placed (fair!)             |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 4) {
            Display::clearScreen();
            printBanner("BINARY SEARCH TREE (BST)");
            
            Display::setColor(Display::LIGHT_MAGENTA);
            cout << R"(
 +=======================================================================+
 |                      BINARY SEARCH TREE (BST)                         |
 +=======================================================================+
 |  DEFINITION: Tree where each node has at most 2 children.             |
 |  Left child < Parent < Right child (Binary Search Property)           |
 +=======================================================================+
 |  VISUAL (Restaurant Ratings):                                         |
 |                                                                       |
 |                        4.5                                            |
 |                       /   \                                           |
 |                     4.3   4.7                                         |
 |                    /   \                                              |
 |                  4.0   4.4                                            |
 |                                                                       |
 |  Inorder Traversal (sorted): 4.0, 4.3, 4.4, 4.5, 4.7                  |
 +=======================================================================+
 |  COMPLEXITY:                                                          |
 |  * Insert: O(log n) average, O(n) worst (skewed)                      |
 |  * Search: O(log n) average, O(n) worst                               |
 |  * Delete: O(log n) average                                           |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * ratingBST -> Stores restaurant ratings                             |
 |  * Enables fast search for ratings                                    |
 |  * Inorder gives sorted ratings automatically                         |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 5) {
            Display::clearScreen();
            printBanner("AVL TREE (Self-Balancing BST)");
            
            Display::setColor(Display::LIGHT_CYAN);
            cout << R"(
 +=======================================================================+
 |                            AVL TREE                                   |
 +=======================================================================+
 |  DEFINITION: Self-balancing BST that maintains height difference      |
 |  between left and right subtrees <= 1 (Balance Factor)                |
 +=======================================================================+
 |  ROTATIONS (to maintain balance):                                     |
 |                                                                       |
 |   Right Rotation (RR):        Left Rotation (LL):                     |
 |        y                           x                                  |
 |       / \                         / \                                 |
 |      x   T3  ------>             T1  y                                |
 |     / \                             / \                               |
 |    T1  T2                          T2  T3                             |
 +=======================================================================+
 |  COMPLEXITY (GUARANTEED):                                             |
 |  * Insert: O(log n) always                                            |
 |  * Search: O(log n) always                                            |
 |  * Delete: O(log n) always                                            |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * priceAVL -> Stores menu item prices with guaranteed O(log n)       |
 |  * Better than BST when frequent insertions/deletions                 |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 6) {
            Display::clearScreen();
            printBanner("MIN-HEAP (Priority Queue)");
            
            Display::setColor(Display::LIGHT_GREEN);
            cout << R"(
 +=======================================================================+
 |                      MIN-HEAP (Priority Queue)                        |
 +=======================================================================+
 |  DEFINITION: Complete binary tree where parent <= children            |
 |  Smallest element always at ROOT                                      |
 +=======================================================================+
 |  VISUAL:                                                              |
 |                                                                       |
 |                      10  <- MIN (always at root)                      |
 |                     /  \                                              |
 |                   20    15                                            |
 |                  /  \   /  \                                          |
 |                40  50  30  25                                         |
 |                                                                       |
 |  Array: [10, 20, 15, 40, 50, 30, 25]                                  |
 |  Parent(i)=(i-1)/2  Left(i)=2i+1  Right(i)=2i+2                       |
 +=======================================================================+
 |  COMPLEXITY:                                                          |
 |  * Insert: O(log n)      * Extract Min: O(log n)                      |
 |  * Get Min: O(1)                                                      |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * Dijkstra's Algorithm -> Always process closest vertex              |
 |  * Prim's MST -> Always add minimum weight edge                       |
 |  * Kruskal's MST -> Sort edges by weight                              |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 7) {
            Display::clearScreen();
            printBanner("GRAPH (Adjacency List)");
            
            Display::setColor(Display::LIGHT_YELLOW);
            cout << R"(
 +=======================================================================+
 |                    GRAPH (Adjacency List)                             |
 +=======================================================================+
 |  DEFINITION: Collection of vertices (nodes) connected by edges        |
 |  Adjacency List = Array of LinkedLists                                |
 +=======================================================================+
 |  VISUAL (Islamabad Sectors):                                          |
 |                                                                       |
 |       F-6 ----3km---- F-7 ----3km---- F-8                             |
 |        |               |               |                              |
 |       4km             5km             4km                             |
 |        |               |               |                              |
 |       G-6 ----4km---- G-8 ----3km---- G-9                             |
 |                                                                       |
 |  Adjacency List:                                                      |
 |  F-6 -> [(F-7,3), (G-6,4)]                                            |
 |  F-7 -> [(F-6,3), (F-8,3), (G-8,5)]                                   |
 |  ...                                                                  |
 +=======================================================================+
 |  COMPLEXITY:                                                          |
 |  * Space: O(V + E)       * Add Edge: O(1)                             |
 |  * Check Edge: O(degree) * Get Neighbors: O(1)                        |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * islamabadMap -> 15 sectors as vertices, roads as edges             |
 |  * Used by Dijkstra to find shortest delivery route                   |
 |  * Used by MST to build optimal delivery network                      |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 8) {
            Display::clearScreen();
            printBanner("ALL SORTING ALGORITHMS");
            
            Display::setColor(Display::LIGHT_CYAN);
            cout << R"(
 +=======================================================================+
 |                    SORTING ALGORITHMS COMPARISON                      |
 +=======================================================================+
 |                                                                       |
 |  +---------------+---------+---------+---------+---------+            |
 |  |  Algorithm    |  Best   | Average |  Worst  |  Space  |            |
 |  +---------------+---------+---------+---------+---------+            |
 |  | Bubble Sort   |  O(n)   | O(n^2)  | O(n^2)  |  O(1)   |            |
 |  | Selection Sort|  O(n^2) | O(n^2)  | O(n^2)  |  O(1)   |            |
 |  | Insertion Sort|  O(n)   | O(n^2)  | O(n^2)  |  O(1)   |            |
 |  | Merge Sort    |O(n logn)|O(n logn)|O(n logn)|  O(n)   |            |
 |  | Quick Sort    |O(n logn)|O(n logn)| O(n^2)  |O(log n) |            |
 |  +---------------+---------+---------+---------+---------+            |
 |                                                                       |
 +=======================================================================+
 |  Bubble Sort:    Compare adjacent, swap if wrong order                |
 |  Selection Sort: Find minimum, swap to front                          |
 |  Insertion Sort: Insert each element into sorted portion              |
 |  Merge Sort:     Divide in halves, merge sorted halves                |
 |  Quick Sort:     Pick pivot, partition around it                      |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * Sort restaurant ratings for display                                |
 |  * Sort menu prices for binary search                                 |
 |  * Kruskal's MST sorts edges by weight                                |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 9) {
            Display::clearScreen();
            printBanner("ALL SEARCHING ALGORITHMS");
            
            Display::setColor(Display::LIGHT_MAGENTA);
            cout << R"(
 +=======================================================================+
 |                   SEARCHING ALGORITHMS COMPARISON                     |
 +=======================================================================+
 |                                                                       |
 |  LINEAR SEARCH:                                                       |
 |  +---+---+---+---+---+---+---+                                        |
 |  | 5 | 2 | 8 | 1 | 9 | 3 | 7 |  Find 9: Check each -> Found at 4      |
 |  +---+---+---+---+---+---+---+                                        |
 |    ^   ^   ^   ^   ^                                                  |
 |   O(n) - Check every element until found                              |
 |                                                                       |
 |  BINARY SEARCH (requires sorted array):                               |
 |  +---+---+---+---+---+---+---+                                        |
 |  | 1 | 2 | 3 | 5 | 7 | 8 | 9 |  Find 7                                |
 |  +---+---+---+---+---+---+---+                                        |
 |              ^ mid=5, 7>5 -> search right                             |
 |                      ^ mid=8, 7<8 -> search left                      |
 |                  ^ mid=7, FOUND!                                      |
 |   O(log n) - Divide in half each step                                 |
 |                                                                       |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * Linear: Search customer by phone in LinkedList                     |
 |  * Binary: Search price in sorted array                               |
 |  * BST Search: Find rating in Binary Search Tree                      |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        } else if (choice == 10) {
            Display::clearScreen();
            printBanner("GRAPH ALGORITHMS: DIJKSTRA & MST");
            
            Display::setColor(Display::LIGHT_GREEN);
            cout << R"(
 +=======================================================================+
 |                DIJKSTRA'S SHORTEST PATH ALGORITHM                     |
 +=======================================================================+
 |  PURPOSE: Find shortest path from source to all vertices              |
 |                                                                       |
 |  HOW IT WORKS:                                                        |
 |  1. Set distance[source] = 0, all others = infinity                   |
 |  2. Use Min-Heap to always process closest unvisited vertex           |
 |  3. Update distances to neighbors if shorter path found               |
 |  4. Repeat until destination reached                                  |
 |                                                                       |
 |  Complexity: O((V + E) log V) with Min-Heap                           |
 +=======================================================================+
 |                                                                       |
 |             MINIMUM SPANNING TREE ALGORITHMS                          |
 +=======================================================================+
 |  PURPOSE: Connect all vertices with minimum total edge weight         |
 |                                                                       |
 |  PRIM'S: Start from vertex, greedily add minimum edge                 |
 |  KRUSKAL'S: Sort all edges, add if no cycle (Union-Find)              |
 |                                                                       |
 |  Both produce same MST weight!                                        |
 +=======================================================================+
 |  USAGE IN OUR PROJECT:                                                |
 |  * Dijkstra: Find fastest delivery route between sectors              |
 |  * MST: Build optimal delivery network covering all sectors           |
 +=======================================================================+
)";
            Display::resetColor();
            pause();
        }
    } while (choice != 0);
}