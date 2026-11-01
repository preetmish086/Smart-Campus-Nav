#include "Campus.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <exception>
#include <cmath>
#include <string>

Campus::Campus()
{
    loadLocations();
    loadPaths();
    loadPathStatuses();
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
    std::ifstream file("paths.txt");

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open paths.txt\n";
        return;
    }

    // Build a temporary graph so invalid data is not
    // partially loaded into the actual campus graph.
    std::vector<Path> loadedPaths;
    std::string line;
    int lineNumber = 0;

    auto hasOnlyTrailingWhitespace =
        [](const std::string& text, std::size_t position)
    {
        while (position < text.size())
        {
            if (!std::isspace(
                    static_cast<unsigned char>(text[position])))
                return false;

            ++position;
        }

        return true;
    };

    while (std::getline(file, line))
    {
        ++lineNumber;

        // Ignore empty lines.
        if (line.find_first_not_of(" \t\r\n") ==
            std::string::npos)
            continue;

        // Each record must contain exactly two separators.
        std::size_t first = line.find('|');
        std::size_t second =
            (first == std::string::npos)
                ? std::string::npos
                : line.find('|', first + 1);

        if (first == std::string::npos ||
            second == std::string::npos ||
            line.find('|', second + 1) != std::string::npos)
        {
            std::cerr << "Invalid path record on line "
                      << lineNumber << ".\n";
            return;
        }

        std::string fromText = line.substr(0, first);
        std::string toText =
            line.substr(first + 1, second - first - 1);
        std::string distanceText = line.substr(second + 1);

        int fromId;
        int toId;
        double distance;

        try
        {
            std::size_t pos1, pos2, pos3;

            fromId = std::stoi(fromText, &pos1);
            toId = std::stoi(toText, &pos2);
            distance = std::stod(distanceText, &pos3);

            if (!hasOnlyTrailingWhitespace(fromText, pos1) ||
                !hasOnlyTrailingWhitespace(toText, pos2) ||
                !hasOnlyTrailingWhitespace(distanceText, pos3))
            {
                std::cerr << "Invalid value on line "
                          << lineNumber << ".\n";
                return;
            }
        }
        catch (const std::exception&)
        {
            std::cerr << "Invalid number on line "
                      << lineNumber << ".\n";
            return;
        }

        // Validate the connection before adding it.
        if (fromId == toId ||
            findLocation(fromId) == nullptr ||
            findLocation(toId) == nullptr ||
            !std::isfinite(distance) ||
            distance <= 0)
        {
            std::cerr << "Invalid location ID or distance on line "
                      << lineNumber << ".\n";
            return;
        }

        // A bidirectional connection must appear only once.
        for (const Path& existing : loadedPaths)
        {
            bool duplicate =
                (existing.getStartId() == fromId &&
                 existing.getEndId() == toId) ||
                (existing.getStartId() == toId &&
                 existing.getEndId() == fromId);

            if (duplicate)
            {
                std::cerr << "Duplicate path on line "
                          << lineNumber << ".\n";
                return;
            }
        }

        loadedPaths.emplace_back(fromId, toId, distance);
    }

    if (file.bad())
    {
        std::cerr << "Error while reading paths.txt\n";
        return;
    }

    // Accept the new graph only after the entire file is valid.
    paths.swap(loadedPaths);

    std::cout << "Loaded " << paths.size()
              << " paths from paths.txt\n";
}

bool Campus::savePaths() const
{
    std::ofstream file("paths.txt");

    if (!file.is_open())
    {
        std::cerr << "Error: Could not save paths.txt\n";
        return false;
    }

    for (const Path& path : paths)
    {
        file << path.getStartId() << '|'
             << path.getEndId() << '|'
             << path.getDistance() << '\n';
    }

    file.flush();

    if (!file.good())
    {
        std::cerr << "Error: Failed while writing paths.txt\n";
        return false;
    }

    return true;
}

