#ifndef PATH_H
#define PATH_H

class Path
{
private:
    int startId;
    int endId;
    double distance;
    bool blocked;

public:
    Path(int startId, int endId, double distance, bool blocked = false);

    int getStartId() const;
    int getEndId() const;
    double getDistance() const;
    bool isBlocked() const;
    void setBlocked(bool status);
    int getOtherEnd(int locationId) const;
};

#endif
