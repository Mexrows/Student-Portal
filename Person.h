#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person
{
    private:
    string password;
    string username;

    public:
    //Constructor and Destructors
    Person();
    Person(string, string);
    Person(const Person &obj);
    ~Person();
    void setPassword(string password);
    void setUsername(string username);
    string getPassword();
    string getUsername();

    //Helper Functions
    bool login(); //Login
};

Person::Person()
{
    this->password = "";
    this->username = "";
}

Person::Person(string password, string username)
{
    this->password = password;
    this->username = username;
}

Person::Person(const Person &obj)
{
    this->password = obj.password;
    this->username = obj.username;
}

Person::~Person()
{

}

void Person::setPassword(string password)
{
    this->password = password;
}

void Person::setUsername(string username)
{
    this->username = username;
}

string Person::getPassword()
{
    return this->password;
}

string Person::getUsername()
{
    return this->username;
}

bool Person::login()
{
    string logName;
    string logPassword;

    cout << "Enter your username: ";
    getline(cin, logName);

    cout << "Enter your password: ";
    getline(cin, logPassword);

    bool verified = true;

    if(logName != this->username)
    {
        verified = false;
        return verified;
    }

    if(logPassword != this->password)
    {
        verified = false;
        return verified;
    }

    return verified;
    
}

#endif