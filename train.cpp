
#include "RailwaySystem.h"
#include <sstream>
#include <cctype>

// ==================== TIME VALIDATION ====================

bool convertTime(string input, string& storedTime) {

    string time = "";

    for (int i = 0; i < input.length(); i++) {
        if (input[i] != ' ') {
            time += input[i];
        }
    }

    if (time.length() != 7 || time[2] != ':')
        return false;

    if (!isdigit(time[0]) || !isdigit(time[1]) ||
        !isdigit(time[3]) || !isdigit(time[4]))
        return false;

    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');

    if (hour < 1 || hour > 12 || minute < 0 || minute > 59)
        return false;

    if (time.substr(5) != "AM" && time.substr(5) != "PM")
        return false;

    storedTime = time;

    return true;
}

// ==================== DISPLAY TIME ====================

string formatTime(string time) {

    if (time.length() == 7) {
        return time.substr(0, 5) + " " + time.substr(5);
    }

    // Convert old 24-hour records to 12-hour display

    if (time.length() == 5 && time[2] == ':') {

        int hour = (time[0] - '0') * 10 + (time[1] - '0');

        string period = (hour >= 12) ? "PM" : "AM";

        hour = hour % 12;

        if (hour == 0)
            hour = 12;

        string result = "";

        if (hour < 10)
            result += "0";

        result += to_string(hour);
        result += time.substr(2);
        result += " " + period;

        return result;
    }

    return time;
}

// ==================== CALCULATE JOURNEY DURATION ====================

int convertToMinutes(string time) {

    int hour, minute;

    if (time.length() == 7) {

        hour = (time[0] - '0') * 10 + (time[1] - '0');
        minute = (time[3] - '0') * 10 + (time[4] - '0');

        string period = time.substr(5);

        if (period == "AM") {
            if (hour == 12)
                hour = 0;
        }
        else if (period == "PM") {
            if (hour != 12)
                hour += 12;
        }
        else {
            return -1;
        }
    }
    else if (time.length() == 5 && time[2] == ':') {

        hour = (time[0] - '0') * 10 + (time[1] - '0');
        minute = (time[3] - '0') * 10 + (time[4] - '0');
    }
    else {
        return -1;
    }

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
        return -1;

    return hour * 60 + minute;
}

string getJourneyDuration(string departure, string arrival) {

    int start = convertToMinutes(departure);
    int end = convertToMinutes(arrival);

    if (start == -1 || end == -1)
        return "Not Available";

    int duration = end - start;

    // Arrival on the next day

    if (duration <= 0)
        duration += 24 * 60;

    int hours = duration / 60;
    int minutes = duration % 60;

    return to_string(hours) + " hours " +
           to_string(minutes) + " minutes";
}

// ==================== CONSTRUCTORS ====================

Train::Train() {

    trainNumber = 0;
    totalSeats = 0;
    availableSeats = 0;

    trainName = "";
    source = "";
    destination = "";
    date = "";

    fare = 0;

    departureTime = "NotSet";
    arrivalTime = "NotSet";
}

Train::Train(int number, string name, string src, string dest,
             string journeyDate, int seats, double f,
             string departure, string arrival) {

    trainNumber = number;
    trainName = name;
    source = src;
    destination = dest;
    date = journeyDate;

    totalSeats = seats;
    availableSeats = seats;

    fare = f;

    departureTime = departure;
    arrivalTime = arrival;
}

// ==================== DISPLAY TRAIN ====================

void Train::display() const {

    cout << "\nTrain Number: " << trainNumber;
    cout << "\nTrain Name: " << trainName;
    cout << "\nSource: " << source;
    cout << "\nDestination: " << destination;
    cout << "\nJourney Date: " << date;

    cout << "\nDeparture Time: " << formatTime(departureTime);
    cout << "\nArrival Time: " << formatTime(arrivalTime);

    cout << "\nJourney Duration: "
         << getJourneyDuration(departureTime, arrivalTime);

    cout << "\nTotal Seats: " << totalSeats;
    cout << "\nAvailable Seats: " << availableSeats;
    cout << "\nTrain Fare: Rs. " << fare << "\n";
}

// ==================== SAVE TRAINS ====================

void saveTrains(const vector<Train>& trains) {

    ofstream file("trains.txt");

    for (int i = 0; i < trains.size(); i++) {

        file << trains[i].trainNumber << " "
             << trains[i].trainName << " "
             << trains[i].source << " "
             << trains[i].destination << " "
             << trains[i].date << " "
             << trains[i].totalSeats << " "
             << trains[i].availableSeats << " "
             << trains[i].fare << " "
             << trains[i].departureTime << " "
             << trains[i].arrivalTime << "\n";
    }

    file.close();
}

// ==================== LOAD TRAINS ====================

void loadTrains(vector<Train>& trains) {

    ifstream file("trains.txt");

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        Train t;

        if (ss >> t.trainNumber
               >> t.trainName
               >> t.source
               >> t.destination
               >> t.date
               >> t.totalSeats
               >> t.availableSeats
               >> t.fare) {

            if (!(ss >> t.departureTime >> t.arrivalTime)) {

                t.departureTime = "NotSet";
                t.arrivalTime = "NotSet";
            }

            trains.push_back(t);
        }
    }

    file.close();
}

