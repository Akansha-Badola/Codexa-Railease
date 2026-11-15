# RAILEASE – Railway Simulation System 🚆

## 1. Project Overview

RAILEASE is a C++-based Railway Simulation System developed as an academic project. It provides a menu-driven platform to manage railway operations, including trains, coaches, passengers, reservations, waiting lists, safety alerts, and staff records.

The project demonstrates the practical implementation of Object-Oriented Programming (OOP), Data Structures, and File Handling in C++.

## 2. Problem Statement

Managing railway records manually can be time-consuming and difficult to maintain. Keeping track of train schedules, coach availability, passenger details, reservations, and staff information requires an organized system.

RAILEASE addresses this problem by providing a centralized, console-based solution for managing railway records and performing essential railway management operations.

## 3. Solution

RAILEASE provides a menu-driven system in which users can access different railway management modules through a simple console interface.

The system uses C++ classes, linked lists, vectors, and file handling to organize records, perform operations, and store supported information in text files.

## 4. Features

1. **Train Management**
   - Add and search trains.
   - Display train details.
   - Update train information, schedules, and status.
   - Search trains by source and destination.
   - Manage train seat availability.
2. **Coach Management**
   - Add and search coaches.
   - Display coach information.
   - Update available seats.
   - Delete coach records.
   - Maintain coach details associated with trains.
3. **Passenger Management**
   - Maintain passenger records.
   - Perform passenger-related record operations.
4. **Reservation Management**
   - Book train tickets.
   - Generate unique PNR numbers.
   - Select trains, coaches, and berths.
   - Check berth availability.
   - Search reservations using PNR.
   - Cancel reservations.
   - Update seat availability after booking and cancellation.
5. **Waiting List and Safety Alerts**
   - Manage waiting-list records.
   - Organize safety alert information.
6. **Staff Management**
   - Maintain staff information.
   - Perform staff-related record operations.
7. **File Handling**
   - Store train, coach, and reservation information in text files.
   - Retrieve supported records when the application starts.
   - Maintain data between program executions for supported modules.
8. **Reports**
   - Support booking, passenger, and safety-related reporting functionality where implemented.

## 5. Technologies Used

- **Programming Language:** C++
- **Core Concepts:** Object-Oriented Programming (OOP)
- **Data Structures:** Vectors, Linked Lists, and Queues
- **File Handling:** C++ File Streams (`ifstream`, `ofstream`)
- **Interface:** Console-based Menu System
- **Development Environment:** C++ Compiler / IDE

## 6. Project Structure

The project is organized into separate source files and a common header file for modular development.

| File | Purpose |
|---|---|
| `main.cpp` | Main program and menu navigation |
| `RailwaySystem.h` | Common class and function declarations |
| `train.cpp` | Train management |
| `coach.cpp` | Coach management |
| `passenger.cpp` | Passenger management |
| `reservation.cpp` | Ticket booking and cancellation |
| `staff.cpp` | Staff management |
| `waiting_safety.cpp` | Waiting-list and safety-alert management |

**Data files:**

- `trains.txt`
- `coaches.txt`
- `reservations.txt`

Additional text files may be created by the relevant modules during execution.

## 7. How to Run

1. Download or clone the repository.
2. Open the project folder in a C++ IDE or terminal.
3. Make sure all required `.cpp` files and the common header file are included.
4. Compile the source files together.
5. Run the generated executable.
6. Select the required operation from the main menu.

**Compilation command (g++):**

```bash
g++ -std=c++11 main.cpp train.cpp coach.cpp waiting_safety.cpp reservation.cpp staff.cpp passenger.cpp -o RailwaySystem.exe
```

**Run the application (Windows PowerShell):**

```powershell
.\RailwaySystem.exe
```

## 8. Learning Outcomes

Through this project, we gained practical experience in:

- Applying Object-Oriented Programming concepts in C++.
- Implementing linked lists and other data structures.
- Developing modular programs using header and source files.
- Performing CRUD operations on railway records.
- Implementing ticket booking and cancellation logic.
- Managing data using file handling.
- Integrating different modules into a single application.
- Testing and debugging a menu-driven software system.

## 9. Team Information

**Team Name:** Codexa

**Team Members:**

1. Binita Singha
2. Suhana Joshi
3. Akanksha Negi
4. Akansha Badola
5. Anushka Pagwal

## 10. Project Status

**Status: Successfully Completed**

RAILEASE has been developed as a functional academic railway simulation project. The project brings together multiple railway management modules in a single C++ application and demonstrates the practical use of OOP, Data Structures, and File Handling.

---

**Developed by Team Codexa**  
*RAILEASE – Organizing Railway Operations Through C++*
