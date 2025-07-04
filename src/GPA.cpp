#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
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
// -------- Declaring function ------
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

        if (course.gradeInput == "mark") {
            gpa = convertToGPA(course.numericScore);
        } else if (course.gradeInput == "letter") {
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
// -------Adding a function to search for students----
void searchStudentByName(const vector<Students>& studentRecords) {
    string searchName;
    cout << "\nEnter student name to search: ";
    cin.ignore(); // clear leftover newline
    getline(cin >> ws, searchName);

    bool found = false;
    for (const auto& student : studentRecords) {
        if (student.name == searchName) {
            displayStudent(student);  // calls the display function we defined earlier
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n❌ Student '" << searchName << "' not found.\n";
    }
}


// ------- Main Menu Function -------
int main() {
    vector<Students> students;
    int choice;

    do {
        cout << "\n====== GPA CHECKER MENU ======\n";
        cout << "1. Add Student & Courses\n";
        cout << "2. View GPA Results\n";
        cout << "3. Save Results to File\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1–4): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Students student;
                cin.ignore(); // Clear buffer
                cout << "\nEnter student name: ";
                getline(cin, student.name);
                // error handling for empty name
                if (student.name .empty()){
                    cout <<"❌ Name cannot be empty. Please try again.\n";
                    break;
                }

                int numCourses;
                cout << "Enter number of courses: ";
                cin >> numCourses;

                // error handling for invalid number of courses
                if(numCourses <= 0) {
                    cout <<"❌ Invalid number of courses. Please try again.\n";
                }

                for (int c = 0; c < numCourses; c++) {
                    Course course;
                    cin.ignore(); // Clear buffer before getline
                    cout << "\nEnter course " << (c + 1) << " name: ";
                    getline(cin, course.name);

                    cout << "Enter grade type (mark or letter): ";
                    cin >> course.gradeInput;

                    if (course.gradeInput == "mark") {
                        cout << "Enter numeric score (0-100): ";
                        cin >> course.numericScore;

                        // error handling for invalid numeric score
                        if (course.numericScore < 0 || course.numericScore >100) {
                            cout <<"❌ Invalid score. Please enter a score between 0 and 100.\n";
                        }
                    } else if (course.gradeInput == "letter") {
                        cout << "Enter letter grade (A, B+, etc.): ";
                        cin >> course.letterGrade;
                    } else {
                        cout << "Invalid grade type. Skipping this course.\n";
                        continue;
                    }

                    cout << "Enter credit hours: ";
                    cin >> course.creditHours;

                    student.courses.push_back(course);
                }

                students.push_back(student);
                break;
            }

            case 2: {
                cout << "\n=========== GPA RESULTS ==========\n";
                for (Students stu : students) {
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
                searchStudentByName(students);
                break;
            }
            case 5:
                cout << "\nExiting the program. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
