#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "Person.h"

using namespace std;

class Student: public Person
{
    private:
        unsigned int id;
        unsigned short gpa;
        string* course; // Student Course
    
    public:
    Student();
    ~Student();
    Student(const Student &obj);
    Student(string, string, unsigned int, unsigned short);


};

Student::Student()
:Person()
{
    this->id = 0;
    this->gpa = 0;
}


Student::Student(string password, string username, unsigned int id, unsigned short gpa)
:Person(password, username)
{
    this->id = id;
    this->gpa = gpa;

};

#endif