#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// Represents one searchable place on campus.
class Location
{
private:
    int id;
    string name;
    string category;
    string description;

public:
    Location(int id, string name, string category, string description)
        : id(id), name(name), category(category), description(description) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    string getDescription() const { return description; }

    void displayDetails() const
    {
        cout << "\n------------------------------------------------------------\n"
             << " Location ID   : " << id << "\n"
             << " Name          : " << name << "\n"
             << " Category      : " << category << "\n"
             << " Description   : " << description << "\n"
             << "------------------------------------------------------------\n";
    }
};

// Represents a walkable connection between two campus locations.
// Distances are illustrative values for this logical campus model.
class Path
{
private:
    int startId;
    int endId;
    double distance;
    bool blocked;

public:
    Path(int startId, int endId, double distance, bool blocked = false)
        : startId(startId), endId(endId), distance(distance), blocked(blocked) {}

    int getStartId() const { return startId; }
    int getEndId() const { return endId; }
    double getDistance() const { return distance; }
    bool isBlocked() const { return blocked; }

    // A path can be closed or reopened by changing its status.
    void setBlocked(bool status) { blocked = status; }

    int getOtherEnd(int locationId) const
    {
        if (locationId == startId) return endId;
        if (locationId == endId) return startId;
        return -1;
    }
};

class Campus
{
private:
    vector<Location> locations;
    vector<Path> paths;

    void addPath(int from, int to, double distance)
    {
        paths.push_back(Path(from, to, distance));
    }

    void loadLocations()
    {
        locations.push_back(Location(1, "Main Gate", "Entrance", "Primary entrance and exit of the IIIT Bhubaneswar campus."));
        locations.push_back(Location(2, "Academic Block", "Academic", "Main academic area containing classrooms and teaching spaces."));
        locations.push_back(Location(3, "Central Library", "Academic", "Library containing books, journals and digital academic resources."));
        locations.push_back(Location(4, "Laboratory Complex", "Academic", "Academic laboratory area used for practical and technical work."));
        locations.push_back(Location(5, "Administrative Block", "Administration", "Administrative offices and institutional services."));
        locations.push_back(Location(6, "Auditorium", "Events", "Venue for seminars, cultural programmes and institute events."));
        locations.push_back(Location(7, "Guest House", "Accommodation", "Guest accommodation facility within the campus."));
        locations.push_back(Location(8, "College Canteen", "Food", "Campus dining and refreshment facility."));
        locations.push_back(Location(9, "Sports Complex", "Sports", "Sports and recreational facilities for students."));
        locations.push_back(Location(10, "Shopping Area", "Utility", "Campus shopping and essential student services area."));
        locations.push_back(Location(11, "Hostel D", "Boys Hostel", "Residential hostel block D."));
        locations.push_back(Location(12, "Hostel E", "Boys Hostel", "Residential hostel block E."));
        locations.push_back(Location(13, "Hostel F", "Boys Hostel", "Residential hostel block F."));
        locations.push_back(Location(14, "Hostel G", "Boys Hostel", "Residential hostel block G."));
        locations.push_back(Location(15, "Hostel I", "Boys Hostel", "Residential hostel block I."));
        locations.push_back(Location(16, "Hostel J", "Boys Hostel", "Residential hostel block J."));
        locations.push_back(Location(17, "Hostel K", "Girls Hostel", "Residential hostel block K."));
        locations.push_back(Location(18, "Hostel L", "Girls Hostel", "Residential hostel block L."));
        locations.push_back(Location(19, "Hostel P", "Girls Hostel", "Residential hostel block P."));
        locations.push_back(Location(20, "Hostel Q", "Girls Hostel", "Residential hostel block Q."));
        locations.push_back(Location(21, "Main Parking Area", "Transport", "Parking and vehicle access area near the campus entrance."));
        locations.push_back(Location(22, "Open Recreation Ground", "Recreation", "Open campus space used for recreation and outdoor activities."));
    }

