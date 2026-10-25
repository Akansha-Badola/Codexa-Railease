#include "RailwaySystem.h"
#include "RailwaySystem.h"

int generatePNR(ReservationList& reservations) {
    static int nextPNR = 100001;

    while (reservations.search(nextPNR) != 0) {
        nextPNR++;
    }

    return nextPNR++;
}
Reservation::Reservation() {
    pnr = 0;
    passengerId = 0;
    trainNumber = 0;
    berth = 0;
    fare = 0;
}

Reservation::Reservation( int pId, int trainNo,
                         string coachName, int berthNo,
                         double ticketFare, string ticketStatus) {
    passengerId = pId;
    trainNumber = trainNo;
    coach = coachName;
    berth = berthNo;
    fare = ticketFare;
    status = ticketStatus;
}

void Reservation::display() const {
    cout << "\nPNR: " << pnr
         << "\nPassenger ID: " << passengerId
         << "\nTrain No: " << trainNumber
         << "\nCoach: " << coach
         << "\nBerth: " << berth
         << "\nFare: " << fare
         << "\nStatus: " << status << "\n";
}

ReservationNode::ReservationNode(const Reservation& reservation) {
    data = reservation;
    next = 0;
}

ReservationList::ReservationList() {
    head = 0;
}

void ReservationList::insert(const Reservation& reservation) {
    ReservationNode* node = new ReservationNode(reservation);
    node->next = head;
    head = node;
}

bool ReservationList::remove(int pnr) {
    ReservationNode* current = head;
    ReservationNode* previous = 0;

    while (current != 0) {
        if (current->data.pnr == pnr) {
            if (previous == 0)
                head = current->next;
            else
                previous->next = current->next;

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

Reservation* ReservationList::search(int pnr) {
    ReservationNode* current = head;

    while (current != 0) {
        if (current->data.pnr == pnr)
            return &current->data;

        current = current->next;
    }

    return 0;
}

void ReservationList::display() const {
    ReservationNode* current = head;

    while (current != 0) {
        current->data.display();
        current = current->next;
    }
}

void reservationMenu(ReservationList& reservations, Train trains[], int trainCount) {
    int choice;

    do {
        cout << "\n--- RESERVATION & CANCELLATION ---\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Search PNR\n";
        cout << "4. Display Reservations\n";
        cout << "0. Back\n";

        cin >> choice;

        if (choice == 1) {
            int pnr, passengerId, trainNo, berth;
            string coach;
            double fare;
            bool found = false;

            cout << "Passenger ID: ";
            cin >> passengerId;

            cout << "Train number: ";
            cin >> trainNo;

            for (int i = 0; i < trainCount; i++) {
                if (trains[i].trainNumber == trainNo) {
                    found = true;

                    if (trains[i].availableSeats <= 0) {
                        cout << "No seats available.\n";
                        break;
                    }

                    cout << "Coach: ";
                    cin >> coach;

                    cout << "Berth number: ";
                    cin >> berth;

                    cout << "Fare: ";
                    cin >> fare;

                    reservations.insert(
                        Reservation( passengerId, trainNo,
                                    coach, berth, fare, "CONFIRMED")
                    );
                    int pnr = generatePNR(reservations);

                    Reservation newReservation(
                        passengerId,
                        trainNo,
                        coach,
                        berth,
                        fare,
                        "CONFIRMED"
                    );

                    newReservation.pnr = pnr;

                    reservations.insert(newReservation);

                    cout << "\nTicket booked successfully!\n";
                    cout << "Your PNR is: " << pnr << "\n";
                    trains[i].availableSeats--;

                    cout << "Ticket booked.\n";
                    break;
                }
            }

            if (!found)
                cout << "Train not found.\n";
        }

        else if (choice == 2) {
            int pnr;

            cout << "PNR: ";
            cin >> pnr;

            Reservation* r = reservations.search(pnr);

            if (r != 0) {
                for (int i = 0; i < trainCount; i++) {
                    if (trains[i].trainNumber == r->trainNumber) {
                        trains[i].availableSeats++;
                        break;
                    }
                }

                reservations.remove(pnr);

                cout << "Reservation cancelled.\n";
            }
            else {
                cout << "PNR not found.\n";
            }
        }

        else if (choice == 3) {
            int pnr;

            cout << "PNR: ";
            cin >> pnr;

            Reservation* r = reservations.search(pnr);

            if (r != 0)
                r->display();
            else
                cout << "PNR not found.\n";
        }

        else if (choice == 4) {
            reservations.display();
        }

    } while (choice != 0);
}