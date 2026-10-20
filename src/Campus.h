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

    void addPath(int from, int to, double distance);
    void loadLocations();
    void loadPaths();
    const Location* findLocation(int id) const;
    static std::string toLower(std::string text);

public:
    Campus();

    void displayLocations() const;
    void searchByName(std::string keyword) const;
    void searchById(int id) const;
    void displayMap() const;
    void displayStatistics() const;
    void displayPaths() const;
    bool blockPath(int fromId, int toId, const std::string& reason);
    bool restorePath(int fromId, int toId);
    void findRoute(int sourceId, int destinationId) const;
};

#endif
