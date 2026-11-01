
#include "Location.h"
#include <iostream>
#include <ostream>
#include <utility>

Location::Location(int id, std::string name, std::string category, std::string description)
    : id(id), name(std::move(name)), category(std::move(category)), description(std::move(description))
{
}

int Location::getId() const { return id; }
std::string Location::getName() const { return name; }
std::string Location::getCategory() const { return category; }
std::string Location::getDescription() const { return description; }

std::ostream& operator<<(std::ostream& out, const Location& location)
{
    out << "\n------------------------------------------------------------\n"
        << " Location ID   : " << location.id << "\n"
        << " Name          : " << location.name << "\n"
        << " Category      : " << location.category << "\n"
        << " Description   : " << location.description << "\n"
        << "------------------------------------------------------------\n";

    return out;
}

void Location::displayDetails() const
{
    std::cout << *this;
}