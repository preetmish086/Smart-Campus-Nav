#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <exception>
#include "src/Campus.h"


int readInt(const std::string& prompt)
{
    std::string line;

    while (true)
    {
        std::cout << prompt;

        if (!std::getline(std::cin >> std::ws, line))
            return 0;

        try
        {
            std::size_t position;
            int value = std::stoi(line, &position);

            // Allow trailing spaces, but reject extra characters.
            while (position < line.size() &&
                   std::isspace(static_cast<unsigned char>(line[position])))
                ++position;

            if (position == line.size())
                return value;
        }
        catch (const std::exception&)
        {
            // Invalid input: display the message below.
        }

        std::cout << "Please enter a valid whole number.\n";
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
              << "|  [5] Find Route (Shortest/Fastest)                                |\n"
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

                std::cout << "\nChoose route mode:\n";
                std::cout << "1. Shortest Distance\n";
                std::cout << "2. Fastest Estimated Time\n";

                int choice = readInt("Enter choice: ");

                if (choice != 1 && choice != 2)
                {
                    std::cout << "Invalid route mode. Please choose 1 or 2.\n";
                    break;
                }

                campus.findRoute(source, destination, choice == 2);
                break;
            }
            case 6:
                campus.displayPaths();
                break;
            case 7:
            {
                std::string username, password;

                std::cout << "\n==================== ADMIN LOGIN ==========================\n";
                std::cout << "Username: ";
                std::getline(std::cin >> std::ws, username);

                std::cout << "Password: ";
                std::getline(std::cin >> std::ws, password);

                if (username != "admin" || password != "campus123")
                {
                    std::cout << "\nAccess denied. Incorrect admin credentials.\n";
                    break;
                }

                std::cout << "\nLogin successful. Welcome, Administrator.\n";

                int adminChoice;

                do
                {
                    std::cout << "\n==================== ADMIN CONTROLS =======================\n"
                              << " [1] Add a new path\n"
                              << " [2] Edit path distance\n"
                              << " [3] Remove a path\n"
                              << " [4] Block a path\n"
                              << " [5] Restore a path\n"
                              << " [6] View all paths and statuses\n"
                              << " [0] Return to main menu\n";

                    adminChoice = readInt("Enter choice: ");

                    if (adminChoice == 1)
                    {
                        campus.displayLocations();

                        int from = readInt("Enter first location ID: ");
                        int to = readInt("Enter second location ID: ");
                        double distance;

                        std::cout << "Enter distance in metres: ";

                        if (!(std::cin >> distance))
                        {
                            std::cin.clear();
                            std::cin.ignore(
                                std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid distance input.\n";
                            continue;
                        }

                        if (campus.addPath(from, to, distance))
                            std::cout << "Path added and saved successfully.\n";
                    }
                    else if (adminChoice == 2)
                    {
                        campus.displayPaths();

                        int from = readInt("Enter first location ID: ");
                        int to = readInt("Enter second location ID: ");
                        double distance;

                        std::cout << "Enter the new distance in metres: ";

                        if (!(std::cin >> distance))
                        {
                            std::cin.clear();
                            std::cin.ignore(
                                std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid distance input.\n";
                            continue;
                        }

                        if (campus.editPathDistance(from, to, distance))
                            std::cout << "Path distance updated successfully.\n";
                    }
                    else if (adminChoice == 3)
                    {
                        campus.displayPaths();

                        int from = readInt("Enter first location ID: ");
                        int to = readInt("Enter second location ID: ");

                        std::cout << "Remove the connection between these locations? (y/n): ";
                        char confirmation;
                        std::cin >> confirmation;

                        if (confirmation == 'y' || confirmation == 'Y')
                        {
                            if (campus.removePath(from, to))
                                std::cout << "Path removed successfully.\n";
                        }
                        else
                        {
                            std::cout << "Path removal cancelled.\n";
                        }
                    }
                    else if (adminChoice == 4)
                    {
                        campus.displayPaths(false, true);

                        int from = readInt("Enter first location ID: ");
                        int to = readInt("Enter second location ID: ");

                        std::string reason;

                        do
                        {
                            std::cout << "Enter reason for closure: ";
                            std::getline(std::cin >> std::ws, reason);

                            if (reason.find_first_not_of(" \t\r\n") ==
                                std::string::npos)
                            {
                                std::cout << "Closure reason cannot be empty. "
                                          << "Please try again.\n";
                            }
                        }
                        while (reason.find_first_not_of(" \t\r\n") ==
                               std::string::npos);

                        if (campus.blockPath(from, to, reason))
                            std::cout << "Path blocked. New route searches will avoid this connection.\n";
                        else
                            std::cout << "Could not block path. Check that the connection exists and is open.\n";
                    }
                    else if (adminChoice == 5)
                    {
                        if (!campus.hasBlockedPaths())
                        {
                            std::cout << "\nThere are currently no blocked paths to restore.\n";
                            break;
                        }
                        campus.displayPaths(true, false);

                        int from = readInt("Enter first location ID: ");
                        int to = readInt("Enter second location ID: ");

                        if (campus.restorePath(from, to))
                            std::cout << "Path restored successfully.\n";
                        else
                            std::cout << "Could not restore path. Check that the connection exists and is blocked.\n";
                    }
                    else if (adminChoice == 6)
                    {
                        campus.displayPaths();
                    }
                    else if (adminChoice != 0)
                    {
                        std::cout << "Invalid admin option.\n";
                    }

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
