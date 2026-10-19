
#include "RailwaySystem.h"

Train::Train() {
    trainNumber = 0;
    totalSeats = 0;
    availableSeats = 0;
    trainName = "";
    source = "";
    destination = "";
    date = "";
}

Train::Train(int number, string name, string src, string dest,
             string journeyDate, int seats) {
    trainNumber = number;
    trainName = name;
    source = src;
    destination = dest;
    date = journeyDate;
    totalSeats = seats;
    availableSeats = seats;
}

void Train::display() const {
    cout << "\nTrain Number: " << trainNumber;
    cout << "\nTrain Name: " << trainName;
    cout << "\nSource: " << source;
    cout << "\nDestination: " << destination;
    cout << "\nJourney Date: " << date;
    cout << "\nTotal Seats: " << totalSeats;
    cout << "\nAvailable Seats: " << availableSeats << "\n";
}

void saveTrains(const vector<Train>& trains) {
    ofstream file("trains.txt");

    for (int i = 0; i < trains.size(); i++) {
        file << trains[i].trainNumber << " "
             << trains[i].trainName << " "
             << trains[i].source << " "
             << trains[i].destination << " "
             << trains[i].date << " "
             << trains[i].totalSeats << " "
             << trains[i].availableSeats << "\n";
    }

    file.close();
}

void loadTrains(vector<Train>& trains) {
    ifstream file("trains.txt");
    Train t;

    while (file >> t.trainNumber
                >> t.trainName
                >> t.source
                >> t.destination
                >> t.date
                >> t.totalSeats
                >> t.availableSeats) {
        trains.push_back(t);
    }

    file.close();
}

void trainMenu(vector<Train>& trains, vector<Coach>& coaches) {
    int choice, number, seats;
    string name, src, dest, journeyDate;
    bool found;

    do {
        cout << "\n===== TRAIN MANAGEMENT =====\n";
        cout << "1. Add Train\n";
        cout << "2. Search Train\n";
        cout << "3. Update Available Seats\n";
        cout << "4. Display All Trains\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter train number: ";
                cin >> number;

                found = false;

                for (int i = 0; i < trains.size(); i++) {
                    if (trains[i].trainNumber == number) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << "Train number already exists.\n";
                    break;
                }

                cout << "Enter train name (one word): ";
                cin >> name;

                cout << "Enter source station (one word): ";
                cin >> src;

                cout << "Enter destination station (one word): ";
                cin >> dest;

                cout << "Enter journey date (DD-MM-YYYY): ";
                cin >> journeyDate;

                cout << "Enter total seats: ";
                cin >> seats;

                if (seats <= 0) {
                    cout << "Seats must be greater than zero.\n";
                    break;
                }

                trains.push_back(
                    Train(number, name, src, dest, journeyDate, seats)
                );

                saveTrains(trains);
                cout << "Train added successfully.\n";
                break;
            }

            case 2:
                cout << "Enter train number to search: ";
                cin >> number;

                found = false;

                for (int i = 0; i < trains.size(); i++) {
                    if (trains[i].trainNumber == number) {
                        trains[i].display();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Train not found.\n";
                }
                break;

            case 3:
                cout << "Enter train number: ";
                cin >> number;

                found = false;

                for (int i = 0; i < trains.size(); i++) {
                    if (trains[i].trainNumber == number) {
                        cout << "Enter available seats (0-"
                             << trains[i].totalSeats << "): ";
                        cin >> seats;

                        if (seats < 0 || seats > trains[i].totalSeats) {
                            cout << "Invalid seat count.\n";
                        } else {
                            trains[i].availableSeats = seats;
                            saveTrains(trains);
                            cout << "Seats updated successfully.\n";
                        }

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Train not found.\n";
                }
                break;

case 4:
    if (trains.empty()) {
        cout << "No trains available.\n";
    } else {
        cout << "\n========== RAILEASE RAILWAY SYSTEM ==========\n";

        for (int i = 0; i < trains.size(); i++) {
            cout << "\nTRAIN " << i + 1 << "\n";
            cout << "---------------------------------------------\n";

            cout << "Train Number : " << trains[i].trainNumber << "\n";
            cout << "Train Name   : " << trains[i].trainName << "\n";
            cout << "Source       : " << trains[i].source << "\n";
            cout << "Destination  : " << trains[i].destination << "\n";
            cout << "Journey Date : " << trains[i].date << "\n";

            cout << "\nCOACH DETAILS\n";
            cout << "---------------------------------------------\n";
            cout << "Coach No.\tCoach Type\tTotal Seats\n";
            cout << "---------------------------------------------\n";

            bool coachFound = false;

            for (int j = 0; j < coaches.size(); j++) {
                if (coaches[j].trainNumber == trains[i].trainNumber) {
                    cout << coaches[j].coachNumber << "\t\t"
                         << coaches[j].coachType << "\t\t"
                         << coaches[j].totalSeats << "\n";

                    coachFound = true;
                }
            }

            if (!coachFound) {
                cout << "No coaches assigned to this train.\n";
            }

            cout << "---------------------------------------------\n";
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
