#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "Person.h"

class Professor: public Person
{
    private:
    string* courseProf;
    unsigned int sizeCourseProf;

    public:
    Professor();
    Professor(string, string, unsigned int);
    Professor(const Professor &obj);
    ~Professor();
};

Professor::Professor()
:Person()
{
    this->courseProf = nullptr;
    this->sizeCourseProf = 0;
}

Professor::Professor(string password, string username, unsigned int)
:Person(password, username)
{
    this->sizeCourseProf = 0;
    this->courseProf = nullptr;
}

Professor::Professor(const Professor &obj)
:Person(obj)
{
    this->sizeCourseProf = obj.sizeCourseProf;
    this->courseProf = new string[this->sizeCourseProf];

    for(unsigned short i = 0; i < this->sizeCourseProf; i++)
        this->courseProf[i] = obj.courseProf[i];
}

Professor::~Professor()
{
    this->sizeCourseProf = 0;
    delete[] courseProf;
    courseProf = nullptr;
}

#endif