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

bool Person::login()
{
    string regName;
    string regPassword;

    cout << "Enter your username: ";
    getline(cin, regName);

    cout << "Enter your password: ";
    getline(cin, regPassword);

    bool verified = true;

    if(regName != this->username)
    {
        verified = false;
        return verified;
    }

    if(regPassword != this->password)
    {
        verified = false;
        return verified;
    }

    return verified;
    
}

#endif