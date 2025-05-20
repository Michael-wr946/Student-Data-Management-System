Student Performance Tracker & Database
Project Overview
This project addresses the challenge of analyzing university semester results when they are published without student names, only roll numbers and grades. This makes it difficult for students to gauge their relative performance.

This C++ application merges student personal details (name, email, DOB) with their academic performance (semester GPAs) to create a comprehensive and easily searchable database.

The Problem
University semester results were released with roll numbers and SGPAs but lacked student names.

This made it challenging to quickly find individual results or understand one's academic standing relative to peers.

A separate list containing student names, roll numbers, email, and date of birth was available.

The Solution
A C++ program was developed to:

Combine Data Sources: Integrate student details from one source with academic grades from another.

Create a Database: Store the combined information in an organized manner.

Enable Easy Access: Allow for quick searching and retrieval of student records.

How It Works & Technical Details
Initial Data Handling: Due to challenges in finding a suitable C++ PDF parsing library at the time, the source PDFs (one with names/roll nos./emails/DOBs, and another with SGPAs/roll nos.) were manually converted into two separate text files:

Names.txt: Containing student personal details.

Grades.txt: Containing semester GPAs and corresponding roll numbers.

Data Input: Standard C++ file input/output operations are used to read data from these .txt files.

Core Data Structure:

A student class is defined to encapsulate all relevant information for each student (name, roll no., SGPA, email, DOB).

A std::vector<student> named Database is used to store all student objects.

Efficient Indexing & Access: To facilitate faster data retrieval, the numeric part of a student's roll number (e.g., "0001" from "B180001ME") is used as an effective index for accessing records within the Database vector. This simplifies and speeds up the process of looking up individual student data.

Key Features (Implemented/Planned)
Consolidates student academic and personal data.

Uses roll numbers for efficient data lookup.

(Other features: like searching, sorting, exporting to CSV)
Technologies Used
Language: C++

Core C++ Libraries: Standard Library (vectors, file I/O, strings, etc.)
