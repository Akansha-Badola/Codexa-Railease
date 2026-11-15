#include "RailwaySystem.h"

// ================= STAFF CONSTRUCTOR =================

Staff::Staff() {
    staffId = 0;
}

Staff::Staff(int id, string staffName,
             string staffRole, string staffPhone) {
    staffId = id;
    name = staffName;
    role = staffRole;
    phone = staffPhone;
}

// ================= STAFF DISPLAY =================

void Staff::display() const {
    cout << "\nStaff ID: " << staffId
         << "\nName: " << name
         << "\nRole: " << role
         << "\nPhone: " << phone << "\n";
}

// ================= STAFF NODE =================

StaffNode::StaffNode(const Staff& staff) {
    data = staff;
    next = nullptr;
}

// ================= STAFF LINKED LIST =================

StaffList::StaffList() {
    head = nullptr;
}

void StaffList::insert(const Staff& staff) {
    StaffNode* node = new StaffNode(staff);
    node->next = head;
    head = node;
}

bool StaffList::remove(int staffId) {
    StaffNode* current = head;
    StaffNode* previous = nullptr;

    while (current != nullptr) {
        if (current->data.staffId == staffId) {
            if (previous == nullptr)
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

Staff* StaffList::search(int staffId) {
    StaffNode* current = head;

    while (current != nullptr) {
        if (current->data.staffId == staffId)
            return &current->data;

        current = current->next;
    }

    return nullptr;
}

void StaffList::display() const {
    StaffNode* current = head;

    if (current == nullptr) {
        cout << "\nNo staff records found.\n";
        return;
    }

    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

// ================= SAVE STAFF DATA =================

void FileHandler::saveStaff(const StaffList& staff) {
    ofstream file("staff.txt");

    if (!file) {
        cout << "Unable to open staff file.\n";
        return;
    }

    StaffNode* current = staff.head;

    while (current != nullptr) {
        file << current->data.staffId << " "
             << current->data.name << " "
             << current->data.role << " "
             << current->data.phone << "\n";

        current = current->next;
    }

    file.close();
    cout << "Staff data saved successfully.\n";
}

// ================= BOOKING REPORT =================

void Reports::bookingReport() {
    ifstream file("reservations.txt");
    cout << "\n========== BOOKING REPORT ==========\n";

    if (!file) {
        cout << "No booking file found.\n";
        return;
    }

    string line;
    while (getline(file, line))
        cout << line << "\n";

    file.close();
}

// ================= SAFETY REPORT =================

void Reports::safetyReport() {
    ifstream file("alerts.txt");
    cout << "\n========== SAFETY REPORT ==========\n";

    if (!file) {
        cout << "No alert file found.\n";
        return;
    }

    string line;
    while (getline(file, line))
        cout << line << "\n";

    file.close();
}

// ================= PASSENGER REPORT =================

void Reports::passengerReport() {
    ifstream file("passengers.txt");
    cout << "\n========== PASSENGER REPORT ==========\n";

    if (!file) {
        cout << "No passenger file found.\n";
        return;
    }

    string line;
    while (getline(file, line))
        cout << line << "\n";

    file.close();
}

// ================= STAFF MENU =================

void staffMenu(StaffList& staff) {
    int choice;

    do {
        cout << "\n================================\n";
        cout << "      STAFF / ADMIN MANAGEMENT\n";
        cout << "================================\n";
        cout << "1. Add Staff\n";
        cout << "2. Search Staff\n";
        cout << "3. Delete Staff\n";
        cout << "4. Display Staff\n";
        cout << "5. Booking Report\n";
        cout << "6. Safety Report\n";
        cout << "7. Passenger Report\n";
        cout << "0. Back\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, role, phone;

            cout << "Staff ID: ";
            cin >> id;

            if (staff.search(id) != nullptr) {
                cout << "Staff ID already exists.\n";
                continue;
            }

            cout << "Name: ";
            cin >> name;
            cout << "Role: ";
            cin >> role;
            cout << "Phone: ";
            cin >> phone;

            staff.insert(Staff(id, name, role, phone));
            cout << "Staff added successfully!\n";
        }
        else if (choice == 2) {
            int id;
            cout << "Enter Staff ID: ";
            cin >> id;
            Staff* s = staff.search(id);

            if (s != nullptr)
                s->display();
            else
                cout << "Staff not found.\n";
        }
        else if (choice == 3) {
            int id;
            cout << "Enter Staff ID: ";
            cin >> id;

            if (staff.remove(id))
                cout << "Staff deleted successfully.\n";
            else
                cout << "Staff not found.\n";
        }
        else if (choice == 4) {
            staff.display();
        }
        else if (choice == 5) {
            Reports::bookingReport();
        }
        else if (choice == 6) {
            Reports::safetyReport();
        }
        else if (choice == 7) {
            Reports::passengerReport();
        }
        else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
