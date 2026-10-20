#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// ============================================================
// LOCATION CLASS
// Represents any searchable location on the campus.
// ============================================================

class Location
{
private:
    int id;
    string name;
    string category;
    string description;

public:
    // Constructor
    Location(int id, string name, string category, string description)
    {
        this->id = id;
        this->name = name;
        this->category = category;
        this->description = description;
    }

    // Getters
    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    string getCategory() const
    {
        return category;
    }

    string getDescription() const
    {
        return description;
    }

    // Display complete location information
    void displayDetails() const
    {
        cout << "\n";
        cout << "------------------------------------------------------------\n";
        cout << " Location ID   : " << id << "\n";
        cout << " Name          : " << name << "\n";
        cout << " Category      : " << category << "\n";
        cout << " Description   : " << description << "\n";
        cout << "------------------------------------------------------------\n";
    }
};


// ============================================================
// CAMPUS CLASS
// Stores and manages all campus locations.
// ============================================================

class Campus
{
private:
    vector<Location> locations;

public:

    // Constructor automatically loads the campus
    Campus()
    {
        loadLocations();
    }

    // --------------------------------------------------------
    // Add all campus locations
    // --------------------------------------------------------
    void loadLocations()
    {
        // Major campus facilities
        locations.push_back(
            Location(1, "Main Gate", "Entrance",
                     "Primary entrance and exit of the IIIT Bhubaneswar campus."));

        locations.push_back(
            Location(2, "Academic Block", "Academic",
                     "Main academic area containing classrooms and teaching spaces."));

        locations.push_back(
            Location(3, "Central Library", "Academic",
                     "Library containing books, journals and digital academic resources."));

        locations.push_back(
            Location(4, "Laboratory Complex", "Academic",
                     "Academic laboratory area used for practical and technical work."));

        locations.push_back(
            Location(5, "Administrative Block", "Administration",
                     "Administrative offices and institutional services."));

        locations.push_back(
            Location(6, "Auditorium", "Events",
                     "Major venue for seminars, cultural programmes and institute events."));

        locations.push_back(
            Location(7, "Guest House", "Accommodation",
                     "Guest accommodation facility within the campus."));

        locations.push_back(
            Location(8, "College Canteen", "Food",
                     "Campus dining and refreshment facility."));

        locations.push_back(
            Location(9, "Sports Complex", "Sports",
                     "Sports and recreational facilities for students."));

        locations.push_back(
            Location(10, "Shopping Area", "Utility",
                     "Campus shopping and essential student services area."));

        // Hostel blocks officially listed by IIIT Bhubaneswar
        locations.push_back(
            Location(11, "Hostel D", "Boys Hostel",
                     "Residential hostel block D."));

        locations.push_back(
            Location(12, "Hostel E", "Boys Hostel",
                     "Residential hostel block E."));

        locations.push_back(
            Location(13, "Hostel F", "Boys Hostel",
                     "Residential hostel block F."));

        locations.push_back(
            Location(14, "Hostel G", "Boys Hostel",
                     "Residential hostel block G."));

        locations.push_back(
            Location(15, "Hostel I", "Boys Hostel",
                     "Residential hostel block I."));

        locations.push_back(
            Location(16, "Hostel J", "Boys Hostel",
                     "Residential hostel block J."));

        locations.push_back(
            Location(17, "Hostel K", "Girls Hostel",
                     "Residential hostel block K."));

        locations.push_back(
            Location(18, "Hostel L", "Girls Hostel",
                     "Residential hostel block L."));

        locations.push_back(
            Location(19, "Hostel P", "Girls Hostel",
                     "Residential hostel block P."));

        locations.push_back(
            Location(20, "Hostel Q", "Girls Hostel",
                     "Residential hostel block Q."));

        // Additional navigation points
        locations.push_back(
            Location(21, "Main Parking Area", "Transport",
                     "Parking and vehicle access area near the campus entrance."));

        locations.push_back(
            Location(22, "Open Recreation Ground", "Recreation",
                     "Open campus space used for recreation and outdoor activities."));
    }

    // --------------------------------------------------------
    // Display all locations
    // --------------------------------------------------------
    void displayLocations() const
    {
        cout << "\n";
        cout << "===================== CAMPUS DIRECTORY =====================\n";

        for (const Location& location : locations)
        {
            cout << " [" << location.getId() << "] "
                 << location.getName()
                 << "  |  " << location.getCategory() << "\n";
        }

        cout << "============================================================\n";
    }

