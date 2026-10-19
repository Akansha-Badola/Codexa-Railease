
#include "RailwaySystem.h"

Coach::Coach() {
    coachNumber = 0;
    trainNumber = 0;
    totalSeats = 0;
    availableSeats = 0;
    coachType = "";
}
Coach::Coach(int number, int trainNo, string type, int seats) {
    coachNumber = number;
    trainNumber = trainNo;
    coachType = type;
    totalSeats = seats;
    availableSeats = seats;
}

void Coach::display() const {
    cout << "\nCoach Number: " << coachNumber;
    cout << "\nCoach Type: " << coachType;
    cout << "\nTotal Seats: " << totalSeats;
    cout << "\nAvailable Seats: " << availableSeats << "\n";
}

void saveCoaches(const vector<Coach>& coaches) {
    ofstream file("coaches.txt");

    for (int i = 0; i < coaches.size(); i++) {
        file << coaches[i].coachNumber << " "
             << coaches[i].trainNumber << " "
             << coaches[i].coachType << " "
             << coaches[i].totalSeats << " "
             << coaches[i].availableSeats << "\n";
    }

    file.close();
}

void loadCoaches(vector<Coach>& coaches) {
    ifstream file("coaches.txt");
    Coach c;

    while (file >> c.coachNumber
                >> c.trainNumber
                >> c.coachType
                >> c.totalSeats
                >> c.availableSeats) {
        coaches.push_back(c);
    }

    file.close();
}


void coachMenu(vector<Train>& trains, vector<Coach>& coaches) {
    int choice, number, seats;
    string type;
    bool found;

    do {
        cout << "\n===== COACH MANAGEMENT =====\n";
        cout << "1. Add Coach\n";
        cout << "2. Search Coach\n";
        cout << "3. Update Available Seats\n";
        cout << "4. Display All Coaches\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

case 1: {
    int trainNo;
    bool trainFound = false;

    cout << "Enter coach number: ";
    cin >> number;

    cout << "Enter train number this coach belongs to: ";
    cin >> trainNo;

    found = false;

    for (int i = 0; i < coaches.size(); i++) {
        if (coaches[i].coachNumber == number &&
            coaches[i].trainNumber == trainNo) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "This coach number already exists for this train.\n";
        break;
    }

    for (int i = 0; i < trains.size(); i++) {
        if (trains[i].trainNumber == trainNo) {
            trainFound = true;
            break;
        }
    }

    if (!trainFound) {
        cout << "Train not found. Add the train first.\n";
        break;
    }

    cout << "Enter coach type (Sleeper/AC3/AC2/AC1): ";
    cin >> type;

    cout << "Enter total seats: ";
    cin >> seats;

    if (seats <= 0) {
        cout << "Seats must be greater than zero.\n";
        break;
    }

    coaches.push_back(Coach(number, trainNo, type, seats));
    saveCoaches(coaches);

    cout << "Coach added successfully.\n";
    break;
}


            case 2:
                cout << "Enter coach number to search: ";
                cin >> number;

                found = false;

                for (int i = 0; i < coaches.size(); i++) {
                    if (coaches[i].coachNumber == number) {
                        coaches[i].display();
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Coach not found.\n";
                break;

            case 3:
                cout << "Enter coach number: ";
                cin >> number;

                found = false;

                for (int i = 0; i < coaches.size(); i++) {
                    if (coaches[i].coachNumber == number) {
                        cout << "Enter available seats (0-"
                             << coaches[i].totalSeats << "): ";
                        cin >> seats;

                        if (seats < 0 ||
                            seats > coaches[i].totalSeats) {
                            cout << "Invalid seat count.\n";
                        } else {
                            coaches[i].availableSeats = seats;
                        saveCoaches(coaches);
                        cout << "Seats updated successfully.\n";
                        }

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Coach not found.\n";
                break;

            case 4:
                if (coaches.empty()) {
                    cout << "No coaches available.\n";
                } else {
                    for (int i = 0; i < coaches.size(); i++) {
                        coaches[i].display();
                    }
                }
                break;

            case 5:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);
}