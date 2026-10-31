
#ifndef CAMPUS_H
#define CAMPUS_H

#include <string>
#include <vector>
#include "Location.h"
#include "Path.h"

class Campus
{
private:
    std::vector<Location> locations;
    std::vector<Path> paths;

    void loadLocations();
    void loadPaths();
    void loadPathStatuses();

    bool savePaths() const;
    bool savePathStatuses() const;

    const Location* findLocation(int id) const;
    static std::string toLower(std::string text);

public:
    Campus();

    void displayLocations() const;
    void searchByName(std::string keyword) const;
    void searchById(int id) const;
    void displayMap() const;
    void displayStatistics() const;

    bool hasBlockedPaths() const;

    void displayPaths(bool showBlockedOnly = false,
                      bool showOpenOnly = false) const;

    bool addPath(int fromId, int toId, double distance);
    bool editPathDistance(int fromId, int toId, double newDistance);
    bool removePath(int fromId, int toId);

    bool blockPath(int fromId, int toId, const std::string& reason);
    bool restorePath(int fromId, int toId);

    void findRoute(int sourceId, int destinationId, bool fastest = false) const;
};

#endif