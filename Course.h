#ifndef COURSE_H
#define COURSE_H
#include <string>

using namespace std;


class Course
{
    private:
    string name;
    int id;

    public:
    Course();
    ~Course();
    Course(const Course &obj);
    Course(string, int);

    string getName()
    {
        return this->name;
    }

    int getId()
    {
        return this->id;
    }
};

Course::Course(string name, int id)
{
    this->name = name;
    this->id = id;
}




#endif