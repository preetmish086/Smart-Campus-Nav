#include "Location.h"
#include <iostream>
#include <utility>

Location::Location(int id, std::string name, std::string category, std::string description)
    : id(id), name(std::move(name)), category(std::move(category)), description(std::move(description))
{
}

int Location::getId() const { return id; }
std::string Location::getName() const { return name; }
std::string Location::getCategory() const { return category; }
std::string Location::getDescription() const { return description; }

void Location::displayDetails() const
{
    std::cout << "\n------------------------------------------------------------\n"
              << " Location ID   : " << id << "\n"
              << " Name          : " << name << "\n"
              << " Category      : " << category << "\n"
              << " Description   : " << description << "\n"
              << "------------------------------------------------------------\n";
}
