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
}
