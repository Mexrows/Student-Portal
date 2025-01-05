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
void writeFile(const string &fileName, string username, string password);
bool readFileAdmin(const string &fileName, string username, string password);

int main()
{
    string filename = "admindb.bin";

    bool isSystemOpen = true;

    do
    {
        mainMenu(isSystemOpen);

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
    cout << "5. Exit the system" << endl;
    cout << "******************************************" << endl;

    unsigned short number = 1;
    do
    {
        if(number > 5 || number < 0)
        {
            cout << "You should enter the number between 1 and 5" << endl;
        }
        cout << "Enter the your choice: ";
        cin >> number;
    } while (number>5 || number<0);
    
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
            isSystemOpen = false;
            break;
        default:
            isSystemOpen = false;
            break;
    }
}

void writeFile(const string &fileName, string username, string password)
{
    ofstream file(fileName, ios::binary | ios::app);

    if(file.is_open())
    {
        size_t size = username.size();
        file.write((char*)&size, sizeof(size_t));
        file.write(username.data(), size);

        size_t size = password.size();
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

        size_t sizeUsername = *((size_t*)p);
        p+=sizeof(size_t);

        char* usernameChar = new char[sizeUsername];
        file.read(usernameChar, sizeUsername);
        string usernameString = usernameChar;




        delete[] usernameChar;
    }
    
}
