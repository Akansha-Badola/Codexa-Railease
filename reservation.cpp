
#include "RailwaySystem.h"
#include <limits>
#include <cctype>

string normalizeBookingStation(string station)
{
    for (int i = 0; i < station.length(); i++)
    {
        station[i] = tolower(static_cast<unsigned char>(station[i]));
    }

    return station;
}

int generatePNR(ReservationList& reservations)
{
    static int nextPNR = 100001;

    while (reservations.search(nextPNR) != NULL)
    {
        nextPNR++;
    }

    return nextPNR++;
}

// ==================== RESERVATION ====================

Reservation::Reservation()
{
    pnr = 0;
    passengerId = 0;
    trainNumber = 0;
    coach = "";
    berth = 0;
    fare = 0;
    status = "";
}

Reservation::Reservation(int pnrNumber, int pId, int trainNo,
                         string coachName, int berthNo,
                         double ticketFare, string ticketStatus)
{
    pnr = pnrNumber;
    passengerId = pId;
    trainNumber = trainNo;
    coach = coachName;
    berth = berthNo;
    fare = ticketFare;
    status = ticketStatus;
}

void Reservation::display() const
{
    cout << "\n-----------------------------";
    cout << "\nPNR: " << pnr;
    cout << "\nPassenger ID: " << passengerId;
    cout << "\nTrain Number: " << trainNumber;
    cout << "\nCoach: " << coach;
    cout << "\nBerth: " << berth;
    cout << "\nFare: Rs. " << fare;
    cout << "\nStatus: " << status;
    cout << "\n-----------------------------\n";
}

// ==================== RESERVATION NODE ====================

ReservationNode::ReservationNode(const Reservation& reservation)
{
    data = reservation;
    next = NULL;
}

// ==================== RESERVATION LIST ====================

ReservationList::ReservationList()
{
    head = NULL;
}

