#include "Campus.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <exception>

Campus::Campus()
{
    loadLocations();
    loadPaths();
    loadPathStatuses();
}

void Campus::addPath(int from, int to, double distance)
{
    paths.push_back(Path(from, to, distance));
}

void Campus::loadLocations()
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

void Campus::loadPaths()
{
    // Illustrative distances in metres; every path is bidirectional.
    addPath(1, 21, 80);  addPath(1, 5, 140);  addPath(1, 2, 220);
    addPath(21, 5, 100); addPath(5, 2, 120); addPath(2, 3, 90);
    addPath(2, 4, 110);  addPath(3, 4, 75);  addPath(3, 6, 160);
    addPath(4, 8, 180);  addPath(5, 7, 130); addPath(7, 10, 100);
    addPath(6, 8, 95);   addPath(6, 9, 170); addPath(8, 10, 85);
    addPath(8, 22, 120); addPath(9, 22, 90); addPath(10, 11, 140);
    addPath(11, 12, 45); addPath(12, 13, 50); addPath(13, 14, 45);
    addPath(14, 15, 70); addPath(15, 16, 50); addPath(16, 17, 160);
    addPath(17, 18, 45); addPath(18, 19, 65); addPath(19, 20, 45);
    addPath(20, 9, 190); addPath(14, 22, 150); addPath(11, 8, 170);
    addPath(17, 10, 130);
}

void Campus::loadPathStatuses()
{
    std::ifstream file("path_status.txt");

    //No saved file yet? Start with every path open.
    if(!file.is_open())
        return;

    std::string line;

    while(std::getline(file, line))
    {
        std::size_t firstSeparator = line.find('|');
        if (firstSeparator == std::string::npos)
            continue;

        std::size_t secondSeparator =
            line.find('|', firstSeparator + 1);

        if (secondSeparator == std::string::npos)
            continue;

        try
        {
            int fromId = std::stoi(line.substr(0, firstSeparator));

            int toId = std::stoi(
                line.substr(firstSeparator + 1,
                            secondSeparator - firstSeparator - 1));

            std::string reason = line.substr(secondSeparator + 1);

            for (Path& path : paths)
            {
                bool sameConnection =
                    (path.getStartId() == fromId &&
                     path.getEndId() == toId) ||
                    (path.getStartId() == toId &&
                     path.getEndId() == fromId);

                if (sameConnection)
                {
                    path.setBlocked(true, reason);
                    break;
                }
            }
        }
        catch (const std::exception&)
        {
            // Ignore malformed records and continue loading.
        }
    }
}


bool Campus::savePathStatuses() const
{
    std::ofstream file("path_status.txt");

    if (!file.is_open())
    {
        std::cerr << "Error: Could not save path statuses.\n";
        return false;
    }

    for (const Path& path : paths)
    {
        if (path.isBlocked())
        {
            file << path.getStartId() << '|'
                 << path.getEndId() << '|'
                 << path.getBlockReason() << '\n';
        }
    }

    file.flush();

    if (!file.good())
    {
        std::cerr << "Error: Failed while writing path statuses.\n";
        return false;
    }

    return true;
}


const Location* Campus::findLocation(int id) const
{
    for (const Location& location : locations)
        if (location.getId() == id) return &location;
    return nullptr;
}

std::string Campus::toLower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

void Campus::displayLocations() const
{
    std::cout << "\n===================== CAMPUS DIRECTORY =====================\n";
    for (const Location& location : locations)
        std::cout << " [" << location.getId() << "] " << location.getName()
                  << "  |  " << location.getCategory() << "\n";
    std::cout << "============================================================\n";
}

void Campus::searchByName(std::string keyword) const
{
    keyword = toLower(keyword);
    bool found = false;
    for (const Location& location : locations)
    {
        if (toLower(location.getName()).find(keyword) != std::string::npos)
        {
            location.displayDetails();
            found = true;
        }
    }
    if (!found) std::cout << "\nNo matching location found.\n";
}

void Campus::searchById(int id) const
{
    const Location* location = findLocation(id);
    if (location) location->displayDetails();
    else std::cout << "\nNo location exists with ID " << id << ".\n";
}

void Campus::displayMap() const
{
    std::cout << "\n============================================================\n"
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
              << "                              |\n"
              << "                        HOSTEL ZONE\n"
              << "\n  * Logical representation, not exact physical GPS geometry.\n"
              << "============================================================\n";
}

