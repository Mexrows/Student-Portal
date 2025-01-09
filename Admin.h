#ifndef ADMIN_H
#define ADMIN_H
#include "Person.h"
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Course.h"
#include "Assistant.h"

void writeFile(const string &fileName, string username, string password);
bool readFileAdmin(const string &fileName, string username, string password);
void adminPanel(bool &isSystemOpen);
void removeProfessor(const string &fileName, const string &username);
void removeStudent(const string &fileName, const string &username);
void removeAssistant(const string &fileName, const string &username);



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
    ofstream file(fileName, ios::binary);

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
    cout << "5. Remove Professor" << endl;
    cout << "6. Remove Student" << endl;
    cout << "7. Remove Assistant" << endl;
    cout << "8. Show all professors" << endl;
    cout << "9. Back to main menu" << endl;
    cout << "10. Exit the system" << endl;

    unsigned short number = 0;
    
    do
    {
        if(number > 9)
        {
            cout << "Enter the number between 1 and 4" << endl;
        }
        cout << "Enter the choice: ";
        cin >> number;
    } while (number > 9);
    
    if(number == 1)
    {
        string username = "";
        string password = "";
        unsigned int numberOfCourse = 0;
        int courseID = 0;
        bool isExistCheck = true;

        cin.ignore();
        
        cout << "Enter the professor username: ";
        getline(cin, username);
        Professor temp;
        isExistCheck = readProfessorFile("professordb.bin", username, password, temp, isExistCheck);
        if(isExistCheck)
        {
            cout << "This professor exists! You cannot add." << endl;
            adminPanel(isSystemOpen);
        }
        
        else
        {
            cout << "Enter the professor password: ";
            getline(cin, password);
            cout << "Enter the number of courses: ";
            cin >> numberOfCourse;

            Course* courses = new Course[numberOfCourse];
            for(unsigned int i = 0; i < numberOfCourse; i++)
            {
                cout << "Enter the " << i+1 << ". course id: ";
                cin >> courseID;
                courses[i].setId(courseID);
            }
           
            Professor p1(password, username);
            p1.courseProf = courses;
            p1.setSizeCourseProf(numberOfCourse);

            writeProfessorFile("professordb.bin", p1);
            adminPanel(isSystemOpen);
        }
        
    }

    if(number == 2)
    {
        string username = "";
        string password = "";
        unsigned int numberOfCourseTeach = 0;
        int courseIDTeach = 0;
        unsigned int numberOfCourseLearn = 0;
        int courseIDLearn = 0;
        float gpa = 0.0f;
        int id = 0;
        bool isExistCheck = true;

        cin.ignore();

        cout << "Enter the assistant username: ";
        getline(cin, username);
        Assistant temp;
        isExistCheck = readAssistantFile("assistantdb.bin", username, password, temp, isExistCheck);
        if(isExistCheck)
        {
            cout << "This assistant exists! You cannot add." << endl;
            adminPanel(isSystemOpen);
        }
        else
        {
            cout << "Enter the assistant password: ";
            getline(cin, password);
            cout << "Enter the assistant's student ID: ";
            cin >> id;
            cout << "Enter the assistant's GPA: ";
            cin >> gpa;
            cout << "Enter the number of courses that assistant teaches: ";
            cin >> numberOfCourseTeach;

            Course* coursesTeach = new Course[numberOfCourseTeach];

            for(unsigned int i = 0; i < numberOfCourseTeach; i++)
            {
                cout << "Enter the " << i+1 << ". course id ";
                cin >> courseIDTeach;
                coursesTeach[i].setId(courseIDTeach);
            }

            cout << "Enter the number of courses that assistant learns: ";
            cin >> numberOfCourseLearn;

            Course* coursesLearn = new Course[numberOfCourseLearn];

            for(unsigned int i = 0; i < numberOfCourseLearn; i++)
            {
                cout << "Enter the " << i+1 << ". course id: ";
                cin >> courseIDLearn;
                coursesLearn[i].setId(courseIDLearn);
            }

            Assistant a1(password, username, id, gpa);

            a1.courseProf = coursesTeach;
            a1.setSizeCourseProf(numberOfCourseTeach);

            a1.courseStudent = coursesLearn;
            a1.setSizeCourseStudent(numberOfCourseLearn);

            writeAssistantFile("assistantdb.bin", a1);
            adminPanel(isSystemOpen);
        }
        
    }

    if(number == 3)
    {
        string username = "";
        string password = "";
        unsigned int numberOfCourse = 0;
        int courseID = 0;
        float gpa = 0.0;
        int id = 0;
        bool isExistCheck = true;

        cin.ignore();
        
        cout << "Enter the student username: ";
        getline(cin, username);
        Student temp;
        isExistCheck = readStudentFile("studentdb.bin", username, password, temp, isExistCheck);
        if(isExistCheck)
        {
            cout << "This student exists! You cannot add." << endl;
            adminPanel(isSystemOpen);
        }
        
        else
        {
            cout << "Enter the student password: ";
            getline(cin, password);
            cout << "Enter the student id: ";
            cin >> id;
            cout << "Enter the student gpa: ";
            cin >> gpa;
            cout << "Enter the number of courses: ";
            cin >> numberOfCourse;

            Course* courses = new Course[numberOfCourse];
            for(unsigned int i = 0; i < numberOfCourse; i++)
            {
                cout << "Enter the " << i+1 << ". course id: ";
                cin >> courseID;
                courses[i].setId(courseID);
            }
           
            Student s1(password, username, id, gpa);
            s1.courseStudent = courses;
            s1.setSizeCourseStudent(numberOfCourse);

            writeStudentFile("studentdb.bin", s1);
            adminPanel(isSystemOpen);
        }
    }

    if(number == 4)
    {
        string courseName;
        int id;
        bool isExistCheck = true;

        cin.ignore();

        cout << "Enter the course name: ";
        getline(cin, courseName);
        cout << "Enter the course id: ";
        cin >> id;

        Course c1(courseName, id);
        isExistCheck = readCourseFile("coursedb.bin", c1.getId(), c1);
        if(isExistCheck)
        {
            cout << "This course exists! You cannot add." << endl;
        }
        else
        {
            writeCourseFile("coursedb.bin", c1);
        }
        
        adminPanel(isSystemOpen);
        
        
    }

    if(number == 5)
    {
        string username = "";
        bool areYouSure;

        cin.ignore();

        cout << "Enter the professor's username: " << endl;
        getline(cin, username);

        cout << "Are you sure to delete the professor (1 [Yes] / 0 [No]): " << endl;
        cin >> areYouSure;

        if(areYouSure)
        {
            removeProfessor("professordb.bin", username);
            adminPanel(isSystemOpen);
        }

        adminPanel(isSystemOpen);
    }

    if(number == 6)
    {
        string username = "";
        bool areYouSure;

        cin.ignore();

        cout << "Enter the student's username: " << endl;
        getline(cin, username);

        cout << "Are you sure to delete the student (1 [Yes] / 0 [No]): " << endl;
        cin >> areYouSure;

        if(areYouSure)
        {
            removeStudent("studentdb.bin", username);
            adminPanel(isSystemOpen);
        }

        adminPanel(isSystemOpen);
    }

    if(number == 7)
    {
        string username = "";
        bool areYouSure;

        cin.ignore();

        cout << "Enter the assistant's username: " << endl;
        getline(cin, username);

        cout << "Are you sure to delete the student (1 [Yes] / 0 [No]): " << endl;
        cin >> areYouSure;

        if(areYouSure)
        {
            removeAssistant("assistantdb.bin", username);
            adminPanel(isSystemOpen);
        }

        adminPanel(isSystemOpen);
    }

    if(number == 8)
    {
        int numberOfProfessor = 0;
        Professor* allProfs = readAllProfessor("professordb.bin", numberOfProfessor);
        for(int i = 0; i<numberOfProfessor; i++)
        {
            cout << "Professor Username: " << allProfs[i].getUsername() << endl;
            cout << "Courses: " << endl;
            for(int j = 0; j<allProfs[i].getSizeCourseProf(); j++)
            {
                cout << j+1 << ". Course ID: " << allProfs[i].courseProf[j].getId();
            }
            
        }
        delete[] allProfs;
    }

    if(number == 9)
    {
        cout << endl << endl;
    }

    if(number == 10)
    {
        isSystemOpen = false;
    }
}

