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
void adminPanel();

int main()
{
    string filename = "admindb.bin";

    writeFile(filename, "s2mle100sh", "1234");
    readFileAdmin(filename, "s2mle100sh", "1234");

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

    unsigned short number = 0;
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

void adminPanel()
{
    cout << "******************************************" << endl;
    cout << "Welcome to Admin Panel!" << endl;
    cout << "******************************************" << endl;
    cout << "1. Add Professor" << endl;
    cout << "2. Add Assistant" << endl;
    cout << "3. Add Student" << endl;

    unsigned short number = 0;
    
    do
    {
        if(number > 3 || number < 0)
        {
            cout << "Enter the number between 1 and 3" << endl;
        }
        cout << "Enter the choice: ";
        cin >> number;
    } while (number > 3 || number < 0);
    
    if(number == 1)
    {
        string username = "";
        string password = "";
        unsigned int numberOfCourse = 0;
        int courseID = 0;
        
        cout << "Write Username" << endl;
        cin >> username;
        cout << "Write Password" << endl;
        cin >> password;
        cout << "Write number of courses" << endl;
        cin >> numberOfCourse;

        Course* courses = new Course[numberOfCourse];
        for(int i = 0; i<numberOfCourse; i++)
        {
            cout << "Enter the " << i+1 << ". course ";
            cin >> courseID;
            courses[i].setId(courseID);
        }
           
        Professor p1(password, username);
        p1.courseProf = courses;
        p1.setSizeCourseProf(numberOfCourse);

        
    }
}
            