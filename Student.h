#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "Person.h"

using namespace std;

class Student: public Person
{
    private:
    unsigned int id;
    float gpa;
    string* courseStudent; // Student Course
    unsigned sizeCourseStudent;
    
    public:
    Student();
    ~Student();
    Student(const Student &obj);
    Student(string, string, unsigned int, float);


};

Student::Student()
:Person()
{
    this->courseStudent = nullptr;
    this->sizeCourseStudent = 0;
    this->id = 0;
    this->gpa = 0;
}

Student::~Student()
{
    this->id = 0;
    this->gpa = 0;
    this->sizeCourseStudent = 0;
    delete[] courseStudent;
    this->courseStudent = nullptr;
}

Student::Student(const Student &obj)
:Person(obj)
{
    this->id = obj.id;
    this->gpa = obj.gpa;
    this->sizeCourseStudent = obj.sizeCourseStudent;

    this->courseStudent = new string[this->sizeCourseStudent];

    for(unsigned short i = 0; i < this->sizeCourseStudent; i++)
        this->courseStudent[i] = obj.courseStudent[i];
}

Student::Student(string password, string username, unsigned int id, float gpa)
:Person(password, username)
{
    this->id = id;
    this->gpa = gpa;
    this->sizeCourseStudent = 0;
    this->courseStudent = nullptr;
};

#endif