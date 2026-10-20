#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location
{
private:
    int id;
    std::string name;
    std::string category;
    std::string description;

public:
    Location(int id, std::string name, std::string category, std::string description);

    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    void displayDetails() const;
};

#endif