void ReservationList::insert(const Reservation& reservation)
{
    ReservationNode* newNode = new ReservationNode(reservation);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    ReservationNode* temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

bool ReservationList::remove(int pnr)
{
    if (head == NULL)
    {
        return false;
    }

    if (head->data.pnr == pnr)
    {
        ReservationNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    ReservationNode* temp = head;

    while (temp->next != NULL &&
           temp->next->data.pnr != pnr)
    {
        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        return false;
    }

    ReservationNode* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;

    delete nodeToDelete;

    return true;
}

Reservation* ReservationList::search(int pnr)
{
    ReservationNode* temp = head;

    while (temp != NULL)
    {
        if (temp->data.pnr == pnr)
        {
            return &temp->data;
        }

        temp = temp->next;
    }

    return NULL;
}

bool ReservationList::isBerthBooked(int trainNo, string coachName,
                                    int berthNo) const
{
    ReservationNode* temp = head;

    while (temp != NULL)
    {
        if (temp->data.trainNumber == trainNo &&
            temp->data.coach == coachName &&
            temp->data.berth == berthNo &&
            temp->data.status == "CONFIRMED")
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

void ReservationList::display() const
{
    if (head == NULL)
    {
        cout << "\nNo reservations found.\n";
        return;
    }

    ReservationNode* temp = head;

    while (temp != NULL)
    {
        temp->data.display();
        temp = temp->next;
    }
}

// ==================== SAVE RESERVATIONS ====================

void FileHandler::saveReservations(const ReservationList& reservations)
{
    ofstream file("reservations.txt");

    if (!file.is_open())
    {
        cout << "\nUnable to save reservations.txt. Check the folder permission.\n";
        return;
    }

    ReservationNode* temp = reservations.head;

    while (temp != NULL)
    {
        file << temp->data.pnr << " "
             << temp->data.passengerId << " "
             << temp->data.trainNumber << " "
             << temp->data.coach << " "
             << temp->data.berth << " "
             << temp->data.fare << " "
             << temp->data.status << "\n";

        temp = temp->next;
    }

    file.close();

    if (file.good())
        cout << "\nReservation data saved successfully in reservations.txt.\n";
    else
        cout << "\nError occurred while writing reservations.txt.\n";
}

// ==================== LOAD RESERVATIONS ====================

void FileHandler::loadReservations(ReservationList& reservations)
{
    ifstream file("reservations.txt");

    // Support the old singular filename only when the current file is absent.
    if (!file.is_open())
    {
        file.clear();
        file.open("reservation.txt");
    }

    if (!file.is_open())
    {
        cout << "\nNo previous reservation file found. A new one will be created after booking.\n";
        return;
    }

    int pnr, passengerId, trainNumber, berth;
    string coach, status;
    double fare;
    int loadedCount = 0;

    while (file >> pnr >> passengerId >> trainNumber
                >> coach >> berth >> fare >> status)
    {
        if (reservations.search(pnr) == NULL)
        {
            Reservation reservation(pnr, passengerId, trainNumber,
                                     coach, berth, fare, status);
            reservations.insert(reservation);
            loadedCount++;
        }
    }

    file.close();
    cout << "\nLoaded " << loadedCount << " reservation(s) from file.\n";
}

// ==================== RESERVATION MENU ====================

void reservationMenu(ReservationList& reservations,
                     vector<Train>& trains,
                     vector<Coach>& coaches)
{
    int choice;

    do
    {
        cout << "\n========================================";
        cout << "\n          RESERVATION MANAGEMENT";
        cout << "\n========================================";
        cout << "\n1. Book Ticket";
        cout << "\n2. Cancel Ticket";
        cout << "\n3. Search PNR";
        cout << "\n4. Display Reservations";
        cout << "\n0. Back";
        cout << "\nEnter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n";
            continue;
        }

        // ==================== BOOK TICKET ====================

        if (choice == 1)
        {
            string source, destination;
            int passengerId, trainNo, coachNo, berth;

            cout << "\nEnter Source Station: ";
            cin >> source;

            cout << "Enter Destination Station: ";
            cin >> destination;

            vector<int> matchingTrains;

            cout << "\n========== AVAILABLE TRAINS ==========\n";

            for (int i = 0; i < (int)trains.size(); i++)
            {
                string trainStatus =
                    normalizeBookingStation(trains[i].status);

                if (normalizeBookingStation(trains[i].source) ==
                        normalizeBookingStation(source) &&
                    normalizeBookingStation(trains[i].destination) ==
                        normalizeBookingStation(destination) &&
                    trainStatus != "cancelled" &&
                    trainStatus != "departed" &&
                    trainStatus != "arrived" &&
                    trains[i].availableSeats > 0)
                {
                    matchingTrains.push_back(i);

                    trains[i].display();

                    cout << "-----------------------------------\n";
                }
            }

            if (matchingTrains.empty())
            {
                cout << "\nNo available trains found for this route.\n";
                continue;
            }

            cout << "\nEnter Train Number to book: ";
            cin >> trainNo;

            int trainIndex = -1;

            for (int i = 0; i < (int)matchingTrains.size(); i++)
            {
                int index = matchingTrains[i];

                if (trains[index].trainNumber == trainNo)
                {
                    trainIndex = index;
                    break;
                }
            }

            if (trainIndex == -1)
            {
                cout << "\nInvalid Train Number.\n";
                continue;
            }

            Train& selectedTrain = trains[trainIndex];

            if (selectedTrain.availableSeats <= 0)
            {
                cout << "\nNo available seats on this train.\n";
                continue;
            }

            cout << "\nEnter Passenger ID: ";
            cin >> passengerId;

            if (passengerId <= 0)
            {
                cout << "\nInvalid Passenger ID.\n";
                continue;
            }

            cout << "\n========== TRAIN DETAILS ==========\n";
            selectedTrain.display();

            // ==================== DISPLAY COACHES ====================

            cout << "\n========== AVAILABLE COACHES ==========\n";

            bool coachFound = false;

            for (int i = 0; i < (int)coaches.size(); i++)
            {
                if (coaches[i].trainNumber == trainNo &&
                    coaches[i].availableSeats > 0)
                {
                    cout << "\nCoach Number: "
                         << coaches[i].coachNumber;

                    cout << "\nCoach Type: "
                         << coaches[i].coachType;

                    cout << "\nTotal Seats: "
                         << coaches[i].totalSeats;

                    cout << "\nAvailable Seats: "
                         << coaches[i].availableSeats << "\n";

                    coachFound = true;
                }
            }

            if (!coachFound)
            {
                cout << "\nNo available coaches for this train.\n";
                continue;
            }

            cout << "\nEnter Coach Number: ";
            cin >> coachNo;

            int coachIndex = -1;

            for (int i = 0; i < (int)coaches.size(); i++)
            {
                if (coaches[i].trainNumber == trainNo &&
                    coaches[i].coachNumber == coachNo)
                {
                    coachIndex = i;
                    break;
                }
            }

            if (coachIndex == -1)
            {
                cout << "\nInvalid Coach Number.\n";
                continue;
            }

            Coach& selectedCoach = coaches[coachIndex];

            if (selectedCoach.availableSeats <= 0)
            {
                cout << "\nNo seats available in this coach.\n";
                continue;
            }

            // ==================== BERTH SELECTION ====================

            cout << "\nEnter Berth Number (1-"
                 << selectedCoach.totalSeats << "): ";

            cin >> berth;

            if (berth < 1 || berth > selectedCoach.totalSeats)
            {
                cout << "\nInvalid Berth Number.\n";
                continue;
            }

            string coachName =
                to_string(selectedCoach.coachNumber) +
                "-" + selectedCoach.coachType;

            if (reservations.isBerthBooked(trainNo, coachName, berth))
            {
                cout << "\nThis berth is already booked.\n";
                continue;
            }

            // ==================== CONFIRM BOOKING ====================

            double fare = selectedTrain.fare;

            int pnr = generatePNR(reservations);

            Reservation newReservation(
                pnr,
                passengerId,
                trainNo,
                coachName,
                berth,
                fare,
                "CONFIRMED"
            );

            reservations.insert(newReservation);

            selectedCoach.availableSeats--;
            selectedTrain.availableSeats--;

            saveTrains(trains);
            saveCoaches(coaches);
            FileHandler::saveReservations(reservations);

            cout << "\nTicket booked successfully!\n";

            cout << "\n========== TICKET DETAILS ==========\n";

            newReservation.display();

            cout << "\nTrain Name: " << selectedTrain.trainName;

            cout << "\nRoute: " << selectedTrain.source
                 << " to " << selectedTrain.destination;

            cout << "\nFare: Rs. " << fare << "\n";
        }

        // ==================== CANCEL TICKET ====================

        else if (choice == 2)
        {
            int pnr;

            cout << "\nEnter PNR Number: ";
            cin >> pnr;

            Reservation* reservation = reservations.search(pnr);

            if (reservation == NULL)
            {
                cout << "\nReservation not found.\n";
                continue;
            }

            if (reservation->status != "CONFIRMED")
            {
                cout << "\nThis reservation is not confirmed.\n";
                continue;
            }

            int trainNo = reservation->trainNumber;
            string coachName = reservation->coach;

            int berthNo = reservation->berth;

            bool trainFound = false;
            bool coachFound = false;

            for (int i = 0; i < (int)trains.size(); i++)
            {
                if (trains[i].trainNumber == trainNo)
                {
                    trains[i].availableSeats++;
                    trainFound = true;
                    break;
                }
            }

            for (int i = 0; i < (int)coaches.size(); i++)
            {
                string currentCoach =
                    to_string(coaches[i].coachNumber) +
                    "-" + coaches[i].coachType;

                if (coaches[i].trainNumber == trainNo &&
                    currentCoach == coachName)
                {
                    coaches[i].availableSeats++;
                    coachFound = true;
                    break;
                }
            }

            if (!trainFound || !coachFound)
            {
                cout << "\nTrain or coach not found. Cancellation failed.\n";
                continue;
            }

            reservations.remove(pnr);

            saveTrains(trains);
            saveCoaches(coaches);
            FileHandler::saveReservations(reservations);

            cout << "\nTicket cancelled successfully.\n";
            cout << "\nPNR: " << pnr;
            cout << "\nBerth Number: " << berthNo << "\n";
        }

        // ==================== SEARCH PNR ====================

        else if (choice == 3)
        {
            int pnr;

            cout << "\nEnter PNR Number: ";
            cin >> pnr;

            Reservation* reservation = reservations.search(pnr);

            if (reservation == NULL)
            {
                cout << "\nReservation not found.\n";
            }
            else
            {
                cout << "\n========== RESERVATION DETAILS ==========\n";
                reservation->display();
            }
        }

        // ==================== DISPLAY RESERVATIONS ====================

        else if (choice == 4)
        {
            cout << "\n========== ALL RESERVATIONS ==========\n";
            reservations.display();
        }

        else if (choice == 0)
        {
            cout << "\nReturning to Main Menu...\n";
        }

        else
        {
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 0);
}
