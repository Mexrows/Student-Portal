#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "Person.h"
#include "Course.h"

class Professor: public Person
{
    private:
    unsigned int sizeCourseProf;

    public:
    Course* courseProf;
    Professor();
    Professor(string, string);
    Professor(string, string, Course*);
    Professor(const Professor &obj);
    ~Professor();

    void setSizeCourseProf(unsigned int sizeCourseProf)
    {
        this->sizeCourseProf = sizeCourseProf;
    }
};

Professor::Professor()
:Person()
{
    this->courseProf = nullptr;
    this->sizeCourseProf = 0;
}

Professor::Professor(string password, string username)
:Person(password, username)
{
    this->sizeCourseProf = 0;
    this->courseProf = nullptr;
}

Professor::Professor(const Professor &obj)
:Person(obj)
{
    this->sizeCourseProf = obj.sizeCourseProf;
    this->courseProf = new Course[this->sizeCourseProf];

    for(unsigned short i = 0; i < this->sizeCourseProf; i++)
        this->courseProf[i] = obj.courseProf[i];
}

Professor::Professor(string password, string username, Course* courses)
:Person(password, username)
{
    this->courseProf = courses;

}

Professor::~Professor()
{
    this->sizeCourseProf = 0;
    delete[] courseProf;
    courseProf = nullptr;
}

#endif