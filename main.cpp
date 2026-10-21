#include <iostream>
#include <limits>
#include <string>
#include "src/Campus.h"

int readInt(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cout << "Please enter a valid whole number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void showHeader()
{
    std::cout << "\n============================================================\n"
              << "                 IIIT BHUBANESWAR\n"
              << "          SMART CAMPUS NAVIGATION SYSTEM\n"
              << "============================================================\n";
}

void showMainMenu()
{
    std::cout << "\n+----------------------------------------------------------+\n"
              << "|                      MAIN MENU                           |\n"
              << "+----------------------------------------------------------+\n"
              << "|  [1] View Campus Map                                     |\n"
              << "|  [2] Explore Campus Directory                            |\n"
              << "|  [3] Search Location                                     |\n"
              << "|  [4] Campus Statistics                                   |\n"
              << "|  [5] Find Shortest Route                                 |\n"
              << "|  [6] View Campus Paths                                   |\n"
              << "|  [7] Admin: Manage Path Closures                         |\n"
              << "|  [0] Exit                                                |\n"
              << "+----------------------------------------------------------+\n";
}

int main()
{
    Campus campus;
    showHeader();
    int choice;

    do
    {
        showMainMenu();
        choice = readInt("\nEnter your choice: ");

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
                std::cout << "\n------------------- SEARCH LOCATION ------------------------\n"
                          << " [1] Search by Name\n [2] Search by ID\n";
                int searchChoice = readInt("Enter choice: ");
                if (searchChoice == 1)
                {
                    std::string keyword;
                    std::cout << "Enter location name: ";
                    std::getline(std::cin >> std::ws, keyword);
                    campus.searchByName(keyword);
                }
                else if (searchChoice == 2)
                    campus.searchById(readInt("Enter location ID: "));
                else
                    std::cout << "\nInvalid search option.\n";
                break;
            }
            case 4:
                campus.displayStatistics();
                break;
            case 5:
            {
                campus.displayLocations();
                int source = readInt("Enter SOURCE location ID: ");
                int destination = readInt("Enter DESTINATION location ID: ");
                campus.findRoute(source, destination);
                break;
            }
            case 6:
                campus.displayPaths();
                break;
            case 7:
            {
                int adminChoice;
                do
                {
                    std::cout << "\n==================== ADMIN CONTROLS =======================\n"
                              << " [1] Block a path\n"
                              << " [2] Restore a path\n"
                              << " [3] View all paths and statuses\n"
                              << " [0] Return to main menu\n";
                    adminChoice = readInt("Enter choice: ");

                    if (adminChoice == 1)
                    {
                        campus.displayPaths(false, true);
                        int from = readInt("Enter first location ID: ");
                        int to = readInt("Enter second location ID: ");
                        std::string reason;
                        std::cout << "Enter reason for closure: ";
                        std::getline(std::cin >> std::ws, reason);
                        if (campus.blockPath(from, to, reason))
                            std::cout << "Path blocked. New route searches will avoid this connection.\n";
                        else
                            std::cout << "Could not block path. Check that the connection exists and is currently open.\n";
                    }
                    else if (adminChoice == 2)
                    {
                        campus.displayPaths(true, false);
                        int from = readInt("Enter first location ID: ");
                        int to = readInt("Enter second location ID: ");
                        if (campus.restorePath(from, to))
                            std::cout << "Path restored and available for future route searches.\n";
                        else
                            std::cout << "Could not restore path. Check that the connection exists and is currently blocked.\n";
                    }
                    else if (adminChoice == 3)
                        campus.displayPaths();
                    else if (adminChoice != 0)
                        std::cout << "Invalid admin option.\n";
                } while (adminChoice != 0);
                break;
            }
            case 0:
                std::cout << "\nExiting Smart Campus Navigation...\nThank you!\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
