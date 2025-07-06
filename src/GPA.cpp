#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm> // for transform (to uppercase)
using namespace std;

// ------- Course structure --------
struct Course {
    string name;
    string gradeInput;   // "mark" or "letter"
    double creditHours;
    double numericScore;
    string letterGrade;
};

// ------- Students structure --------
struct Students {
    string name;
    vector<Course> courses;
};

// -------- Function declarations ------
void displayStudent(const Students& student);

// ------ Letter Grade Support -------
double convertLetterToGPA(string grade) {
    if (grade == "A") return 4.0;
    else if (grade == "B+") return 3.75;
    else if (grade == "B") return 3.25;
    else if (grade == "B-") return 3.0;
    else if (grade == "C+") return 2.75;
    else if (grade == "C") return 2.5;
    else if (grade == "C-") return 2.0;
    else if (grade == "D") return 1.5;
    else return 0.0; // Invalid or fail
}

// ------- Numeric Grade Conversion -------
double convertToGPA(double score) {
    if (score >= 80) return 4.0;
    else if (score >= 75) return 3.75;
    else if (score >= 70) return 3.50;
    else if (score >= 65) return 3.00;
    else if (score >= 60) return 3.00;
    else if (score >= 55) return 2.75;
    else if (score >= 50) return 2.50;
    else if (score >= 45) return 2.00;
    else if (score >= 40) return 1.50;
    else return 0.00;
}

// ------- GPA calculation --------
double calculateGPA(Students stu) {
    double totalPoints = 0.0;
    double totalCredits = 0.0;

    for (Course course : stu.courses) {
        double gpa = 0.0;

        if (course.gradeInput == "mark" || course.gradeInput == "MARK") {
            gpa = convertToGPA(course.numericScore);
        } else if (course.gradeInput == "letter" || course.gradeInput == "LETTER") {
            gpa = convertLetterToGPA(course.letterGrade);
        }

        totalPoints += gpa * course.creditHours;
        totalCredits += course.creditHours;
    }

    if (totalCredits == 0) return 0.0;
    return totalPoints / totalCredits;
}

// ------- GPA Classification -------
string classifyGPA(double gpa) {
    if (gpa >= 3.60) return "First Class";
    else if (gpa >= 3.00) return "Second Class";
    else if (gpa >= 2.00) return "Second Class Lower";
    else if (gpa >= 1.00) return "Pass";
    else return "Fail";
}

// ------- File Saving Function -------
void saveResultsToFile(const vector<Students>& students, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile) {
        cout << "Error opening file for writing!\n";
        return;
    }

    outputFile << "=========== GPA RESULTS ==========\n";
    for (const Students& stu : students) {
        double gpa = calculateGPA(stu);
        string classification = classifyGPA(gpa);

        outputFile << fixed << setprecision(2);
        outputFile << "Student: " << stu.name
                   << " | GPA: " << gpa
                   << " | Class: " << classification << endl;
    }

    outputFile.close();
    cout << "\n✅ Results saved to '" << filename << "' successfully!\n";
}

// ------- Search Function -------
void searchStudentByName(const vector<Students>& studentRecords) {
    string searchName;
    cout << "\nEnter student name to search: ";
    getline(cin >> ws, searchName);

    bool found = false;
    for (const auto& student : studentRecords) {
        if (student.name == searchName) {
            displayStudent(student);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n❌ Student '" << searchName << "' not found.\n";
    }
}

// ------- Display Student Details -------
void displayStudent(const Students& student) {
    double gpa = calculateGPA(student);
    string classification = classifyGPA(gpa);

    cout << "\n======= STUDENT DETAILS =======\n";
    cout << "Name: " << student.name << endl;
    cout << fixed << setprecision(2);
    cout << "GPA: " << gpa << " | Class: " << classification << endl;

    cout << "Courses:\n";
    for (const Course& course : student.courses) {
        cout << " - " << course.name << " (";
        if (course.gradeInput == "mark")
            cout << course.numericScore;
        else
            cout << course.letterGrade;
        cout << ", " << course.creditHours << " credit hours)\n";
    }
}

// ------- Main Menu -------
int main() {
    vector<Students> students;
    int choice;

    do {
        cout << "\n====== GPA CHECKER MENU ======\n";
        cout << "1. Add Student & Courses\n";
        cout << "2. View GPA Results\n";
        cout << "3. Save Results to File\n";
        cout << "4. Search for a Student by Name\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1–5): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Students student;
                cin.ignore(); // Clear input buffer

                cout << "\nEnter student name: ";
                getline(cin >> ws, student.name);

                if (student.name.empty()) {
                    cout << "❌ Name cannot be empty. Please try again.\n";
                    break;
                }

                int numCourses;
                cout << "Enter number of courses: ";
                cin >> numCourses;

                if (numCourses <= 0) {
                    cout << "❌ Invalid number of courses. Please try again.\n";
                    break;
                }

                for (int c = 0; c < numCourses; c++) {
                    Course course;

                    cout << "\nEnter course " << (c + 1) << " name: ";
                    getline(cin >> ws, course.name);

                    cout << "Enter grade type (mark or letter): ";
                    cin >> course.gradeInput;

                    if (course.gradeInput == "mark") {
                        cout << "Enter numeric score (0-100): ";
                        cin >> course.numericScore;
                        if (course.numericScore < 0 || course.numericScore > 100) {
                            cout << "❌ Invalid score. Skipping this course.\n";
                            continue;
                        }
                    } else if (course.gradeInput == "letter") {
                        cout << "Enter letter grade (A, B+, etc.): ";
                        cin >> course.letterGrade;

                        // Convert to uppercase
                        transform(course.letterGrade.begin(), course.letterGrade.end(), course.letterGrade.begin(), ::toupper);
                    } else {
                        cout << "❌ Invalid grade type. Skipping this course.\n";
                        continue;
                    }

                    cout << "Enter credit hours: ";
                    cin >> course.creditHours;

                    if (course.creditHours <= 0) {
                        cout << "❌ Invalid credit hours. Skipping this course.\n";
                        continue;
                    }

                    student.courses.push_back(course);
                }

                if (student.courses.empty()) {
                    cout << "⚠️ No valid courses added for this student. They won't be saved.\n";
                    break;
                }

                students.push_back(student);
                break;
            }

            case 2: {
                cout << "\n=========== GPA RESULTS ==========\n";
                for (const Students& stu : students) {
                    double gpa = calculateGPA(stu);
                    string classification = classifyGPA(gpa);

                    cout << fixed << setprecision(2);
                    cout << "Student: " << stu.name
                         << " | GPA: " << gpa
                         << " | Class: " << classification << endl;
                }
                break;
            }

            case 3: {
                string filename;
                cout << "\nEnter filename to save results (e.g., mygpa.txt): ";
                cin >> filename;
                saveResultsToFile(students, filename);
                break;
            }

            case 4: {
                cin.ignore(); // Clear buffer before search
                searchStudentByName(students);
                break;
            }

            case 5:
                cout << "\nExiting the program. Goodbye!\n";
                break;

            default:
                cout << "\n❌ Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
