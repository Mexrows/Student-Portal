#ifndef ADMIN_H
#define ADMIN_H
#include "Person.h"

class Admin: public Person
{
    public:
    Admin();
    ~Admin();
    Admin(const Admin &obj);
    Admin(string, string);
};

Admin::Admin(string password, string username): Person(password, username)
{
    
};




#endif