
#include "RailwaySystem.h"


int main() {
    vector<Train> trains;
    vector<Coach> coaches;
    int choice;

    loadTrains(trains);
    loadCoaches(coaches);


    do {
        cout << "\n===== RAILEASE RAILWAY SIMULATION SYSTEM =====\n";
        cout << "1. Train Management\n";
        cout << "2. Coach Management\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
               trainMenu(trains, coaches);
                break;

            case 2:
               coachMenu(trains, coaches);
                break;

            case 3:
                cout << "Exiting RAILEASE...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
