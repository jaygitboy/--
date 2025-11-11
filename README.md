Hubei College Entrance Examination Volunteer Application System
A C Language Course Design Project of School of Integrated Circuit, Huazhong University of Science and Technology (HUST)
Project Overview
This project is a course design for the C Language course at the School of Integrated Circuit, ,Huazhong University of Science and Technology. It aims to develop a practical volunteer application assistance system tailored to the college entrance examination (Gaokao) admission rules in Hubei Province.
The system simulates the core business logic of Hubei's Gaokao volunteer application process, providing functions such as user information management, college/major query, volunteer filling, admission prediction, and result display. It is developed purely in C language, focusing on modular design, clear logic structure, and compliance with C language programming specifications.
Features
1. User Management
Support user registration and login (with student ID verification for simulated real scenarios)
Store and manage basic user information (name, student ID, Gaokao score, subject combination, etc.)
Password encryption storage (simple hash algorithm for course design purposes)
2. College & Major Query
Built-in simulated database of Hubei Province colleges and majors (including admission scores, major quotas, subject requirements, etc.)
Multi-condition query: Search by college name, major category, minimum admission score, subject restrictions, etc.
Display detailed information (college profile, major curriculum, historical admission data)
3. Volunteer Filling
Comply with Hubei Gaokao volunteer setting rules (e.g., parallel volunteers, sequential volunteers)
Support filling in multiple volunteers (college + major combination) with priority adjustment
Duplicate check and validity verification (e.g., score threshold check, subject requirement matching)
4. Admission Simulation & Prediction
Simulate the official admission process based on user's volunteer order and score ranking
Predict admission probability for each volunteer based on historical data
Generate detailed admission result reports (admitted college/major, reason for rejection if applicable)
5. Data Persistence
Save user data, filled volunteers, and simulation results to local files (.txt format)
Support data reading and restoration on program restart
Technical Specifications
Programming Language: Pure C (compliant with C99 standard)
Development Environment: Compatible with GCC, MinGW, Dev-C++, or Visual Studio
Data Storage: Text files (no database dependency, for simplicity of course design)

coworker:ZD YJQ

This project is for educational use only. All rights reserved by the development team and the School of Integrated Circuit, HUST.