bool Campus::addPath(int fromId, int toId, double distance)
{
    // Validate the two endpoints and distance.
    if (fromId == toId ||
        findLocation(fromId) == nullptr ||
        findLocation(toId) == nullptr ||
        !std::isfinite(distance) ||
        distance <= 0)
    {
        std::cout << "Invalid location IDs or distance.\n";
        return false;
    }

    // Connections are bidirectional, so check both orientations.
    for (const Path& path : paths)
    {
        bool sameConnection =
            (path.getStartId() == fromId &&
             path.getEndId() == toId) ||
            (path.getStartId() == toId &&
             path.getEndId() == fromId);

        if (sameConnection)
        {
            std::cout << "That connection already exists.\n";
            return false;
        }
    }

    paths.emplace_back(fromId, toId, distance);

    if (!savePaths())
    {
        paths.pop_back();
        std::cout << "Could not save the new path. Change cancelled.\n";
        return false;
    }

    return true;
}

bool Campus::editPathDistance(
    int fromId, int toId, double newDistance)
{
    if (!std::isfinite(newDistance) || newDistance <= 0)
    {
        std::cout << "Distance must be a positive, finite number.\n";
        return false;
    }

    for (Path& path : paths)
    {
        bool sameConnection =
            (path.getStartId() == fromId &&
             path.getEndId() == toId) ||
            (path.getStartId() == toId &&
             path.getEndId() == fromId);

        if (sameConnection)
        {
            double oldDistance = path.getDistance();
            path.setDistance(newDistance);

            if (!savePaths())
            {
                path.setDistance(oldDistance);
                std::cout << "Could not save the change. Distance restored.\n";
                return false;
            }

            return true;
        }
    }

    std::cout << "That connection does not exist.\n";
    return false;
}

bool Campus::removePath(int fromId, int toId)
{
    for (std::size_t i = 0; i < paths.size(); ++i)
    {
        bool sameConnection =
            (paths[i].getStartId() == fromId &&
             paths[i].getEndId() == toId) ||
            (paths[i].getStartId() == toId &&
             paths[i].getEndId() == fromId);

        if (sameConnection)
        {
            // Keep a copy in case a save fails and we need to roll back.
            Path removedPath = paths[i];
            paths.erase(paths.begin() + i);

            if (!savePaths())
            {
                paths.insert(paths.begin() + i, removedPath);
                std::cout << "Could not save the change. Path restored.\n";
                return false;
            }

            // Also remove any saved closure for this connection.
            if (!savePathStatuses())
            {
                paths.insert(paths.begin() + i, removedPath);
                savePaths();
                savePathStatuses();

                std::cout << "Could not update closure records. "
                          << "Path removal cancelled.\n";
                return false;
            }

            return true;
        }
    }

    std::cout << "That connection does not exist.\n";
    return false;
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

bool Campus::hasBlockedPaths() const
{
    for (const Path& path : paths)
    {
        if (path.isBlocked())
            return true;
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

void Campus::findRoute(int sourceId, int destinationId, bool fastest) const{
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

            // Shortest mode minimizes distance.
            // Fastest mode estimates travel time using assumed walking speeds.
            double assumedSpeed = 1.2;

            if (fastest && path.getDistance() >= 150.0)
            {
                assumedSpeed = 1.5;
            }

            double edgeCost = fastest
                ? path.getDistance() / assumedSpeed
                : path.getDistance();

            double newDistance = distance[current] + edgeCost;
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
    // Calculate the actual physical distance and estimated walking time
    // along the selected route.
    double totalDistance = 0.0;
    double estimatedSeconds = 0.0;

    for (std::size_t i = 0; i + 1 < route.size(); ++i)
    {
        int from = route[i];
        int to = route[i + 1];

        for (const Path& path : paths)
        {
            bool sameConnection =
                (path.getStartId() == from && path.getEndId() == to) ||
                (path.getStartId() == to && path.getEndId() == from);

            if (sameConnection)
            {
                double speed =
                    (path.getDistance() >= 150.0) ? 1.5 : 1.2;

                totalDistance += path.getDistance();
                estimatedSeconds += path.getDistance() / speed;
                break;
            }
        }
    }

    double estimatedMinutes = estimatedSeconds / 60.0;

    std::cout << "\n Route mode: "
          << (fastest ? "Fastest estimated time" : "Shortest distance")
          << "\n Total distance: " << totalDistance << " metres\n"
          << " Estimated walking time: " << estimatedMinutes << " minutes\n"
          << " (Approximate, based on assumed walking speeds)\n"
          << "============================================================\n";
}
