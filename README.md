Food Delivery Management System (DSA Project)
📌 Project Overview
This project is a comprehensive Console-based Food Delivery Management System developed in C++. It simulates a real-world food delivery ecosystem connecting Customers, Restaurants, and Delivery Agents. The system utilizes efficient Data Structures and Algorithms to manage data, optimize routes, and handle operations effectively.

🚀 Key Features
👤 Customer Portal
User Registration & Login: Secure ID mapping using Hash Tables.
Browse Restaurants & Menus: View available food options.
Place Orders: Real-time order processing.
Order History: View past orders (LIFO access using Stack).
Interactive Delivery Map: Visual representation of locations.
🍽️ Restaurant Portal
Menu Management: Add or update menu items.
Order Processing: View and process pending orders (FIFO using Queue).
Categorized Management: Organized restaurant views.
🚚 Delivery Portal
Agent Management: Manage delivery personnel.
Order Assignment: Assign agents to active orders.
Route Optimization: Efficient delivery paths.
⚙️ System & Analytics
Active Order Tracking: Monitor ongoing deliveries.
City Map Visualization: ASCII art representation of the city.
Shortest Path Calculation: Navigation using Dijkstra's Algorithm.
Network Optimization: Minimum Spanning Tree (MST) for network efficiency.
🛠️ Data Structures Used
This project demonstrates the practical application of the following data structures:

Linked List: Storing Restaurants, Menu Items, and Delivery Agents (Dynamic size, easy modification).
Stack (LIFO): Customer Order History (Most recent orders first).
Queue (FIFO): Order Processing (First-Come-First-Serve).
Hash Table: Customer Management (O(1) lookup for login/search).
Graph (Adjacency List): City Map representation (Nodes = Cities, Edges = Distances).
Heap (Priority Queue): Used in Dijkstra's Algorithm for efficient shortest path finding.
Union-Find (Disjoint Set): Used in Kruskal's Algorithm for MST.
🧮 Algorithms Implemented
Dijkstra's Algorithm: Finding the shortest path between Restaurant and Customer.
Prim's & Kruskal's Algorithm: Minimum Spanning Tree (MST) for network optimization.
Searching Algorithms: Linear Search (small lists) and Binary Search (sorted datasets).
Sorting Algorithms: Quick Sort / Merge Sort for organizing data.
📂 File Structure
Core System
main.cpp
: Entry point, Main Menu, and Portal logic.
IslamabadMap.h
: ASCII Map visualization.
Managers (Logic Layer)
CustomerManager.h
: Customer login, registration, data.
RestaurantManager.h
: Restaurants and Menus.
OrderManager.h
: Order placement and tracking.
DeliveryManager.h
: Agents and assignments.
Models (Data Layer)
Customer.h
, 
Restaurant.h
, 
MenuItem.h
, 
Order.h
, 
DeliveryAgent.h
Data Structures & Algorithms (Lib)
LinkedList.h
, 
Stack.h
, 
Queue.h
, 
HashTable.h
, 
Graph.h
, 
Heap.h
Dijkstra.h
, 
MST.h
, 
Searching.h
, 
Sorting.h
UI/Utils
Display.h
: UI formatting and ASCII art.






💻 How to Compile and Run
Prerequisites: G++ Compiler (MinGW for Windows)

Open a terminal in the project directory.
Compile the project:
g++ main.cpp -o food_delivery_system
Run the executable:
./food_delivery_system