void removeProfessor(const string &fileName, const string &username)
{
    ifstream file(fileName, ios::binary | ios::ate);
    ofstream temp("temp.bin", ios::binary);

    if(file.is_open() && temp.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char [fileSize];
        file.read(mBlock, fileSize);
        file.close();
        char* p = mBlock;
        char* end = mBlock + fileSize;
        
        while(p < end)
        {
            size_t sizeUsername = *((size_t*)p);
            p += sizeof(size_t);

            string usernameString(p, sizeUsername);
            p += sizeUsername;

            size_t sizePassword = *((size_t*)p);
            p += sizeof(size_t);

            string passwordString(p, sizePassword);
            p += sizePassword;

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p += sizeof(unsigned int);

            Course* courses = new Course [sizeOfCourses];

            for(unsigned int i = 0; i < sizeOfCourses; i++)
            {
                int id = *((int*)p);
                p += sizeof(int);
                courses[i].setId(id);
            }

            if(username != usernameString)
            {
                temp.write((char*)&sizeUsername, sizeof(size_t));
                temp.write(usernameString.data(), sizeUsername);
                temp.write((char*)&sizePassword, sizeof(size_t));
                temp.write(passwordString.data(), sizePassword);
                temp.write((char*)&sizeOfCourses, sizeof(unsigned int));

                for(unsigned int i = 0; i < sizeOfCourses; i++)
                {
                    int courseID = courses[i].getId();
                    temp.write((char*)&courseID, sizeof(int));
                }
            }
        }

        delete[] mBlock;
        temp.close();

        remove(fileName.data());
        rename("temp.bin", fileName.data());
    }

    else
    {
        cout << "Files couldn't opened!" << endl;
    }

    
}

