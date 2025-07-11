#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// ------- Course structure --------
struct Course {
    string name;
    string gradeInput;
    double creditHours;
    double numericScore;
    string letterGrade;
};

// ------- Students structure --------
struct Students {
    string name;
    vector<Course> courses;
};

// ------- GPA Calculations --------
double convertLetterToGPA(string grade) {
    if (grade == "A") return 4.0;
    else if (grade == "B+") return 3.75;
    else if (grade == "B") return 3.25;
    else if (grade == "B-") return 3.0;
    else if (grade == "C+") return 2.75;
    else if (grade == "C") return 2.5;
    else if (grade == "C-") return 2.0;
    else if (grade == "D") return 1.5;
    else return 0.0;
}

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

string classifyGPA(double gpa) {
    if (gpa >= 3.60) return "First Class";
    else if (gpa >= 3.00) return "Second Class";
    else if (gpa >= 2.00) return "Second Class Lower";
    else if (gpa >= 1.00) return "Pass";
    else return "Fail";
}

// ------- Display Student --------
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

// ------- File Saving Functions --------
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

void saveFullRecords(const vector<Students>& students, const string& filename) {
    ofstream out(filename);
    if (!out) {
        cout << "❌ Error opening file for writing.\n";
        return;
    }

    for (const auto& student : students) {
        out << "# New student\n";
        out << student.name << "\n";
        out << student.courses.size() << "\n";
        for (const auto& course : student.courses) {
            out << course.name << "," << course.gradeInput << ",";
            if (course.gradeInput == "mark")
                out << course.numericScore;
            else
                out << course.letterGrade;
            out << "," << course.creditHours << "\n";
        }
    }

    out.close();
    cout << "✅ Student records saved to '" << filename << "'\n";
}

void loadFullRecords(vector<Students>& students, const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "❌ Error opening file...\n";
        return;
    }

    students.clear();
    string line;
    while (getline(in, line)) {
        if (line == "# New student") {
            Students student;
            getline(in, student.name);

            int numCourses;
            in >> numCourses;
            in.ignore();

            for (int i = 0; i < numCourses; ++i) {
                Course course;
                getline(in, line);
                stringstream ss(line);
                string token;

                getline(ss, course.name, ',');
                getline(ss, course.gradeInput, ',');

                if (course.gradeInput == "mark") {
                    getline(ss, token, ',');
                    course.numericScore = stod(token);
                } else {
                    getline(ss, course.letterGrade, ',');
                }

                getline(ss, token, ',');
                course.creditHours = stod(token);

                student.courses.push_back(course);
            }

            students.push_back(student);
        }
    }

    in.close();
    cout << "✅ Student records loaded from '" << filename << "'\n";
}

// ------- Extra Features --------
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

void deleteStudentByName(vector<Students>& students) {
    string nameToDelete;
    cout << "\nEnter the name of the student to delete: ";
    getline(cin >> ws, nameToDelete);

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->name == nameToDelete) {
            char confirm;
            cout << "Are you sure you want to delete " << nameToDelete << "? (y/n): ";
            cin >> confirm;
            if (tolower(confirm) == 'y') {
                students.erase(it);
                cout << "\n✅ Student '" << nameToDelete << "' deleted successfully.\n";
            } else {
                cout << "\n❌ Deletion cancelled.\n";
            }
            return;
        }
    }

    cout << "\n❌ Student '" << nameToDelete << "' not found.\n";
}

