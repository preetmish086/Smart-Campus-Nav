#include "Path.h"

Path::Path(int startId, int endId, double distance, bool blocked)
    : startId(startId), endId(endId), distance(distance), blocked(blocked)
{
}

int Path::getStartId() const { return startId; }
int Path::getEndId() const { return endId; }
double Path::getDistance() const { return distance; }
bool Path::isBlocked() const { return blocked; }
void Path::setBlocked(bool status) { blocked = status; }

// Since paths are bidirectional, return the opposite endpoint of this path.
int Path::getOtherEnd(int locationId) const
{
    if (locationId == startId) return endId;
    if (locationId == endId) return startId;
    return -1; // This path is not connected to the supplied location.
}
