#include "RailwaySystem.h"
#include <limits>

Passenger::Passenger()
{
    passengerId = 0;
    age = 0;
    name = "";
    phone = "";
}

Passenger::Passenger(int id, string passengerName, int passengerAge, string passengerPhone)
{
    passengerId = id;
    name = passengerName;
    age = passengerAge;
    phone = passengerPhone;
}

void Passenger::display() const
{
    cout << "\n-----------------------------";
    cout << "\nPassenger ID: " << passengerId;
    cout << "\nName: " << name;
    cout << "\nAge: " << age;
    cout << "\nPhone: " << phone;
    cout << "\n-----------------------------\n";
}

PassengerNode::PassengerNode(const Passenger& p)
{
    data = p;
    next = nullptr;
}

PassengerList::PassengerList()
{
    head = nullptr;
}

void PassengerList::insert(const Passenger& p)
{
    PassengerNode* newNode = new PassengerNode(p);

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        PassengerNode* temp = head;

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    cout << "\nPassenger added successfully!\n";
}

Passenger* PassengerList::search(int id)
{
    PassengerNode* temp = head;

    while (temp != nullptr)
    {
        if (temp->data.passengerId == id)
        {
            return &temp->data;
        }

        temp = temp->next;
    }

    return nullptr;
}

bool PassengerList::remove(int id)
{
    PassengerNode* temp = head;
    PassengerNode* prev = nullptr;

    while (temp != nullptr)
    {
        if (temp->data.passengerId == id)
        {
            if (prev == nullptr)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            delete temp;
            return true;
        }

        prev = temp;
        temp = temp->next;
    }

    return false;
}

void PassengerList::display() const
{
    if (head == nullptr)
    {
        cout << "\nNo passenger records found!\n";
        return;
    }

    PassengerNode* temp = head;

    while (temp != nullptr)
    {
        temp->data.display();
        temp = temp->next;
    }
}

void passengerMenu(PassengerList& passengers)
{
    int choice, id, age;
    string name, phone;

    do
    {
        cout << "\n================================";
        cout << "\n      PASSENGER MANAGEMENT";
        cout << "\n================================";
        cout << "\n1. Add Passenger";
        cout << "\n2. Display All Passengers";
        cout << "\n3. Search Passenger";
        cout << "\n4. Update Passenger Details";
        cout << "\n5. Delete Passenger";
        cout << "\n6. Back to Main Menu";
        cout << "\n================================";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cout << "\nInvalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                cout << "\nEnter Passenger ID: ";
                cin >> id;

                if (id <= 0 || passengers.search(id) != nullptr)
                {
                    cout << "\nInvalid or duplicate ID!\n";
                    break;
                }

                cout << "Enter Passenger Name: ";
                getline(cin >> ws, name);

                cout << "Enter Age: ";
                cin >> age;

                if (age <= 0 || age > 120)
                {
                    cout << "\nInvalid age!\n";
                    break;
                }

                cout << "Enter Phone Number: ";
                cin >> phone;

                Passenger p(id, name, age, phone);
                passengers.insert(p);

                break;
            }

            case 2:
            {
                passengers.display();
                break;
            }

            case 3:
            {
                cout << "\nEnter Passenger ID: ";
                cin >> id;

                Passenger* p = passengers.search(id);

                if (p != nullptr)
                {
                    cout << "\nPassenger found!";
                    p->display();
                }
                else
                {
                    cout << "\nPassenger not found!\n";
                }

                break;
            }

            case 4:
            {
                cout << "\nEnter Passenger ID: ";
                cin >> id;

                Passenger* p = passengers.search(id);

                if (p != nullptr)
                {
                    cout << "Enter New Name: ";
                    getline(cin >> ws, p->name);

                    cout << "Enter New Age: ";
                    cin >> p->age;

                    if (p->age <= 0 || p->age > 120)
                    {
                        cout << "\nInvalid age!\n";
                        break;
                    }

                    cout << "Enter New Phone Number: ";
                    cin >> p->phone;

                    cout << "\nPassenger details updated successfully!\n";
                }
                else
                {
                    cout << "\nPassenger not found!\n";
                }

                break;
            }

            case 5:
            {
                cout << "\nEnter Passenger ID to delete: ";
                cin >> id;

                if (passengers.remove(id))
                {
                    cout << "\nPassenger deleted successfully!\n";
                }
                else
                {
                    cout << "\nPassenger not found!\n";
                }

                break;
            }

            case 6:
            {
                cout << "\nReturning to Main Menu...\n";
                break;
            }

            default:
            {
                cout << "\nPlease enter a valid choice!\n";
            }
        }

    } while (choice != 6);
}
