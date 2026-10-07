# Smart Campus Navigation & Route Optimization System

## IIIT Bhubaneswar

A C++ based Smart Campus Navigation and Route Optimization System designed to provide interactive campus navigation, intelligent route selection, and dynamic route management.

The system models the campus as a navigable graph where campus locations are represented as nodes and connecting paths are represented as weighted edges.

---

## Features

### Student / Visitor

* Explore the IIIT Bhubaneswar campus
* View a visual campus map
* Search for buildings and facilities
* Find routes between campus locations
* Select route preferences
* View route distance and estimated travel time
* Receive alternative routes when a path is unavailable

### Administrator

* View and manage campus locations
* Block or restore campus routes
* Record reasons for route obstruction
* Add or modify campus facilities
* View active campus alerts
* Dynamically affect available navigation routes

### Route Optimization

* Shortest route
* Fastest route
* Accessible route
* Dynamic route recalculation
* Obstruction-aware navigation

---

## OOP Concepts Used

The project demonstrates major Object-Oriented Programming concepts through the system architecture:

* Classes and Objects
* Encapsulation
* Abstraction
* Inheritance
* Compile-time Polymorphism
* Runtime Polymorphism
* Constructors and Destructors
* Function Overloading
* Operator Overloading
* Composition and Aggregation
* Static Members
* Dynamic Memory Management

---

## Core Technologies

* **Programming Language:** C++
* **Data Structures:** Graphs, Vectors, Maps, Priority Queues
* **Algorithm:** Dijkstra's Shortest Path Algorithm
* **Data Persistence:** File Handling
* **Interface:** Interactive C++ Console UI

No external programming language or framework is required.

---

## System Architecture

```text
                    SMART CAMPUS SYSTEM
                            |
              +-------------+-------------+
              |                           |
           STUDENT                     ADMIN
              |                           |
       Navigation UI               Management UI
              |                           |
              +-------------+-------------+
                            |
                     CAMPUS GRAPH
                            |
                    ROUTE ENGINE
                            |
                 Route Optimization
                            |
                 Dynamic Route Updates
```

---

## Campus Model

The system uses a logical navigation model of the IIIT Bhubaneswar campus.

Campus locations include academic, residential, recreational and common facilities. Each location is represented as a node, while navigable connections between locations are represented as weighted edges.

The graph can dynamically change when an administrator blocks or restores a route.

---

## Project Structure

```text
SmartCampusNav/
│
├── include/       # Header files
├── src/           # C++ implementations
├── data/          # Campus and route data
├── tests/         # Testing files
├── docs/          # Project documentation
│
├── main.cpp
├── README.md
└── .gitignore
```

---

## Example Scenario

A student requests a route from a hostel to the library.

The system calculates the optimal route:

```text
HOSTEL D
   |
   v
STUDENT CENTRE
   |
   v
ACADEMIC BLOCK
   |
   v
LIBRARY
```

If the administrator blocks the path between the Academic Block and Library because of construction work, the system automatically recalculates the route and provides an alternative path.

---

## Objective

The primary objective is to demonstrate how Object-Oriented Programming and graph-based route optimization can be combined to build a practical smart-campus navigation system.

The project emphasizes modular design, real-world applicability, dynamic system behavior, and clear application of OOP principles.