// ==================== TRAIN MENU ====================

void trainMenu(vector<Train>& trains, vector<Coach>& coaches) {

    int choice, number, seats;
    double fare;

    string name, src, dest, journeyDate;
    string departure, arrival;
    string storedDeparture, storedArrival;

    bool found;

    do {

        cout << "\n===== TRAIN MANAGEMENT =====\n";
        cout << "1. Add Train\n";
        cout << "2. Search Train\n";
        cout << "3. Update Available Seats\n";
        cout << "4. Display All Trains\n";
        cout << "5. Delete Train\n";
        cout << "6. Update Train Schedule\n";
        cout << "7. Back to Main Menu\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            // ADD TRAIN

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

                cout << "Enter train fare: ";
                cin >> fare;

                if (fare <= 0) {
                    cout << "Fare must be greater than zero.\n";
                    break;
                }

                cout << "Enter departure time (HH:MM AM/PM): ";
                cin >> ws;
                getline(cin, departure);

                if (!convertTime(departure, storedDeparture)) {
                    cout << "Invalid departure time.\n";
                    cout << "Example: 06:30 AM or 06:30 PM\n";
                    break;
                }

                cout << "Enter arrival time (HH:MM AM/PM): ";
                getline(cin, arrival);

                if (!convertTime(arrival, storedArrival)) {
                    cout << "Invalid arrival time.\n";
                    cout << "Example: 06:30 AM or 06:30 PM\n";
                    break;
                }

                trains.push_back(
                    Train(number, name, src, dest, journeyDate,
                          seats, fare, storedDeparture, storedArrival)
                );

                saveTrains(trains);

                cout << "Train added successfully.\n";

                break;
            }

            // SEARCH TRAIN

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

                if (!found)
                    cout << "Train not found.\n";

                break;

            // UPDATE AVAILABLE SEATS

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
                        }
                        else {

                            trains[i].availableSeats = seats;

                            saveTrains(trains);

                            cout << "Seats updated successfully.\n";
                        }

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Train not found.\n";

                break;

            // DISPLAY ALL TRAINS

            case 4:

                if (trains.empty()) {

                    cout << "No trains available.\n";
                }
                else {

                    cout << "\n========== RAILEASE RAILWAY SYSTEM ==========\n";

                    for (int i = 0; i < trains.size(); i++) {

                        cout << "\nTRAIN " << i + 1 << "\n";
                        cout << "---------------------------------------------\n";

                        cout << "Train Number : " << trains[i].trainNumber << "\n";
                        cout << "Train Name   : " << trains[i].trainName << "\n";
                        cout << "Source       : " << trains[i].source << "\n";
                        cout << "Destination  : " << trains[i].destination << "\n";
                        cout << "Journey Date : " << trains[i].date << "\n";

                        cout << "Departure Time: "
                             << formatTime(trains[i].departureTime) << "\n";

                        cout << "Arrival Time  : "
                             << formatTime(trains[i].arrivalTime) << "\n";

                        cout << "Journey Duration: "
                             << getJourneyDuration(trains[i].departureTime,
                                                   trains[i].arrivalTime) << "\n";

                        cout << "Total Seats  : " << trains[i].totalSeats << "\n";

                        cout << "Available Seats: "
                             << trains[i].availableSeats << "\n";

                        cout << "Train Fare   : Rs. " << trains[i].fare << "\n";

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

            // DELETE TRAIN

            case 5:

                cout << "Enter train number to delete: ";
                cin >> number;

                found = false;

                for (int i = 0; i < trains.size(); i++) {

                    if (trains[i].trainNumber == number) {

                        trains.erase(trains.begin() + i);

                        saveTrains(trains);

                        cout << "Train deleted successfully.\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Train not found.\n";

                break;

            // UPDATE TRAIN SCHEDULE

            case 6:

                cout << "Enter train number: ";
                cin >> number;

                found = false;

                for (int i = 0; i < trains.size(); i++) {

                    if (trains[i].trainNumber == number) {

                        cout << "Current Departure Time: "
                             << formatTime(trains[i].departureTime) << "\n";

                        cout << "Current Arrival Time: "
                             << formatTime(trains[i].arrivalTime) << "\n";

                        cout << "Current Journey Duration: "
                             << getJourneyDuration(trains[i].departureTime,
                                                   trains[i].arrivalTime) << "\n";

                        cout << "Enter new departure time (HH:MM AM/PM): ";

                        cin >> ws;
                        getline(cin, departure);

                        if (!convertTime(departure, storedDeparture)) {

                            cout << "Invalid departure time.\n";

                            found = true;
                            break;
                        }

                        cout << "Enter new arrival time (HH:MM AM/PM): ";

                        getline(cin, arrival);

                        if (!convertTime(arrival, storedArrival)) {

                            cout << "Invalid arrival time.\n";

                            found = true;
                            break;
                        }

                        trains[i].departureTime = storedDeparture;
                        trains[i].arrivalTime = storedArrival;

                        saveTrains(trains);

                        cout << "Train schedule updated successfully.\n";

                        cout << "New Journey Duration: "
                             << getJourneyDuration(storedDeparture,
                                                   storedArrival) << "\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Train not found.\n";

                break;

            case 7:

                cout << "Returning to main menu...\n";

                break;

            default:

                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);
}
