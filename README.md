 GPA Calculator

A simple and efficient GPA Calculator that helps students compute their Grade Point Average (GPA) based on their marks or letter grades. The program supports multiple subjects, weighted GPA calculation, letter grade conversion, and student record management.


       Features

 Enter multiple subjects per student

 Accept both marks (0–100) and letter grades (A, B, etc.)

 Automatic GPA calculation based on a grading scale

 Supports weighted GPA (credit hours)

 Converts marks ↔ letter grades automatically

 Search, edit, and delete student records

 Save and load student GPA records from a file

🏅 Provides GPA classification (First Class, Second Class, etc.)


🛠️ Tech Stack

Language: C++

Paradigm: Object-Oriented Programming (OOP)

File Handling: Used for storing and retrieving student records

Input Validation: Prevents invalid or out-of-range entries

📖 How It Works

User inputs student details (name, courses, marks/grades, credit hours).

Program converts marks to GPA points using a grading scale.


GPA is calculated as:

𝐺
𝑃
𝐴
=
∑
(
Grade Point
×
Credit Hours
)
∑
(
Credit Hours
)
GPA=
∑(Credit Hours)
∑(Grade Point×Credit Hours)
	​


GPA classification is displayed (e.g., First Class, Second Class, Pass).

Data can be saved to or loaded from a file for later use.

🧩 Algorithm Explanation
Step 1: Input Student Data

Prompt user for student name.

For each course:

Input course name

Input either marks (0–100) or letter grade (A–F)

Input credit hours

Step 2: Convert Marks/Grades to GPA Points

If marks are given:

Use a grading scale (e.g., 80–100 → A → 4.0, 70–79 → B → 3.0, etc.)

If letter grade is given:

Convert directly to grade points.

Step 3: Compute Weighted GPA

For each course:

Multiply grade point × credit hours

Keep track of total grade points and total credits.

Formula:

𝐺
𝑃
𝐴
=
Total Weighted Grade Points
Total Credits
GPA=
Total Credits
Total Weighted Grade Points
	​

Step 4: Classify GPA

If GPA ≥ 3.6 → First Class

If 3.0 ≤ GPA < 3.6 → Second Class Upper

If 2.0 ≤ GPA < 3.0 → Second Class Lower

Else → Pass/Fail

Step 5: Save & Display

Display student GPA and classification.

Optionally save results to a file.

📊 Example Usage

Input:

Student: John Doe

Courses:

Math → 85 (3 credits)

Physics → 78 (4 credits)

English → B (2 credits)

Output:

Student: John Doe
GPA: 3.45
Classification: Second Class Upper

📂 Project Structure
📦 GPA-Calculator
 ┣ 📜 main.cpp       # Main program
 ┣ 📜 Student.h      # Student class header
 ┣ 📜 Student.cpp    # Student class implementation
 ┣ 📜 GPA.txt        # File storage for records
 ┗ 📜 README.md      # Project documentation

🔮 Future Improvements

Add a Graphical User Interface (GUI) with Qt

Export results in PDF/Excel format

Add semester-wise GPA & CGPA support

Web-based GPA calculator version

🤝 Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you’d like to change.

📜 License

This project is licensed under the MIT License.
