#include "RailwaySystem.h"

int main() {
    vector<Train> trains;
    vector<Coach> coaches;
    PassengerList passengers;
    WaitingList waiting;
    AlertList alerts;
    ReservationList reservations;
    StaffList staff;
    int choice;

    loadTrains(trains);
    loadCoaches(coaches);
    FileHandler::loadReservations(reservations);

    do {
        cout << "\n===== RAILEASE RAILWAY SIMULATION SYSTEM =====\n";
        cout << "1. Train Management\n";
        cout << "2. Coach Management\n";
        cout << "3. Passenger Management\n";
        cout << "4. Reservation Management\n";
        cout << "5. Waiting List & Safety Alerts\n";
        cout << "6. Staff / Admin Management\n";
        cout << "7. Save Staff Data\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: trainMenu(trains, coaches); break;
            case 2: coachMenu(trains, coaches); break;
            case 3: passengerMenu(passengers); break;
            case 4: reservationMenu(reservations, trains, coaches); break;
            case 5: waitingSafetyMenu(waiting, alerts); break;
            case 6: staffMenu(staff); break;
            case 7: FileHandler::saveStaff(staff); break;
            case 8: cout << "Exiting RAILEASE...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