void editStudentByName(vector<Students>& students) {
    string searchName;
    cout << "\nEnter student name to edit: ";
    getline(cin >> ws, searchName);

    for (auto& student : students) {
        if (student.name == searchName) {
            cout << "\nEditing student: " << student.name << endl;
            cout << "Enter new name (or press Enter to keep current): ";
            string newName;
            getline(cin >> ws, newName);
            if (!newName.empty()) student.name = newName;

            cout << "\nCourses for " << student.name << ":\n";
            for (size_t i = 0; i < student.courses.size(); ++i) {
                cout << i + 1 << ". " << student.courses[i].name << endl;
            }

            int courseIndex;
            cout << "\nEnter course number to edit (or 0 to skip): ";
            cin >> courseIndex;

            if (courseIndex > 0 && courseIndex <= student.courses.size()) {
                Course& course = student.courses[courseIndex - 1];
                cin.ignore();

                cout << "Editing course: " << course.name << endl;
                cout << "Enter new course name (or press Enter to keep): ";
                string newCourseName;
                getline(cin, newCourseName);
                if (!newCourseName.empty()) course.name = newCourseName;

                cout << "Enter new grade type (mark/letter): ";
                cin >> course.gradeInput;

                if (course.gradeInput == "mark") {
                    cout << "Enter new numeric score (0-100): ";
                    cin >> course.numericScore;
                } else {
                    cout << "Enter new letter grade (A, B+, etc.): ";
                    cin >> course.letterGrade;
                    transform(course.letterGrade.begin(), course.letterGrade.end(), course.letterGrade.begin(), ::toupper);
                }

                cout << "Enter new credit hours: ";
                cin >> course.creditHours;

                cout << "✅ Course updated successfully!\n";
            } else {
                cout << "⚠️ No course edited.\n";
            }

            return;
        }
    }

    cout << " Student '" << searchName << "' not found.\n";
}

// ------- Main Program --------
int main() {
    vector<Students> students;
    int choice;

    do {
        cout << "\n====== GPA CHECKER MENU ======\n";
        cout << "1. Add Student & Courses\n";
        cout << "2. View GPA Results\n";
        cout << "3. Save GPA Summary to File\n";
        cout << "4. Search for a Student by Name\n";
        cout << "5. Load Full Student Records\n";
        cout << "6. Save Full Student Records\n";
        cout << "7. Edit a Student\n";
        cout << "8. Delete a Student\n";
        cout << "9. Exit\n";
        cout << "Enter your choice (1–9): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Students student;
                cin.ignore();
                cout << "\nEnter student name: ";
                getline(cin, student.name);

                int numCourses;
                cout << "Enter number of courses: ";
                cin >> numCourses;

                for (int i = 0; i < numCourses; ++i) {
                    Course course;
                    cout << "\nEnter course name: ";
                    getline(cin >> ws, course.name);

                    cout << "Enter grade type (mark or letter): ";
                    cin >> course.gradeInput;

                    if (course.gradeInput == "mark") {
                        cout << "Enter numeric score (0-100): ";
                        cin >> course.numericScore;
                    } else {
                        cout << "Enter letter grade: ";
                        cin >> course.letterGrade;
                        transform(course.letterGrade.begin(), course.letterGrade.end(), course.letterGrade.begin(), ::toupper);
                    }

                    cout << "Enter credit hours: ";
                    cin >> course.creditHours;

                    student.courses.push_back(course);
                }

                students.push_back(student);
                break;
            }
            case 2:
                for (const Students& s : students) {
                    double gpa = calculateGPA(s);
                    string cls = classifyGPA(gpa);
                    cout << fixed << setprecision(2);
                    cout << "Student: " << s.name << " | GPA: " << gpa << " | Class: " << cls << "\n";
                }
                break;
            case 3: {
                string filename;
                cout << "Enter filename to save results: ";
                cin >> filename;
                saveResultsToFile(students, filename);
                break;
            }
            case 4:
                cin.ignore();
                searchStudentByName(students);
                break;
            case 5: {
                string filename;
                cout << "Enter filename to load records: ";
                cin >> filename;
                loadFullRecords(students, filename);
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to save records: ";
                cin >> filename;
                saveFullRecords(students, filename);
                break;
            }
            case 7:
                cin.ignore();
                editStudentByName(students);
                break;
            case 8:
                cin.ignore();
                deleteStudentByName(students);
                break;
            case 9:
                cout << "Exiting... Goodbye!\n";
                break;
            default:
                cout << "❌ Invalid choice! Try again.\n";
        }

    } while (choice != 9);

    return 0;
}
