#ifndef ADMIN_H
#define ADMIN_H
#include "Person.h"
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Course.h"

void writeFile(const string &fileName, string username, string password);
bool readFileAdmin(const string &fileName, string username, string password);
void adminPanel();

class Admin: public Person
{
    public:
    Admin();
    ~Admin();
    Admin(const Admin &obj);
    Admin(string, string);
};

Admin::Admin(string password, string username): Person(password, username)
{
    
};


void writeFile(const string &fileName, string username, string password)
{
    ofstream file(fileName, ios::binary | ios::app);

    if(file.is_open())
    {
        size_t size = username.size();
        file.write((char*)&size, sizeof(size_t));
        file.write(username.data(), size);

        size = password.size();
        file.write((char*)&size, sizeof(size_t));
        file.write(password.data(), size);
    }

    else
        cout << "Couldn't open the file!" << endl;
}


bool readFileAdmin(const string &fileName, string username, string password)
{
    ifstream file(fileName, ios::binary | ios::ate);
    if(file.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char[fileSize];
        file.read(mBlock, fileSize);
        char *p = mBlock;

        //Username
        size_t sizeUsername = *((size_t*)p);
        p+=sizeof(size_t);

        string usernameString(p, sizeUsername);
        p+=sizeUsername;

        //Password
        size_t sizePassword = *((size_t*)p);
        p += sizeof(size_t);

        string passwordString(p, sizePassword);
        p += sizePassword;

        //Check username and password
        bool isExist = false;
        if (usernameString == username && passwordString == password)
        {
            isExist = true;
        }
        return isExist;
        delete[] mBlock;
    }
    else
    {
        cout << "File Error!";
        return false;
    }
    
    return false;
}

void adminPanel(bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "Welcome to Admin Panel!" << endl;
    cout << "******************************************" << endl;
    cout << "1. Add Professor" << endl;
    cout << "2. Add Assistant" << endl;
    cout << "3. Add Student" << endl;
    cout << "4. Add Course" << endl;
    cout << "5. Back to main menu" << endl;
    cout << "6. Exit the system" << endl;

    unsigned short number = 0;
    
    do
    {
        if(number > 3 || number < 0)
        {
            cout << "Enter the number between 1 and 4" << endl;
        }
        cout << "Enter the choice: ";
        cin >> number;
    } while (number > 4 || number < 0);
    
    if(number == 1)
    {
        string username = "";
        string password = "";
        unsigned int numberOfCourse = 0;
        int courseID = 0;
        
        cout << "Enter the professor username" << endl;
        cin >> username;
        cout << "Enter the professor password" << endl;
        cin >> password;
        cout << "Enter the number of courses" << endl;
        cin >> numberOfCourse;

        Course* courses = new Course[numberOfCourse];
        for(int i = 0; i<numberOfCourse; i++)
        {
            cout << "Enter the " << i+1 << ". course id ";
            cin >> courseID;
            courses[i].setId(courseID);
        }
           
        Professor p1(password, username);
        p1.courseProf = courses;
        p1.setSizeCourseProf(numberOfCourse);

        writeProfessorFile("professordb.bin", p1);
        adminPanel(isSystemOpen);
    }

    if(number == 2)
    {

    }

    if(number == 3)
    {
        string username = "";
        string password = "";
        unsigned int numberOfCourse = 0;
        int courseID = 0;
        float gpa = 0.0;
        int id = 0;
        
        cout << "Enter the student username" << endl;
        cin >> username;
        cout << "Enter the student password" << endl;
        cin >> password;
        cout << "Enter the student id" << endl;
        cin >> id;
        cout << "Enter the student gpa" << endl;
        cin >> gpa;
        cout << "Enter the number of courses" << endl;
        cin >> numberOfCourse;

        Course* courses = new Course[numberOfCourse];
        for(int i = 0; i<numberOfCourse; i++)
        {
            cout << "Enter the " << i+1 << ". course id ";
            cin >> courseID;
            courses[i].setId(courseID);
        }
           
        Student s1(password, username, id, gpa);
        s1.courseStudent = courses;
        s1.setSizeCourseStudent(numberOfCourse);

        writeStudentFile("studentdb.bin", s1);
        adminPanel(isSystemOpen);
    }

    if(number == 4)
    {
        string courseName;
        int id;
        cout << "Enter the course name: ";
        cin >> courseName;
        cout << "Enter the course id ";
        cin >> id;

        Course c1(courseName, id);
        writeCourseFile("coursedb.bin", c1);
        readCourseFile("coursedb.bin", c1.getId(), c1);
    }

    if(number == 5)
    {

    }

    if(number == 6)
    {
        isSystemOpen = false;
    }
}

#endif