#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;


struct Student
{
    int rollNo;
    string name;

    int physics;
    int chemistry;
    int maths;

    int total;
    float percentage;
    char grade;
};


vector<Student> students;




void calculateResult(Student &s)
{
    s.total = s.physics + s.chemistry + s.maths;

    s.percentage = s.total / 3.0;

    if (s.percentage >= 90)
        s.grade = 'A';

    else if (s.percentage >= 80)
        s.grade = 'B';

    else if (s.percentage >= 70)
        s.grade = 'C';

    else if (s.percentage >= 60)
        s.grade = 'D';

    else if (s.percentage >= 50)
        s.grade = 'E';

    else
        s.grade = 'F';
}



int findStudent(int rollNo)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].rollNo == rollNo)
        {
            return i;
        }
    }

    return -1;
}



void addStudent()
{
    Student s;

    cout << "\n========== ADD STUDENT ==========\n";

    cout << "Enter Roll Number: ";
    cin >> s.rollNo;

    // Check duplicate roll number
    if (findStudent(s.rollNo) != -1)
    {
        cout << "Student with this Roll Number already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Physics Marks: ";
    cin >> s.physics;

    cout << "Enter Chemistry Marks: ";
    cin >> s.chemistry;

    cout << "Enter Maths Marks: ";
    cin >> s.maths;

    // Calculate result
    calculateResult(s);

    // Add student to vector
    students.push_back(s);

    cout << "\nStudent added successfully!\n";
}

void displayStudent(Student s)
{
    cout << "\n----------------------------------\n";

    cout << "Roll Number : " << s.rollNo << endl;
    cout << "Name        : " << s.name << endl;

    cout << "Physics     : " << s.physics << endl;
    cout << "Chemistry   : " << s.chemistry << endl;
    cout << "Maths       : " << s.maths << endl;

    cout << "Total       : " << s.total << "/300" << endl;

    cout << fixed << setprecision(2);
    cout << "Percentage  : " << s.percentage << "%" << endl;

    cout << "Grade       : " << s.grade << endl;

    cout << "\n";
}


void displayAllStudents()
{
    cout << "\nALL STUDENTS\n";

    if (students.empty())
    {
        cout << "No students available.\n";
        return;
    }

    for (Student s : students)
    {
        displayStudent(s);
    }
}

void searchStudent()
{
    int rollNo;

    cout << "\nSEARCH STUDENT\n";

    cout << "Enter Roll Number: ";
    cin >> rollNo;

    int index = findStudent(rollNo);

    if (index == -1)
    {
        cout << "Student not found!\n";
    }
    else
    {
        cout << "\nStudent found!\n";
        displayStudent(students[index]);
    }
}


void updateStudent()
{
    int rollNo;

    cout << "\nUPDATE STUDENT\n";

    cout << "Enter Roll Number: ";
    cin >> rollNo;

    int index = findStudent(rollNo);

    if (index == -1)
    {
        cout << "Student not found!\n";
        return;
    }

    cin.ignore();

    cout << "Enter New Name: ";
    getline(cin, students[index].name);

    cout << "Enter New Physics Marks: ";
    cin >> students[index].physics;

    cout << "Enter New Chemistry Marks: ";
    cin >> students[index].chemistry;

    cout << "Enter New Maths Marks: ";
    cin >> students[index].maths;

    // Recalculate result
    calculateResult(students[index]);

    cout << "\nStudent updated successfully!\n";
}


// DELETE STUDENT

void deleteStudent()
{
    int rollNo;

    cout << "\n DELETE STUDENT \n";

    cout << "Enter Roll Number: ";
    cin >> rollNo;

    int index = findStudent(rollNo);

    if (index == -1)
    {
        cout << "Student not found!\n";
        return;
    }

    students.erase(students.begin() + index);

    cout << "Student deleted successfully!\n";
}


//SORT BY MARKS 

bool compareMarks(Student a, Student b)
{
    return a.percentage > b.percentage;
}


void sortStudents()
{
    cout << "\n STUDENTS SORTED BY MARKS\n";

    if (students.empty())
    {
        cout << "No students available.\n";
        return;
    }

    sort(students.begin(), students.end(), compareMarks);

    for (int i = 0; i < students.size(); i++)
    {
        cout << i + 1 << ". "
             << students[i].name
             << " | Roll No: " << students[i].rollNo
             << " | Percentage: " << fixed << setprecision(2)
             << students[i].percentage << "%"
             << endl;
    }
}


//  FIND TOPPER 

void findTopper()
{
    cout << "\n TOPPER \n";

    if (students.empty())
    {
        cout << "No students available.\n";
        return;
    }

    int topperIndex = 0;

    for (int i = 1; i < students.size(); i++)
    {
        if (students[i].percentage > students[topperIndex].percentage)
        {
            topperIndex = i;
        }
    }

    cout << "\n🏆 Topper:\n";

    displayStudent(students[topperIndex]);
}


// CLASS AVERAGE

void classAverage()
{
    cout << "\nCLASS AVERAGE \n";

    if (students.empty())
    {
        cout << "No students available.\n";
        return;
    }

    float sum = 0;

    for (Student s : students)
    {
        sum += s.percentage;
    }

    float average = sum / students.size();

    cout << fixed << setprecision(2);

    cout << "Number of Students : "
         << students.size() << endl;

    cout << "Class Average      : "
         << average << "%" << endl;
}


//  DISPLAY BY GRADE 

void displayByGrade()
{
    char grade;

    cout << "\n DISPLAY BY GRADE \n";

    cout << "Enter Grade (A/B/C/D/E/F): ";
    cin >> grade;

    // Convert lowercase to uppercase
    grade = toupper(grade);

    bool found = false;

    cout << "\nStudents with Grade " << grade << ":\n";

    for (Student s : students)
    {
        if (s.grade == grade)
        {
            cout << "\nRoll No     : " << s.rollNo;
            cout << "\nName        : " << s.name;
            cout << "\nPercentage  : "
                 << fixed << setprecision(2)
                 << s.percentage << "%";
            cout << "\nGrade       : " << s.grade << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No student found with Grade "
             << grade << ".\n";
    }
}


//  GRADE SUMMARY 

void gradeSummary()
{
    cout << "\nGRADE SUMMARY \n";

    if (students.empty())
    {
        cout << "No students available.\n";
        return;
    }

    // map stores Grade -> Number of students
    map<char, int> gradeCount;

    for (Student s : students)
    {
        gradeCount[s.grade]++;
    }

    cout << "\nGrade\tStudents\n";

    for (auto item : gradeCount)
    {
        cout << item.first
             << "\t"
             << item.second
             << endl;
    }
}


//  MAIN MENU

int main()
{
    int choice;

    do
    {
        cout << "\n\n";
        cout << "\n";
        cout << "      STUDENT MANAGEMENT & RESULT SYSTEM\n";
        cout << "\n";

        cout << "1.  Add Student\n";
        cout << "2.  Display All Students\n";
        cout << "3.  Search Student\n";
        cout << "4.  Update Student\n";
        cout << "5.  Delete Student\n";
        cout << "6.  Calculate Result\n";
        cout << "7.  Sort Students by Marks\n";
        cout << "8.  Find Topper\n";
        cout << "9.  Class Average\n";
        cout << "10. Display Students by Grade\n";
        cout << "11. Grade Summary\n";
        cout << "0.  Exit\n";

        cout << "\n";

        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:

                if (students.empty())
                {
                    cout << "\nNo students available.\n";
                }
                else
                {
                    cout << "\nResults are calculated automatically "
                         << "when students are added or updated.\n";

                    displayAllStudents();
                }

                break;

            case 7:
                sortStudents();
                break;

            case 8:
                findTopper();
                break;

            case 9:
                classAverage();
                break;

            case 10:
                displayByGrade();
                break;

            case 11:
                gradeSummary();
                break;

            case 0:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 0);


    return 0;
}