void Campus::displayStatistics() const
{
    std::cout << "\n=================== CAMPUS STATISTICS ======================\n"
              << " Total mapped locations : " << locations.size() << "\n"
              << " Total mapped paths     : " << paths.size() << "\n"
              << " Hostel blocks          : 10\n"
              << " Navigation status      : Ready\n"
              << " Route algorithm        : Dijkstra's shortest path\n"
              << "============================================================\n";
}

void Campus::displayPaths(bool showBlockedOnly, bool showOpenOnly) const
{
    std::cout << "\n====================== CAMPUS PATHS ========================\n";

    bool found = false;

    for (const Path& path : paths)
    {
        if (showBlockedOnly && !path.isBlocked())
            continue;

        if (showOpenOnly && path.isBlocked())
            continue;

        const Location* start = findLocation(path.getStartId());
        const Location* end = findLocation(path.getEndId());

        if (start && end)
        {
            std::cout << " [" << start->getId() << "] " << start->getName()
                      << " <-> [" << end->getId() << "] " << end->getName()
                      << " | " << path.getDistance() << " m | "
                      << (path.isBlocked() ? "BLOCKED" : "OPEN");

            if (path.isBlocked() && !path.getBlockReason().empty())
                std::cout << " | Reason: " << path.getBlockReason();

            std::cout << "\n";
            found = true;
        }
    }

    if (!found)
        std::cout << " No paths match this filter.\n";

    std::cout << "============================================================\n";
}

bool Campus::blockPath(int fromId, int toId, const std::string& reason)
{
    for (Path& path : paths)
    {
        bool sameConnection =
            (path.getStartId() == fromId && path.getEndId() == toId) ||
            (path.getStartId() == toId && path.getEndId() == fromId);

        if (sameConnection)
        {
            if (path.isBlocked()) return false;

            path.setBlocked(true, reason);

            if (!savePathStatuses())
            {
                path.setBlocked(false);
                return false;
            }

            return true;
        }
    }
    return false;
}

bool Campus::restorePath(int fromId, int toId)
{
    for (Path& path : paths)
    {
        bool sameConnection =
            (path.getStartId() == fromId && path.getEndId() == toId) ||
            (path.getStartId() == toId && path.getEndId() == fromId);

        if (sameConnection)
        {
            if (!path.isBlocked()) return false;
            
            std::string previousReason = path.getBlockReason();
            path.setBlocked(false);

            if (!savePathStatuses())
            {
                path.setBlocked(true, previousReason);
                return false;
            }

            return true;
        }
    }
    return false;
}

void Campus::findRoute(int sourceId, int destinationId) const
{
    if (!findLocation(sourceId) || !findLocation(destinationId))
    {
        std::cout << "\nInvalid source or destination ID. Please choose IDs from the directory.\n";
        return;
    }
    if (sourceId == destinationId)
    {
        std::cout << "\nYou are already at " << findLocation(sourceId)->getName() << ".\n";
        return;
    }

    const double INF = std::numeric_limits<double>::infinity();
    // IDs currently run from 1 to locations.size(), so the ID can index these vectors.
    std::vector<double> distance(locations.size() + 1, INF);
    std::vector<int> previous(locations.size() + 1, -1);
    std::vector<bool> visited(locations.size() + 1, false);
    distance[sourceId] = 0;

    // Dijkstra: repeatedly choose the unvisited location with the smallest known distance.
    for (std::size_t count = 0; count < locations.size(); ++count)
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

        if (current == -1) break;
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
        std::cout << "\nNo available route connects these locations.\n";
        return;
    }

    std::vector<int> route;
    for (int at = destinationId; at != -1; at = previous[at])
        route.push_back(at);
    std::reverse(route.begin(), route.end());

    std::cout << "\n====================== ROUTE RESULT ========================\n"
              << " From       : " << findLocation(sourceId)->getName() << "\n"
              << " Destination: " << findLocation(destinationId)->getName() << "\n"
              << " Route      : ";
    for (std::size_t i = 0; i < route.size(); ++i)
    {
        if (i > 0) std::cout << " -> ";
        std::cout << findLocation(route[i])->getName();
    }
    std::cout << "\n Total distance: " << distance[destinationId] << " metres\n"
              << "============================================================\n";
}
