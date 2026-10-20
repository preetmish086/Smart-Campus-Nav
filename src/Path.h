#ifndef PATH_H
#define PATH_H

#include <string>

class Path
{
private:
    int startId;
    int endId;
    double distance;
    bool blocked;
    std::string blockReason;

public:
    Path(int startId, int endId, double distance, bool blocked = false);

    int getStartId() const;
    int getEndId() const;
    double getDistance() const;
    bool isBlocked() const;
    void setBlocked(bool status, const std::string& reason = "");
    std::string getBlockReason() const;
    int getOtherEnd(int locationId) const;
};

#endif
