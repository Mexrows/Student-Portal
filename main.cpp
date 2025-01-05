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

void mainMenu();

int main()
{
    bool isSystemOpen = true;

    do
    {
        mainMenu();
    } while (isSystemOpen);
    


    return 0;
}

void mainMenu()
{
    cout << "******************************************" << endl;
    cout << "    University Management System" << endl;
    cout << "******************************************" << endl << endl;

    cout << "Please, press enter to continue!";
    cin.ignore();
    cout << endl << endl;
}

void loginScreen()
{
    cout << "******************************************" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Professor Login" << endl;
    cout << "3. Assistant Login" << endl;
    cout << "4. Student Login" << endl;
    cout << "5. Admin Login" << endl;
    cout << "6. Back to the main menu" << endl;
    cout << "7. Exit the system" << endl;
    cout << "******************************************" << endl;

    unsigned short number = 0;
}