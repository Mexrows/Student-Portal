#include <iostream>
#include <fstream>
#include <string>
#include "Person.h"
#include "Admin.h"
#include "Assistant.h"
#include "Course.h"
#include "Professor.h"
#include "Student.h"
using namespace std;

void mainMenu(bool &isSystemOpen);
void loginScreen(bool &isSystemOpen);

/*
Admin:
username = admin
password = adminpw
---------------------------
Professor:
username = prof1
password = prof1pw
courses = c++, python

username = prof2
password = prof2pw
courses = java
---------------------------
Assistant:
username = assistant1
password = assistant1pw
id = 50
gpa = 3.4
asisst course = c++, python
learn course = java

username = assistant2
password = assistant2pw
id = 51
gpa = 3.8
asisst course = java
learn course = c++
---------------------------
Student:
username = student1
password = student1pw
id = 1
courses = c++, python
gpa = 4.0

username = student2
password = student2pw
id = 2
courses = java
gpa = 3.5

username = student3
password = student3pw
id = 3
courses = c++, java
gpa = 3.0
---------------------------
Courses:
name = c++
id = 1

name = java
id = 2

name = python
id = 3

*/

int main()
{

    writeFile("admindb.bin", "admin", "adminpw");

    bool isSystemOpen = true;
    mainMenu(isSystemOpen);

    if(isSystemOpen)
    {
        do
        {
            loginScreen(isSystemOpen);
        } while (isSystemOpen);
    }


    return 0;
}

void mainMenu(bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "    University Management System" << endl;
    cout << "******************************************" << endl << endl;  
}

void loginScreen(bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Professor Login" << endl;
    cout << "3. Assistant Login" << endl;
    cout << "4. Student Login" << endl;
    cout << "5. Courses" << endl;
    cout << "6. Exit the system" << endl;
    cout << "******************************************" << endl;

    unsigned short number = 0;
    do
    {
        if(number > 6)
        {
            cout << "You should enter the number between 1 and 5" << endl;
        }
        cout << "Enter the your choice: ";
        cin >> number;
    } while (number > 6);
    
    string username = "";
    string password = "";
    bool isExist = false;
    
    if(number == 1)
    {
        cout << "Welcome to Admin Login!" << endl;

            cin.ignore();

            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            cout << endl;
            isExist = readFileAdmin("admindb.bin", username, password);

            bool validLogin = false;

            while(!validLogin)
            {
                if(isExist)
                {
                    validLogin = true;
                    adminPanel(isSystemOpen);
                }

                else
                {
                    cout << "Username or password is wrong!" << endl << endl;
                    break;
                }
            }
    }
    
    else if(number == 2)
    {
        cout << "Welcome to Professor Login!" << endl;;

            cin.ignore();

            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            cout << endl;
            Professor professor;
            isExist = readProfessorFile("professordb.bin", username, password, professor, false);

            bool validLogin = false;

            while(!validLogin)
            {
                if(isExist)
                {
                    validLogin = true;
                    professorPanel(professor, isSystemOpen);
                }

                else
                {
                    cout << "Username or password is wrong!" << endl << endl;
                    break;
                }
            }
    }
    
    else if(number == 3)
    {
        cout<< "Welcome to Assistant Login!" << endl << endl;

        cin.ignore();
        
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);
        cout << endl;

        Assistant assistant;
        isExist = readAssistantFile("assistantdb.bin", username, password, assistant, false);

        bool validLogin = false;

        while(!validLogin)
        {
            if(isExist)
            {
                validLogin = true;
                assitantPanel(assistant, isSystemOpen);
            }
            else
            {
                cout << "Username or password is wrong!" << endl << endl;
                break;
            }
        }
    }
    
    else if(number == 4)
    {
        cout << "Welcome to Student Login!" << endl;

            cin.ignore();

            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            cout << endl;
            Student student;
            isExist = readStudentFile("studentdb.bin", username, password, student, false);

            bool validLogin = false;

            while(!validLogin)
            {
                if(isExist)
                {
                    validLogin = true;
                    studentPanel(student, isSystemOpen);
                }

                else
                {
                    cout << "Username or password is wrong!" << endl << endl;
                    break;
                }
            }
    }

    else if(number == 5)
    {
        coursePanel();
    }
    
    else if(number == 6)
    {
        isSystemOpen = false;
    }
}








            