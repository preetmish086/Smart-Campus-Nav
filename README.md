<div align="center">

<img src="assets/logo.png" alt="IIIT Bhubaneswar Logo" width="80" style="border-radius: 50%;" />

# Smart Campus Navigation and Route Optimization System

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![OOP](https://img.shields.io/badge/Paradigm-OOP-orange.svg)
![Institution](https://img.shields.io/badge/IIIT-Bhubaneswar-purple.svg)

A graph-based campus navigation application developed in **C++17** using Object-Oriented Programming concepts.

</div>

<div align="center">

# Smart Campus Navigation and Route Optimization System

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![OOP](https://img.shields.io/badge/Paradigm-OOP-orange.svg)
![Institution](https://img.shields.io/badge/IIIT-Bhubaneswar-purple.svg)

A graph-based campus navigation application developed in **C++17** using Object-Oriented Programming concepts.

</div>

---

The application models a logical representation of the IIIT Bhubaneswar campus, calculates routes between locations using Dijkstra's algorithm, and allows administrators to manage pathways and temporary closures.

## Project Overview

The campus is represented as an **undirected weighted graph**:

- Each campus location is a vertex represented by a `Location` object.
- Each connecting pathway is an edge represented by a `Path` object.
- Each edge stores its endpoint IDs, physical distance, availability status and optional blockage reason.
- The `Campus` class manages the graph, route calculation, administrative operations and file persistence.

The supplied dataset contains **22 campus locations and 31 initial pathways**.

---

## Features

### User Operations
- View the logical campus map.
- Explore the campus location directory.
- Search for locations by ID or name.
- View campus statistics.
- Display available pathways and their statuses.
- Find routes between two campus locations.

### Route Optimization
The system uses **Dijkstra's shortest-path algorithm** and provides two route-selection modes:

1. **Shortest Distance:** Minimizes the total physical distance in metres.
2. **Fastest Estimated Time:** Minimizes estimated traversal time using assumed walking speeds:
   - 1.2 m/s for pathways shorter than 150 metres.
   - 1.5 m/s for pathways of 150 metres or more.

Blocked pathways are excluded from route calculation. If a pathway becomes unavailable, the algorithm can find an alternative route when one exists.

### Administrative Operations
The administrator interface provides:

- Add a new pathway.
- Edit an existing pathway's distance.
- Remove a pathway.
- Block a pathway with a reason.
- Restore a blocked pathway.
- View all pathways and their statuses.

Path management operations validate inputs and update the corresponding data files.

---

## Object-Oriented Design

The project is organized around three main classes:

| Class | Responsibility |
| :--- | :--- |
| `Location` | Stores campus location details such as ID, name, category and description. |
| `Path` | Represents a connection between two locations, including distance and blockage information. |
| `Campus` | Coordinates campus data, route calculation, path management and persistence. |

OOP concepts demonstrated:

- **Encapsulation:** Private data members with controlled public access.
- **Abstraction:** Public operations hide internal graph and file-handling details.
- **Composition:** `Campus` contains vectors of `Location` and `Path` objects.
- **Constructors:** Initialize objects with their required data.
- **Const correctness:** Read-only operations use const-qualified member functions.
- **Operator overloading:** A friend `operator<<` overload allows `Location` objects to be printed using the output stream operator.

---

## Graph Algorithm

Dijkstra's algorithm is used to calculate the minimum-cost route.

For shortest-distance mode, the edge cost is the pathway distance.

For fastest-estimated-time mode:

$$\text{Edge Cost}=\frac{\text{Distance}}{\text{Assumed Speed}}$$

The algorithm maintains:
- A distance vector for tentative minimum costs.
- A predecessor vector for route reconstruction.
- A visited vector to track processed locations.

The current implementation stores connections in a `std::vector<Path>` and scans this collection during edge relaxation.

> **Time Complexity:** $O(V^2+VE)$  
> **Auxiliary Space Complexity:** $O(V)$  
> *where $V$ is the number of locations and $E$ is the number of pathways.*

---

## File Persistence

The application uses two local text files:

| File | Format | Purpose |
| :--- | :--- | :--- |
| `paths.txt` | `fromId|toId|distance` | Stores the pathway connections and distances. |
| `path_status.txt` | `fromId|toId|reason` | Stores blocked pathways and their reasons. |

The `Campus` constructor loads the location catalogue, pathway data and saved blockage information during startup.

Administrative changes are saved locally, allowing pathway updates and blockage statuses to persist across application restarts.

---

## Project Structure

```text
SmartCampusNav/
│
├── main.cpp
├── paths.txt
├── path_status.txt
├── README.md
│
└── src/
    ├── Campus.h
    ├── Campus.cpp
    ├── Location.h
    ├── Location.cpp
    ├── Path.h
    └── Path.cpp
```

---

## Compilation and Execution

### Requirements
- C++ compiler supporting C++17.
- GCC / MinGW recommended.

### Compile
Run the following command from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp src/Location.cpp src/Path.cpp src/Campus.cpp -o SmartCampusNav
```

### Run

**On Windows:**
```powershell
.\SmartCampusNav.exe
```

**On Linux:**
```bash
./SmartCampusNav
```

> **Note:** Run the executable from the project root so that the application can locate `paths.txt` and `path_status.txt`.

---

## Demonstration Scenario

A sample route is calculated from **Hostel E (ID 12)** to **Open Recreation Ground (ID 22)**.

- With all pathways open, the shortest route is:  
  `12 → 13 → 14 → 22`  
  **Total distance:** **245 metres**

- If the pathway between Hostel F (ID 13) and Hostel G (ID 14) is blocked, an alternative route is:  
  `12 → 11 → 8 → 22`  
  **Total distance:** **335 metres**

This demonstrates how pathway availability affects route calculation and allows the application to adapt to temporary closures.

---

## Limitations

- The application uses a terminal-based interface.
- The campus map is a logical schematic, not a geographically scaled map.
- Distances are supplied through local data files.
- Travel times are estimates based on assumed walking speeds.
- No GPS, live traffic sensing, cloud synchronization or mobile interface is implemented.
- Administrator credentials are hard-coded and intended only for demonstration purposes.

---

## Future Enhancements

Possible extensions include:
- A graphical campus map.
- GPS integration and surveyed campus coordinates.
- Accessibility-aware route selection.
- Secure administrator authentication.
- Database-backed persistence.
- Automated unit and integration testing.

---

## Academic Context

- **Project:** Smart Campus Navigation and Route Optimization System  
- **Course:** Object-Oriented Programming (OOPS)  
- **Institution:** International Institute of Information Technology, Bhubaneswar  
- **Academic Session:** 2026–27  

- **Developed by:** Preetika Mishra  
- **Branch:** CSE-B | **Semester:** 3rd Semester  

- **Submitted to:** Dr. Srichandan Sobhanayak  

---

> *This project is an academic implementation demonstrating object-oriented design, graph representation, shortest-path algorithms and file handling in C++.*