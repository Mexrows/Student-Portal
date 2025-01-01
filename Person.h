#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person
{
    string password;
    string username;

    //Constructor and Destructors
    Person();
    Person(string, string);
    Person(const Person &obj);
    ~Person();
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

#endif