# FixTrack
FixTrack: Campus Equipment Maintenance System

**OVERVIEW**

FixTrack is a console-based application written in C that manages campus equipment maintenance and repair requests. It allows users to add, update, search, delete, and process maintenance requests based on priority levels.

The system helps organize and track repair requests, making it easier to manage equipment problems in a structured way.

**DATA STRUCTURE USED**

1. Linked List
   Used to store all active maintenance requests. It allows adding, updating, deleting, and searching of requests.
2. Queue
   Used to store completed requests in the order they are processed (First-In, First-Out).
3. Array
   Used to store history logs of all actions like ADD, UPDATE, DELETE, and PROCESS.

**ALGORITHMS USED**

1. Linear Search
   Used to find a request by ID and to check for duplicate IDs.

2. Priority Selection
   Used to process requests based on priority level (1 = High, 2 = Medium, 3 = Low).

**HOW TO RUN IN VS CODE**
 
**Requirements**
  1. Install VS Code 
  2. Install C/C++ extension (Microsoft) 
  3. Install MinGW-w64 (GCC compiler)

**HOW TO RUN CODE**
  1. Open your project folder
  2. Open terminal (Cntrl + J)
  3. Compile program using:
     gcc FixTrack.c -o fixtrack
  4. Run the program using:
     ./fixtrack or fixtrack.exe
