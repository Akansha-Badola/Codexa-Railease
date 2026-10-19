#ifndef RAILWAY_SYSTEM_H
#define RAILWAY_SYSTEM_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// ==================== TRAIN ====================

class Train {
public:
    int trainNumber, totalSeats, availableSeats;
    string trainName, source, destination, date;

    Train();
    Train(int number, string name, string src, string dest,
          string journeyDate, int seats);
    void display() const;
};


// ==================== COACH ====================

class Coach {
public:
    int coachNumber;
    int trainNumber;
    int totalSeats;
    int availableSeats;
    string coachType;

    Coach();
    Coach(int number, int trainNo, string type, int seats);
    void display() const;
};

// ==================== PASSENGER ====================

class Passenger {
public:
    int passengerId, age;
    string name, phone;

    Passenger();
    Passenger(int id, string passengerName, int passengerAge,
              string passengerPhone);
    void display() const;
};

struct PassengerNode {
    Passenger data;
    PassengerNode* next;

    PassengerNode(const Passenger& passenger);
};

class PassengerList {
private:
    PassengerNode* head;

public:
    PassengerList();
    void insert(const Passenger& passenger);
    bool remove(int passengerId);
    Passenger* search(int passengerId);
    void display() const;
};

// ==================== RESERVATION ====================

class Reservation {
public:
    int pnr, passengerId, trainNumber, berth;
    string coach, status;
    double fare;

    Reservation();
    Reservation(int pnrNumber, int pId, int trainNo,
                string coachName, int berthNo,
                double ticketFare, string ticketStatus);
    void display() const;
};

struct ReservationNode {
    Reservation data;
    ReservationNode* next;

    ReservationNode(const Reservation& reservation);
};


class ReservationList {
private:
    ReservationNode* head;

public:
    ReservationList();
    void insert(const Reservation& reservation);
    bool remove(int pnr);
    Reservation* search(int pnr);
    void display() const;
};

// ==================== WAITING LIST ====================

class WaitingNode {
public:
    int passengerId, trainNumber;
    string name, coachPreference;
    WaitingNode* next;

    WaitingNode(int pId, int trainNo,
                string passengerName, string coach);
};

class WaitingList {
private:
    WaitingNode* front;
    WaitingNode* rear;

public:
    WaitingList();
    void enqueue(int passengerId, int trainNumber,
                 string name, string coach);
    bool dequeue();
    void display() const;
};

// ==================== SAFETY ALERT ====================

class SafetyAlert {
public:
    int alertId, pnr, trainNumber, berth;
    string coach, type, description, status;

    SafetyAlert();
    SafetyAlert(int id, int pnrNumber, int trainNo,
                string coachName, int berthNo,
                string alertType, string message,
                string alertStatus);
    void display() const;
};

struct AlertNode {
    SafetyAlert data;
    AlertNode* next;

    AlertNode(const SafetyAlert& alert);
};

class AlertList {
private:
    AlertNode* head;

public:
    AlertList();
    void insert(const SafetyAlert& alert);
    bool updateStatus(int alertId, string newStatus);
    SafetyAlert* search(int alertId);
    void display() const;
};
// ==================== STAFF ====================

class Staff {
public:
    int staffId;
    string name, role, phone;

    Staff();
    Staff(int id, string staffName,
          string staffRole, string staffPhone);
    void display() const;
};

struct StaffNode {
    Staff data;
    StaffNode* next;

    StaffNode(const Staff& staff);
};

class StaffList {
private:
    StaffNode* head;

public:
    StaffList();
    void insert(const Staff& staff);
    bool remove(int staffId);
    Staff* search(int staffId);
    void display() const;
};

// ==================== FILE HANDLER ====================

class FileHandler {
public:
    // Original team declarations kept unchanged
    static void saveTrains(Train trains[], int count);
    static void loadTrains(Train trains[], int& count);

    static void savePassengers(const PassengerList& passengers);
    static void saveReservations(const ReservationList& reservations);
    static void saveWaitingList(const WaitingList& waitingList);
    static void saveAlerts(const AlertList& alerts);
    static void saveStaff(const StaffList& staff);
};

// ==================== REPORTS ====================

class Reports {
public:
    static void bookingReport();
    static void safetyReport();
    static void passengerReport();
};

// ==================== MENU FUNCTIONS ====================

// Original team train menu declaration kept for compatibility
void trainMenu(Train trains[], int& count);

// Your vector-based Train and Coach menus
void trainMenu(vector<Train>& trains, vector<Coach>& coaches);
void coachMenu(vector<Train>& trains, vector<Coach>& coaches);

// Your vector-based file functions (separate from FileHandler)
void loadTrains(vector<Train>& trains);
void saveTrains(const vector<Train>& trains);
void loadCoaches(vector<Coach>& coaches);
void saveCoaches(const vector<Coach>& coaches);

// Passenger Management
void passengerMenu(PassengerList& passengers);

// Reservation Management
void reservationMenu(ReservationList& reservations,
                     Train trains[], int trainCount);

// Waiting List and Safety Alerts
void waitingSafetyMenu(WaitingList& waiting,
                       AlertList& alerts);

// Staff Management
void staffMenu(StaffList& staff);

#endif

