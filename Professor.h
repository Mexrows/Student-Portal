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
    
}

#endif