    void loadPaths()
    {
        // Each connection is bidirectional. Values are illustrative distances in metres.
        addPath(1, 21, 80);
        addPath(1, 5, 140);
        addPath(1, 2, 220);
        addPath(21, 5, 100);
        addPath(5, 2, 120);
        addPath(2, 3, 90);
        addPath(2, 4, 110);
        addPath(3, 4, 75);
        addPath(3, 6, 160);
        addPath(4, 8, 180);
        addPath(5, 7, 130);
        addPath(7, 10, 100);
        addPath(6, 8, 95);
        addPath(6, 9, 170);
        addPath(8, 10, 85);
        addPath(8, 22, 120);
        addPath(9, 22, 90);
        addPath(10, 11, 140);
        addPath(11, 12, 45);
        addPath(12, 13, 50);
        addPath(13, 14, 45);
        addPath(14, 15, 70);
        addPath(15, 16, 50);
        addPath(16, 17, 160);
        addPath(17, 18, 45);
        addPath(18, 19, 65);
        addPath(19, 20, 45);
        addPath(20, 9, 190);
        addPath(14, 22, 150);
        addPath(11, 8, 170);
        addPath(17, 10, 130);
    }

    const Location* findLocation(int id) const
    {
        for (const Location& location : locations)
            if (location.getId() == id) return &location;
        return nullptr;
    }

    int findLocationIdByName(string name) const
    {
        name = toLower(name);
        for (const Location& location : locations)
            if (toLower(location.getName()) == name) return location.getId();
        return -1;
    }

    static string toLower(string text)
    {
        transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        return text;
    }

public:
    Campus()
    {
        loadLocations();
        loadPaths();
    }

    void displayLocations() const
    {
        cout << "\n===================== CAMPUS DIRECTORY =====================\n";
        for (const Location& location : locations)
            cout << " [" << location.getId() << "] " << location.getName()
                 << "  |  " << location.getCategory() << "\n";
        cout << "============================================================\n";
    }

    void searchByName(string keyword) const
    {
        keyword = toLower(keyword);
        bool found = false;
        for (const Location& location : locations)
        {
            if (toLower(location.getName()).find(keyword) != string::npos)
            {
                location.displayDetails();
                found = true;
            }
        }
        if (!found) cout << "\nNo matching location found.\n";
    }

    void searchById(int id) const
    {
        const Location* location = findLocation(id);
        if (location) location->displayDetails();
        else cout << "\nNo location exists with ID " << id << ".\n";
    }

    void displayMap() const
    {
        cout << "\n============================================================\n"
             << "                IIIT BHUBANESWAR CAMPUS\n"
             << "                  LOGICAL NAVIGATION MAP\n"
             << "============================================================\n\n"
             << "                         [MAIN GATE]\n"
             << "                              |\n"
             << "                 +------------+------------+\n"
             << "                 |                         |\n"
             << "          [PARKING AREA]              [ADMIN BLOCK]\n"
             << "                 |                         |\n"
             << "                 +------------+------------+\n"
             << "                              |\n"
             << "                      [ACADEMIC BLOCK]\n"
             << "                              |\n"
             << "                 +------------+------------+\n"
             << "                 |                         |\n"
             << "          [LABORATORY COMPLEX]       [LIBRARY]\n"
             << "                 |                         |\n"
             << "                 +------------+------------+\n"
             << "                              |\n"
             << "                       [STUDENT ZONE]\n"
             << "                              |\n"
             << "              +---------------+---------------+\n"
             << "              |               |               |\n"
             << "         [CANTEEN]       [AUDITORIUM]    [SPORTS]\n"
             << "              |                               |\n"
             << "              +---------------+---------------+\n"
             << "                              |\n"
             << "                        HOSTEL ZONE\n"
             << "\n  * Logical representation, not exact physical GPS geometry.\n"
             << "============================================================\n";
    }

    void displayStatistics() const
    {
        cout << "\n=================== CAMPUS STATISTICS ======================\n"
             << " Total mapped locations : " << locations.size() << "\n"
             << " Total mapped paths     : " << paths.size() << "\n"
             << " Hostel blocks          : 10\n"
             << " Navigation status      : Ready\n"
             << " Route algorithm        : Dijkstra's shortest path\n"
             << "============================================================\n";
    }

    void displayPaths() const
    {
        cout << "\n====================== CAMPUS PATHS ========================\n";
        for (const Path& path : paths)
        {
            const Location* start = findLocation(path.getStartId());
            const Location* end = findLocation(path.getEndId());
            if (start && end)
            {
                cout << " " << start->getName() << " <-> " << end->getName()
                     << " | " << path.getDistance() << " m | "
                     << (path.isBlocked() ? "BLOCKED" : "OPEN") << "\n";
            }
        }
        cout << "============================================================\n";
    }

