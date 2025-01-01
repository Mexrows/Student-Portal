#ifndef ASISTANT.H
#define ASISTANT.H
#include "Professor.h"
#include "Student.h"

class Assistant: public Student, public Professor
{   
    public:
    Assistant();
    ~Assistant();
    Assistant(const Assistant &obj);
    Assistant(string, string);
};

Assistant::Assistant(string password, string username): Person(password,username)
{

};





#endif