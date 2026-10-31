
#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>

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

    // Overload the output operator for Location objects.
    friend std::ostream& operator<<(std::ostream& out, const Location& location);
};

#endif