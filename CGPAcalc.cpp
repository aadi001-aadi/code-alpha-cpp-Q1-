#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Structure to hold individual course details
struct Course {
    string name;
    string grade;
    double creditHours;
    double gradePoints;
};

// Function to convert letter grades to GPA points
double letterGradeToPoints(string grade) {
    // Convert to uppercase for case-insensitivity
    transform(grade.begin(), grade.end(), grade.begin(), ::toupper);
    
    if (grade == "A+" || grade == "A") return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B") return 3.0;
    if (grade == "B-") return 2.7;
    if (grade == "C+") return 2.3;
    if (grade == "C") return 2.0;
    if (grade == "C-") return 1.7;
    if (grade == "D+") return 1.3;
    if (grade == "D") return 1.0;
    return 0.0; // F grade or invalid input
}

int main() {
    int totalSemesters;
    cout << "=================================\n";
    cout << "        CGPA CALCULATOR          \n";
    cout << "=================================\n";
    cout << "Enter the total number of semesters: ";
    cin >> totalSemesters;

    double cumulativeTotalPoints = 0;
    double cumulativeTotalCredits = 0;

    for (int sem = 1; sem <= totalSemesters; ++sem) {
        int numCourses;
        cout << "\n--- Semester " << sem << " ---\n";
        cout << "Enter the number of courses taken: ";
        cin >> numCourses;

        vector<Course> courses(numCourses);
        double semTotalPoints = 0;
        double semTotalCredits = 0;

        for (int i = 0; i < numCourses; ++i) {
            cout << "\nCourse " << i + 1 << " Name/Code: ";
            cin.ignore();
            getline(cin, courses[i].name);
            
            cout << "Enter Grade (e.g., A, B+, C-, F): ";
            cin >> courses[i].grade;
            
            cout << "Enter Credit Hours: ";
            cin >> courses[i].creditHours;

            // Calculate points for this specific course
            double pointsPerCredit = letterGradeToPoints(courses[i].grade);
            courses[i].gradePoints = pointsPerCredit * courses[i].creditHours;

            semTotalPoints += courses[i].gradePoints;
            semTotalCredits += courses[i].creditHours;
        }

        // Display Semester Report
        cout << "\n=======================================================\n";
        cout << "             SEMESTER " << sem << " REPORT CARD             \n";
        cout << "=======================================================\n";
        cout << left << setw(15) << "Course" << setw(10) << "Grade" << setw(15) << "Credit Hours" << setw(15) << "Points Earned" << endl;
        cout << "-------------------------------------------------------\n";
        for (const auto& course : courses) {
            cout << left << setw(15) << course.name 
                 << setw(10) << course.grade 
                 << setw(15) << course.creditHours 
                 << setw(15) << course.gradePoints << endl;
        }
        cout << "-------------------------------------------------------\n";
        
        double semGPA = (semTotalCredits > 0) ? (semTotalPoints / semTotalCredits) : 0.0;
        cout << fixed << setprecision(2);
        cout << "Semester " << sem << " GPA: " << semGPA << "\n";
        cout << "=======================================================\n";

        // Aggregate for CGPA
        cumulativeTotalPoints += semTotalPoints;
        cumulativeTotalCredits += semTotalCredits;
    }

    // Final CGPA Calculation
    double finalCGPA = (cumulativeTotalCredits > 0) ? (cumulativeTotalPoints / cumulativeTotalCredits) : 0.0;
    
    cout << "\n=================================\n";
    cout << "        FINAL CGPA SUMMARY       \n";
    cout << "=================================\n";
    cout << "Total Credits Earned: " << cumulativeTotalCredits << endl;
    cout << "Overall CGPA        : " << finalCGPA << endl;
    cout << "=================================\n";

    return 0;
}
