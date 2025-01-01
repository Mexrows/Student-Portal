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
    
    Student();
    ~Student();
    Student(const Student &obj);
    Student(unsigned int, unsigned short);


};


Student::Student(unsigned int id, unsigned short gpa)
{
    this->id = id;
    this->gpa = gpa;

};

#endif