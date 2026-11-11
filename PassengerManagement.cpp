#include "RailwaySystem.h"

// Default constructor
Passenger::Passenger()
{
    passengerId = 0;
    age = 0;
}

// Parameterized constructor
Passenger::Passenger(int id, string passengerName, int passengerAge,
                     string passengerPhone)
{
    passengerId = id;
    name = passengerName;
    age = passengerAge;
    phone = passengerPhone;
}

// Display passenger details
void Passenger::display() const
{
    cout << "\nPassenger ID: " << passengerId;
    cout << "\nName: " << name;
    cout << "\nAge: " << age;
    cout << "\nPhone: " << phone << endl;
}

// Passenger node constructor
PassengerNode::PassengerNode(const Passenger& passenger)
{
    data = passenger;
    next = 0;
}

// Passenger list constructor
PassengerList::PassengerList()
{
    head = 0;
}

// Add passenger
void PassengerList::insert(const Passenger& passenger)
{
    PassengerNode* newNode = new PassengerNode(passenger);

    newNode->next = head;
    head = newNode;
}

// Search passenger
Passenger* PassengerList::search(int passengerId)
{
    PassengerNode* current = head;

    while (current != 0)
    {
        if (current->data.passengerId == passengerId)
        {
            return &current->data;
        }

        current = current->next;
    }

    return 0;
}

// Delete passenger
bool PassengerList::remove(int passengerId)
{
    PassengerNode* current = head;
    PassengerNode* previous = 0;

    while (current != 0)
    {
        if (current->data.passengerId == passengerId)
        {
            if (previous == 0)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

// Display all passengers
void PassengerList::display() const
{
    PassengerNode* current = head;

    if (current == 0)
    {
        cout << "\nNo passenger records found.\n";
        return;
    }

    cout << "\n========== PASSENGER RECORDS ==========\n";

    while (current != 0)
    {
        current->data.display();
        current = current->next;
    }
}

// Passenger management menu
void passengerMenu(PassengerList& passengers)
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "        PASSENGER MANAGEMENT\n";
        cout << "====================================\n";
        cout << "1. Add Passenger\n";
        cout << "2. Search Passenger\n";
        cout << "3. Update Passenger Details\n";
        cout << "4. Delete Passenger\n";
        cout << "5. Display All Passengers\n";
        cout << "0. Back to Main Menu\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            // Add Passenger
            case 1:
            {
                int id, age;
                string name, phone;

                cout << "\nEnter Passenger ID: ";
                cin >> id;

                if (passengers.search(id) != 0)
                {
                    cout << "\nPassenger ID already exists.\n";
                    break;
                }

                cout << "Enter Name: ";
                cin >> name;

                cout << "Enter Age: ";
                cin >> age;

                cout << "Enter Phone Number: ";
                cin >> phone;

                if (age <= 0)
                {
                    cout << "\nInvalid age.\n";
                    break;
                }

                passengers.insert(Passenger(id, name, age, phone));

                cout << "\nPassenger added successfully.\n";
                break;
            }

            // Search Passenger
            case 2:
            {
                int id;

                cout << "\nEnter Passenger ID: ";
                cin >> id;

                Passenger* p = passengers.search(id);

                if (p != 0)
                {
                    cout << "\nPassenger record found:\n";
                    p->display();
                }
                else
                {
                    cout << "\nPassenger not found.\n";
                }

                break;
            }

            // Update Passenger
            case 3:
            {
                int id;

                cout << "\nEnter Passenger ID to update: ";
                cin >> id;

                Passenger* p = passengers.search(id);

                if (p != 0)
                {
                    cout << "\nCurrent Passenger Details:\n";
                    p->display();

                    cout << "\nEnter New Name: ";
                    cin >> p->name;

                    cout << "Enter New Age: ";
                    cin >> p->age;

                    cout << "Enter New Phone Number: ";
                    cin >> p->phone;

                    if (p->age <= 0)
                    {
                        cout << "\nInvalid age. Please correct the record.\n";
                    }
                    else
                    {
                        cout << "\nPassenger details updated successfully.\n";
                    }
                }
                else
                {
                    cout << "\nPassenger not found.\n";
                }

                break;
            }

            // Delete Passenger
            case 4:
            {
                int id;

                cout << "\nEnter Passenger ID to delete: ";
                cin >> id;

                if (passengers.remove(id))
                {
                    cout << "\nPassenger deleted successfully.\n";
                }
                else
                {
                    cout << "\nPassenger not found.\n";
                }

                break;
            }

            // Display All Passengers
            case 5:
            {
                passengers.display();
                break;
            }

            case 0:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);
}