    // --------------------------------------------------------
    // Search using location name
    // --------------------------------------------------------
    void searchByName(string keyword) const
    {
        // Convert search text to lowercase
        transform(keyword.begin(), keyword.end(), keyword.begin(),
                  [](unsigned char c)
                  {
                      return tolower(c);
                  });

        bool found = false;

        for (const Location& location : locations)
        {
            string name = location.getName();

            transform(name.begin(), name.end(), name.begin(),
                      [](unsigned char c)
                      {
                          return tolower(c);
                      });

            // Partial matching
            if (name.find(keyword) != string::npos)
            {
                location.displayDetails();
                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo matching location found.\n";
        }
    }

    // --------------------------------------------------------
    // Search using location ID
    // --------------------------------------------------------
    void searchById(int id) const
    {
        for (const Location& location : locations)
        {
            if (location.getId() == id)
            {
                location.displayDetails();
                return;
            }
        }

        cout << "\nNo location exists with ID " << id << ".\n";
    }

    // --------------------------------------------------------
    // Display visual campus map
    // --------------------------------------------------------
    void displayMap() const
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                IIIT BHUBANESWAR CAMPUS\n";
        cout << "                  LOGICAL NAVIGATION MAP\n";
        cout << "============================================================\n\n";

        cout << "                         [MAIN GATE]\n";
        cout << "                              |\n";
        cout << "                 +------------+------------+\n";
        cout << "                 |                         |\n";
        cout << "          [PARKING AREA]              [ADMIN BLOCK]\n";
        cout << "                 |                         |\n";
        cout << "                 +------------+------------+\n";
        cout << "                              |\n";
        cout << "                      [ACADEMIC BLOCK]\n";
        cout << "                              |\n";
        cout << "                 +------------+------------+\n";
        cout << "                 |                         |\n";
        cout << "          [LABORATORY COMPLEX]       [LIBRARY]\n";
        cout << "                 |                         |\n";
        cout << "                 +------------+------------+\n";
        cout << "                              |\n";
        cout << "                       [STUDENT ZONE]\n";
        cout << "                              |\n";
        cout << "              +---------------+---------------+\n";
        cout << "              |               |               |\n";
        cout << "         [CANTEEN]       [AUDITORIUM]    [SPORTS]\n";
        cout << "              |                               |\n";
        cout << "              +---------------+---------------+\n";
        cout << "                              |\n";
        cout << "                        HOSTEL ZONE\n";
        cout << "                              |\n";
        cout << "        +--------+--------+---+---+--------+--------+\n";
        cout << "        |        |        |       |        |        |\n";
        cout << "      [D]      [E]      [F]     [G]      [I]      [J]\n";
        cout << "        |        |        |       |        |        |\n";
        cout << "        +--------+--------+---+---+--------+--------+\n";
        cout << "                              |\n";
        cout << "                 +------------+------------+\n";
        cout << "                 |            |            |\n";
        cout << "               [K]          [L]          [P/Q]\n";
        cout << "\n";
        cout << "  * This is a logical navigation representation,\n";
        cout << "    not a claim of exact physical GPS geometry.\n";
        cout << "============================================================\n";
    }

    // --------------------------------------------------------
    // Campus information
    // --------------------------------------------------------
    void displayStatistics() const
    {
        cout << "\n";
        cout << "=================== CAMPUS STATISTICS ======================\n";
        cout << " Total mapped locations : " << locations.size() << "\n";
        cout << " Academic facilities    : 4+\n";
        cout << " Hostel blocks          : 10\n";
        cout << " Sports / recreation    : Available\n";
        cout << " Navigation status      : Online\n";
        cout << " Route engine           : Coming in next milestone\n";
        cout << "============================================================\n";
    }
};


// ============================================================
// USER INTERFACE
// ============================================================

void showHeader()
{
    cout << "\n";
    cout << "============================================================\n";
    cout << "                 IIIT BHUBANESWAR\n";
    cout << "          SMART CAMPUS NAVIGATION SYSTEM\n";
    cout << "============================================================\n";
}

void showMainMenu()
{
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                      MAIN MENU                           |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|  [1] View Campus Map                                     |\n";
    cout << "|  [2] Explore Campus Directory                            |\n";
    cout << "|  [3] Search Location                                     |\n";
    cout << "|  [4] Campus Statistics                                   |\n";
    cout << "|  [0] Exit                                                |\n";
    cout << "+----------------------------------------------------------+\n";
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    Campus campus;

    int choice;

    showHeader();

    do
    {
        showMainMenu();

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                campus.displayMap();
                break;

            case 2:
                campus.displayLocations();
                break;

            case 3:
            {
                int searchChoice;

                cout << "\n";
                cout << "------------------- SEARCH LOCATION ------------------------\n";
                cout << " [1] Search by Name\n";
                cout << " [2] Search by ID\n";
                cout << "------------------------------------------------------------\n";

                cout << "Enter choice: ";
                cin >> searchChoice;

                if (searchChoice == 1)
                {
                    string keyword;

                    cout << "Enter location name: ";
                    getline(cin >> ws, keyword);

                    campus.searchByName(keyword);
                }
                else if (searchChoice == 2)
                {
                    int id;

                    cout << "Enter location ID: ";
                    cin >> id;

                    campus.searchById(id);
                }
                else
                {
                    cout << "\nInvalid search option.\n";
                }

                break;
            }

            case 4:
                campus.displayStatistics();
                break;

            case 0:
                cout << "\nExiting Smart Campus Navigation...\n";
                cout << "Thank you!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}