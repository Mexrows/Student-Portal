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

void mainMenu(bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "    University Management System" << endl;
    cout << "******************************************" << endl << endl;

    cout << "Please, press enter to continue!";
    cin.ignore();
    cout << endl << endl;
    loginScreen(isSystemOpen);
    
}

void loginScreen(bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Professor Login" << endl;
    cout << "3. Assistant Login" << endl;
    cout << "4. Student Login" << endl;
    cout << "5. Back to the main menu" << endl;
    cout << "6. Exit the system" << endl;
    cout << "******************************************" << endl;

    unsigned short number = 0;
    do
    {
        cout << "Enter the your choice: ";
        cin >> number;
    } while (number>8 && number<0);
    
    switch(number)
    {
        case 1:
            cout << "Welcome to Admin Login!";
            break;
        case 2:
            cout << "Welcome to Professor Login!";
            break;
        case 3:
            cout<< "Welcome to Assistant Login!";
            break;
        case 4:
            cout << "Welcome to Student Login!";
            break;
        case 5:
            mainMenu();
            break;
        case 6:
            isSystemOpen = false;
            break;
    }
}
