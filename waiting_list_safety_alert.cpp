
#include "RailwaySystem.h"

// ==================== WAITING NODE ====================

WaitingNode::WaitingNode(int pId, int trainNo,
                         string passengerName, string coach) {
    passengerId = pId;
    trainNumber = trainNo;
    name = passengerName;
    coachPreference = coach;
    next = 0;
}

// ==================== WAITING LIST ====================

WaitingList::WaitingList() {
    front = 0;
    rear = 0;
}

void WaitingList::enqueue(int passengerId, int trainNumber,
                          string name, string coach) {
    WaitingNode* node =
        new WaitingNode(passengerId, trainNumber, name, coach);

    if (rear == 0) {
        front = rear = node;
    }
    else {
        rear->next = node;
        rear = node;
    }

    cout << "\nPassenger added to waiting list.\n";
}

bool WaitingList::dequeue() {
    if (front == 0)
        return false;

    WaitingNode* temp = front;
    front = front->next;

    if (front == 0)
        rear = 0;

    delete temp;

    return true;
}

void WaitingList::display() const {
    if (front == 0) {
        cout << "\nWaiting list is empty.\n";
        return;
    }

    WaitingNode* current = front;

    cout << "\n========== WAITING LIST ==========\n";

    while (current != 0) {
        cout << "\nPassenger ID: " << current->passengerId
             << "\nName: " << current->name
             << "\nTrain Number: " << current->trainNumber
             << "\nCoach Preference: " << current->coachPreference
             << "\n";

        current = current->next;
    }
}

// ==================== SAFETY ALERT ====================

SafetyAlert::SafetyAlert() {
    alertId = 0;
    pnr = 0;
    trainNumber = 0;
    berth = 0;
}

SafetyAlert::SafetyAlert(int id, int pnrNumber, int trainNo,
                         string coachName, int berthNo,
                         string alertType, string message,
                         string alertStatus) {
    alertId = id;
    pnr = pnrNumber;
    trainNumber = trainNo;
    coach = coachName;
    berth = berthNo;
    type = alertType;
    description = message;
    status = alertStatus;
}

void SafetyAlert::display() const {
    cout << "\nAlert ID: " << alertId
         << "\nPNR: " << pnr
         << "\nTrain Number: " << trainNumber
         << "\nCoach: " << coach
         << "\nBerth: " << berth
         << "\nAlert Type: " << type
         << "\nDescription: " << description
         << "\nStatus: " << status
         << "\n";
}

// ==================== ALERT NODE ====================

AlertNode::AlertNode(const SafetyAlert& alert) {
    data = alert;
    next = 0;
}

// ==================== ALERT LIST ====================

AlertList::AlertList() {
    head = 0;
}

void AlertList::insert(const SafetyAlert& alert) {
    AlertNode* node = new AlertNode(alert);

    node->next = head;
    head = node;
}

bool AlertList::updateStatus(int alertId, string newStatus) {
    AlertNode* current = head;

    while (current != 0) {
        if (current->data.alertId == alertId) {
            current->data.status = newStatus;
            return true;
        }

        current = current->next;
    }

    return false;
}

SafetyAlert* AlertList::search(int alertId) {
    AlertNode* current = head;

    while (current != 0) {
        if (current->data.alertId == alertId)
            return &current->data;

        current = current->next;
    }

    return 0;
}

void AlertList::display() const {
    if (head == 0) {
        cout << "\nNo safety alerts available.\n";
        return;
    }

    AlertNode* current = head;

    cout << "\n========== SAFETY ALERTS ==========\n";

    while (current != 0) {
        current->data.display();
        current = current->next;
    }
}

// ==================== WAITING LIST & SAFETY MENU ====================

void waitingSafetyMenu(WaitingList& waiting, AlertList& alerts) {
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "     WAITING LIST & SAFETY ALERTS\n";
        cout << "========================================\n";

        cout << "\n---------- WAITING LIST ----------\n";
        cout << "1. Add Waiting Passenger\n";
        cout << "2. Remove First Waiting Passenger\n";
        cout << "3. Display Waiting List\n";

        cout << "\n---------- SAFETY ALERTS ----------\n";
        cout << "4. Create Safety Alert\n";
        cout << "5. Search Alert\n";
        cout << "6. Update Alert Status\n";
        cout << "7. Display All Alerts\n";

        cout << "\n0. Back\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, trainNo;
            string name, coach;

            cout << "Passenger ID: ";
            cin >> id;

            cout << "Train Number: ";
            cin >> trainNo;

            cout << "Passenger Name: ";
            cin >> name;

            cout << "Coach Preference: ";
            cin >> coach;

            waiting.enqueue(id, trainNo, name, coach);
        }

        else if (choice == 2) {
            if (waiting.dequeue())
                cout << "\nFirst waiting passenger removed.\n";
            else
                cout << "\nWaiting list is empty.\n";
        }

        else if (choice == 3) {
            waiting.display();
        }

        else if (choice == 4) {
            int id, pnr, trainNo, berth;
            string coach, type, description;

            cout << "Alert ID: ";
            cin >> id;

            cout << "PNR: ";
            cin >> pnr;

            cout << "Train Number: ";
            cin >> trainNo;

            cout << "Coach: ";
            cin >> coach;

            cout << "Berth Number: ";
            cin >> berth;

            cout << "Alert Type: ";
            cin >> type;

            cout << "Description: ";
            cin >> description;

            alerts.insert(
                SafetyAlert(id, pnr, trainNo, coach, berth,
                            type, description, "OPEN")
            );

            cout << "\nSafety alert created successfully.\n";
        }

        else if (choice == 5) {
            int id;

            cout << "Enter Alert ID: ";
            cin >> id;

            SafetyAlert* alert = alerts.search(id);

            if (alert != 0)
                alert->display();
            else
                cout << "\nAlert not found.\n";
        }

        else if (choice == 6) {
            int id;
            string status;

            cout << "Enter Alert ID: ";
            cin >> id;

            cout << "Enter New Status: ";
            cin >> status;

            if (alerts.updateStatus(id, status))
                cout << "\nAlert status updated successfully.\n";
            else
                cout << "\nAlert not found.\n";
        }

        else if (choice == 7) {
            alerts.display();
        }

        else if (choice == 0) {
            cout << "\nReturning to previous menu.\n";
        }

        else {
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);
}
