# Student Performance Tracker & Database

## Project Overview

This project addresses a common challenge faced by university students: analyzing semester results when they are published with roll numbers and grades, but without student names. This system aims to simplify the process of finding individual academic performance and understanding one's standing relative to peers.

This C++ application merges student personal details (name, email, DOB) from one source with their academic performance (semester GPAs) from another, creating a comprehensive and easily searchable local database.

## The Problem

* University semester results were often released with only roll numbers and SGPAs, omitting student names.
* This made it cumbersome for students to quickly locate their own results or gauge their relative academic performance.
* A separate, pre-existing list (e.g., a PDF or text file) contained essential student details like names, roll numbers, email addresses, and dates of birth.

## The Solution

A C++ program was developed to provide a streamlined solution by:

1.  **Consolidating Data:** Integrating student personal details with their corresponding academic grades.
2.  **Creating a Structured Database:** Storing the merged information in an organized and accessible manner within the program.
3.  **Enabling Efficient Access:** Allowing for quick searching and retrieval of individual student records.

## How It Works & Technical Details

* **Initial Data Handling & Limitations:**
    * Due to initial challenges in finding a readily available C++ library for direct PDF parsing at the time of development, the source PDFs were manually converted into two separate plain text files (`.txt`).
    * `Names.txt`: Contained student personal details (name, roll no., email, DOB).
    * `Grades.txt`: Contained semester GPAs and associated roll numbers.
    * *Note: A future enhancement could involve integrating a PDF parsing library for direct data extraction.*
* **Data Input:** Standard C++ file input/output streams (`std::ifstream`) are utilized to read data from these pre-processed `.txt` files.
* **Core Data Structure:**
    * A `Student` class (or struct) is defined to encapsulate all relevant information for each student:
        * `std::string name;`
        * `std::string rollNo;`
        * `double sgpa;`
        * `std::string email;`
        * `std::string dob;`
    * A `std::vector<Student>` named `database` serves as the primary container to store all student objects.
* **Efficient Indexing & Access Strategy:**
    * To facilitate faster data retrieval, the unique numeric part of a student's roll number (e.g., extracting "0001" from "B180001ME") is used as an effective index for accessing records within the `database` vector.
    * This approach simplifies and accelerates the lookup process for individual student data. *Consideration: For very large datasets, a `std::map<std::string, Student>` using the full roll number as a key might offer more direct lookups without manual index parsing.*

## Key Features

* **Data Consolidation:** Merges student academic records with personal details.
* **Efficient Lookup:** Utilizes the numeric part of roll numbers for quick data access.
* **C++ Implementation:** Built using standard C++ for portability and performance.
* *(Other implemented features: like searching by name, sorting by SGPA, exporting data to CSV, etc.)*

## Technologies Used

* **Primary Language:** C++
* **Core C++ Libraries:**
    * `<iostream>` for console I/O (primarily for debugging or simple CLI).
    * `<fstream>` for file input operations.
    * `<vector>` for dynamic array (database storage).
    * `<string>` for text manipulation.
    * `<sstream>` (potentially) for parsing lines from files or roll numbers.
    * `<algorithm>` (potentially) for sorting or searching functionalities.