void removeStudent(const string &fileName, const string &username)
{
    ifstream file(fileName, ios::binary | ios::ate);
    ofstream temp("temp.bin", ios::binary);

    if(file.is_open() && temp.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char [fileSize];
        file.read(mBlock, fileSize);
        file.close();
        char* p = mBlock;
        char* end = mBlock + fileSize;
        
        while(p < end)
        {
            size_t sizeUsername = *((size_t*)p);
            p += sizeof(size_t);

            string usernameString(p, sizeUsername);
            p += sizeUsername;

            size_t sizePassword = *((size_t*)p);
            p += sizeof(size_t);

            string passwordString(p, sizePassword);
            p += sizePassword;

            unsigned int id = *((unsigned int*)p);
            p += sizeof(unsigned int);

            float gpa = *((float*)p);
            p += sizeof(float);

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p += sizeof(unsigned int);

            Course* courses = new Course [sizeOfCourses];

            for(unsigned int i = 0; i < sizeOfCourses; i++)
            {
                int id = *((int*)p);
                p += sizeof(int);
                courses[i].setId(id);
            }

            if(username != usernameString)
            {
                temp.write((char*)&sizeUsername, sizeof(size_t));
                temp.write(usernameString.data(), sizeUsername);
                temp.write((char*)&sizePassword, sizeof(size_t));
                temp.write(passwordString.data(), sizePassword);
                temp.write((char*)&id, sizeof(unsigned int));
                temp.write((char*)&gpa, sizeof(float));
                temp.write((char*)&sizeOfCourses, sizeof(unsigned int));

                for(unsigned int i = 0; i < sizeOfCourses; i++)
                {
                    int courseID = courses[i].getId();
                    temp.write((char*)&courseID, sizeof(int));
                }
            }
        }

        delete[] mBlock;
        temp.close();

        remove(fileName.data());
        rename("temp.bin", fileName.data());
    }

    else
    {
        cout << "Files couldn't opened!" << endl;
    }
}

void removeAssistant(const string &fileName, const string &username)
{
    ifstream file(fileName, ios::binary | ios::ate);
    ofstream temp("temp.bin", ios::binary);

    if(file.is_open() && temp.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char [fileSize];
        file.read(mBlock, fileSize);
        file.close();
        char* p = mBlock;
        char* end = mBlock + fileSize;
        
        while(p < end)
        {
            size_t sizeUsername = *((size_t*)p);
            p += sizeof(size_t);

            string usernameString(p, sizeUsername);
            p += sizeUsername;

            size_t sizePassword = *((size_t*)p);
            p += sizeof(size_t);

            string passwordString(p, sizePassword);
            p += sizePassword;

            unsigned int id = *((unsigned int*)p);
            p += sizeof(unsigned int);

            float gpa = *((float*)p);
            p += sizeof(float);

            unsigned int sizeOfCoursesProf = *((unsigned int*)p);
            p += sizeof(unsigned int);

            Course* courseProf = new Course [sizeOfCoursesProf];

            for(unsigned int i = 0; i < sizeOfCoursesProf; i++)
            {
                int courseID = *((int*)p);
                p += sizeof(int);
                courseProf[i].setId(courseID);
            }

            unsigned int sizeOfCourseStudent = *((unsigned int*)p);
            p += sizeof(unsigned int);


            Course* coursesStudent = new Course [sizeOfCourseStudent];

            for(unsigned int i = 0; i < sizeOfCourseStudent; i++)
            {
                int id = *((int*)p);
                p += sizeof(int);
                coursesStudent[i].setId(id);
            }

            if(username != usernameString)
            {
                temp.write((char*)&sizeUsername, sizeof(size_t));
                temp.write(usernameString.data(), sizeUsername);
                temp.write((char*)&sizePassword, sizeof(size_t));
                temp.write(passwordString.data(), sizePassword);
                temp.write((char*)&id, sizeof(unsigned int));
                temp.write((char*)&gpa, sizeof(float));
                temp.write((char*)&sizeOfCoursesProf, sizeof(unsigned int));

                for(unsigned int i = 0; i < sizeOfCoursesProf; i++)
                {
                    int courseID = courseProf[i].getId();
                    temp.write((char*)&courseID, sizeof(int));
                }

                temp.write((char*)&sizeOfCourseStudent, sizeof(unsigned int));

                for(unsigned int i = 0; i < sizeOfCourseStudent; i++)
                {
                    int courseID = coursesStudent[i].getId();
                    temp.write((char*)&courseID, sizeof(int));
                }
            }
        }

        delete[] mBlock;
        temp.close();

        remove(fileName.data());
        rename("temp.bin", fileName.data());
    }

    else
    {
        cout << "Files couldn't opened!" << endl;
    }
}

#endif