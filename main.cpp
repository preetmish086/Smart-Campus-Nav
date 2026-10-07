#include <iostream>
#include <string>
using namespace std;

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
    cout << "---------------------- MAIN MENU ---------------------------\n";
    cout << "  [1] Explore Campus\n";
    cout << "  [2] View Campus Map\n";
    cout << "  [3] Search Location\n";
    cout << "  [0] Exit\n";
    cout << "------------------------------------------------------------\n";
}

void showCampusMap()
{
    cout << "\n";
    cout << "                    IIIT BHUBANESWAR\n";
    cout << "                      CAMPUS MAP\n\n";

    cout << "                    +-----------+\n";
    cout << "                    |  HOSTEL D  |\n";
    cout << "                    +-----+-----+\n";
    cout << "                          |\n";
    cout << "                          |\n";
    cout << "              +-----------+-----------+\n";
    cout << "              |                       |\n";
    cout << "        +-----+------+          +-----+------+\n";
    cout << "        | SPORTS AREA |          |  HOSTEL E  |\n";
    cout << "        +-----+------+          +-----+------+\n";
    cout << "              |                       |\n";
    cout << "              +-----------+-----------+\n";
    cout << "                          |\n";
    cout << "                   +------+------+\n";
    cout << "                   |STUDENT      |\n";
    cout << "                   |CENTRE       |\n";
    cout << "                   +------+------+\n";
    cout << "                          |\n";
    cout << "                +---------+---------+\n";
    cout << "                |                   |\n";
    cout << "         +------+-------+    +------+------+\n";
    cout << "         | ACADEMIC     |    |   LIBRARY   |\n";
    cout << "         | BLOCK        |    |             |\n";
    cout << "         +--------------+    +-------------+\n";
}

void exploreCampus()
{
    cout << "\n";
    cout << "------------------- CAMPUS LOCATIONS -----------------------\n";
    cout << "  1. Main Gate\n";
    cout << "  2. Academic Block\n";
    cout << "  3. Central Library\n";
    cout << "  4. Student Centre\n";
    cout << "  5. Sports Area\n";
    cout << "  6. Hostel D\n";
    cout << "  7. Hostel E\n";
    cout << "------------------------------------------------------------\n";
}

void searchLocation()
{
    string location;

    cout << "\nEnter location to search: ";
    getline(cin >> ws, location);

    cout << "\nSearching for \"" << location << "\"...\n";

    if (location == "Library" || location == "library")
    {
        cout << "\nLocation Found!\n";
        cout << "Name   : Central Library\n";
        cout << "Type   : Academic Facility\n";
        cout << "Status : Available\n";
    }
    else if (location == "Academic Block" || location == "academic block")
    {
        cout << "\nLocation Found!\n";
        cout << "Name   : Academic Block\n";
        cout << "Type   : Academic Building\n";
        cout << "Status : Available\n";
    }
    else
    {
        cout << "\nLocation not found in the current campus database.\n";
    }
}

int main()
{
    int choice;

    showHeader();

    do
    {
        showMainMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                exploreCampus();
                break;

            case 2:
                showCampusMap();
                break;

            case 3:
                searchLocation();
                break;

            case 0:
                cout << "\nThank you for using Smart Campus Navigation!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}