    void findRoute(int sourceId, int destinationId) const
    {
        if (!findLocation(sourceId) || !findLocation(destinationId))
        {
            cout << "\nInvalid source or destination ID. Please choose IDs from the directory.\n";
            return;
        }
        if (sourceId == destinationId)
        {
            cout << "\nYou are already at " << findLocation(sourceId)->getName() << ".\n";
            return;
        }

        const double INF = numeric_limits<double>::infinity();
        vector<double> distance(23, INF);
        vector<int> previous(23, -1);
        vector<bool> visited(23, false);
        distance[sourceId] = 0;

        // Dijkstra: repeatedly choose the closest unvisited location.
        for (size_t count = 0; count < locations.size(); ++count)
        {
            int current = -1;
            double bestDistance = INF;
            for (const Location& location : locations)
            {
                int id = location.getId();
                if (!visited[id] && distance[id] < bestDistance)
                {
                    bestDistance = distance[id];
                    current = id;
                }
            }

            if (current == -1) break; // Remaining locations cannot be reached.
            if (current == destinationId) break;
            visited[current] = true;

            for (const Path& path : paths)
            {
                if (path.isBlocked()) continue;
                int neighbour = path.getOtherEnd(current);
                if (neighbour == -1 || visited[neighbour]) continue;

                double newDistance = distance[current] + path.getDistance();
                if (newDistance < distance[neighbour])
                {
                    distance[neighbour] = newDistance;
                    previous[neighbour] = current;
                }
            }
        }

        if (distance[destinationId] == INF)
        {
            cout << "\nNo available route connects these locations.\n";
            return;
        }

        vector<int> route;
        for (int at = destinationId; at != -1; at = previous[at])
            route.push_back(at);
        reverse(route.begin(), route.end());

        cout << "\n====================== ROUTE RESULT ========================\n";
        cout << " From       : " << findLocation(sourceId)->getName() << "\n";
        cout << " Destination: " << findLocation(destinationId)->getName() << "\n";
        cout << " Route      : ";
        for (size_t i = 0; i < route.size(); ++i)
        {
            if (i > 0) cout << " -> ";
            cout << findLocation(route[i])->getName();
        }
        cout << "\n Total distance: " << distance[destinationId] << " metres\n";
        cout << "============================================================\n";
    }
};

int readInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value) return value;
        cout << "Please enter a valid whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void showHeader()
{
    cout << "\n============================================================\n"
         << "                 IIIT BHUBANESWAR\n"
         << "          SMART CAMPUS NAVIGATION SYSTEM\n"
         << "============================================================\n";
}

void showMainMenu()
{
    cout << "\n+----------------------------------------------------------+\n"
         << "|                      MAIN MENU                           |\n"
         << "+----------------------------------------------------------+\n"
         << "|  [1] View Campus Map                                     |\n"
         << "|  [2] Explore Campus Directory                            |\n"
         << "|  [3] Search Location                                     |\n"
         << "|  [4] Campus Statistics                                   |\n"
         << "|  [5] Find Shortest Route                                 |\n"
         << "|  [6] View Campus Paths                                   |\n"
         << "|  [0] Exit                                                |\n"
         << "+----------------------------------------------------------+\n";
}

int main()
{
    Campus campus;
    showHeader();

    int choice;
    do
    {
        showMainMenu();
        choice = readInt("\nEnter your choice: ");

        switch (choice)
        {
            case 1:
                campus.displayMap();
                break;
            case 2:
                campus.displayLocations();
                break;
            case 3:
            {
                cout << "\n------------------- SEARCH LOCATION ------------------------\n"
                     << " [1] Search by Name\n [2] Search by ID\n";
                int searchChoice = readInt("Enter choice: ");
                if (searchChoice == 1)
                {
                    string keyword;
                    cout << "Enter location name: ";
                    getline(cin >> ws, keyword);
                    campus.searchByName(keyword);
                }
                else if (searchChoice == 2)
                    campus.searchById(readInt("Enter location ID: "));
                else
                    cout << "\nInvalid search option.\n";
                break;
            }
            case 4:
                campus.displayStatistics();
                break;
            case 5:
            {
                campus.displayLocations();
                int source = readInt("Enter SOURCE location ID: ");
                int destination = readInt("Enter DESTINATION location ID: ");
                campus.findRoute(source, destination);
                break;
            }
            case 6:
                campus.displayPaths();
                break;
            case 0:
                cout << "\nExiting Smart Campus Navigation...\nThank you!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}