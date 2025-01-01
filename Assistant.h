#ifndef ASISTANT_H
#define ASISTANT_H
#include "Professor.h"
#include "Student.h"

class Assistant: public Student, public Professor
{   
    public:
    Assistant();
    ~Assistant();
    Assistant(const Assistant &obj);
    Assistant(string, string, unsigned int, float);
};

Assistant::Assistant()
{
}

Assistant::~Assistant()
{
}

Assistant::Assistant(const Assistant &obj)
    : Student(obj), Professor(obj)
{
}

Assistant::Assistant(string password, string username, unsigned int id, float gpa)
:Student(password, username, id, gpa), Professor(password, username) 
{

};



#endif