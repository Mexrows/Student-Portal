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
    Person();
    ~Person();
};

#endif