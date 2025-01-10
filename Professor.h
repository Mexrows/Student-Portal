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
    void setSizeCourseProf(unsigned int sizeCourseProf);
    unsigned int getSizeCourseProf();
    ~Professor();

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

void Professor::setSizeCourseProf(unsigned int sizeCourseProf)
{
    this->sizeCourseProf = sizeCourseProf;
}

unsigned int Professor::getSizeCourseProf()
{
    return this->sizeCourseProf;
}

void writeProfessorFile(const string &fileName, Professor prof);
bool readProfessorFile(const string &fileName, string username, string password, Professor &prof, bool isExistCheck);
void professorPanel(Professor &professor, bool &isSystemOpen);
Professor* readAllProfessor(const string &fileName, int &numberOfProfessor);
bool doesCourseHaveProfessor(const string filename, int courseID);
void removeProfessor(const string &fileName, const string &username);

/*
1.username
2.password
3.sizeOfCourses
4.Course ID
*/
void writeProfessorFile(const string &fileName, Professor prof)
{
    ofstream file(fileName, ios::binary | ios::app);

    if(file.is_open())
    {
        size_t size = prof.getUsername().size();
        file.write((char*)&size, sizeof(size_t));
        file.write(prof.getUsername().data(), size);

        size = prof.getPassword().size();
        file.write((char*)&size, sizeof(size_t));
        file.write(prof.getPassword().data(), size);

        unsigned int sizeCourseProf = prof.getSizeCourseProf();
        file.write((char*)&sizeCourseProf, sizeof(unsigned int));

        int courseID = 0;
        for(unsigned int i = 0; i < sizeCourseProf; i++)
        {
            courseID = prof.courseProf[i].getId();
            file.write((char*)&courseID, sizeof(int));
        }
        file.close();
    }

    else
        cout << "Couldn't open the file!" << endl;
}

bool readProfessorFile(const string &fileName, string username, string password, Professor &prof, bool isExistCheck)
{
    ifstream file(fileName, ios::binary | ios::ate);
    if(file.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char[fileSize];
        file.read(mBlock, fileSize);
        file.close();
        char* p = mBlock;
        char* end = mBlock + fileSize;
        bool isExist = false;

        while(p < end)
        {
            //Username
            size_t sizeUsername = *((size_t*)p);
            p+=sizeof(size_t);

            char* bufferUsername = new char[sizeUsername + 1];
        
            for (size_t i = 0; i < sizeUsername; ++i) {
                bufferUsername[i] = *p++;
            }

            bufferUsername[sizeUsername] = '\0';
            string usernameString = bufferUsername;
            delete[] bufferUsername;

            if(isExistCheck)
            {
                if(username == usernameString)
                    return isExistCheck;
            }

            //Password
            size_t sizePassword = *((size_t*)p);
            p += sizeof(size_t);

            char* bufferPassword = new char[sizePassword + 1];

            for (size_t i = 0; i < sizePassword; ++i) {
                bufferPassword[i] = *p++;
            }

            bufferPassword[sizePassword] = '\0';
            string passwordString = bufferPassword;
            delete[] bufferPassword;

            //Check username and password
            if (usernameString == username && passwordString == password)
            {
                isExist = true;

                unsigned int sizeOfCourses = *((unsigned int*)p);
                p+=sizeof(unsigned int);

                prof.setUsername(usernameString);
                prof.setPassword(passwordString);
                prof.setSizeCourseProf(sizeOfCourses);
                prof.courseProf = new Course[sizeOfCourses];
                for(unsigned int i = 0; i < sizeOfCourses; i++)
                {
                    int id = *((int*)p);
                    p+=sizeof(int);
                    prof.courseProf[i].setId(id);
                }
                break;
            }
            
            unsigned int sizeOfCourses = *((unsigned int*)p);
            p += sizeof(unsigned int);

            p += sizeOfCourses * sizeof(int);
        }
        delete[] mBlock;
        return isExist;
                
    }
    else
        cout << "Couldn't open the file!" << endl;

    return false;
}

void professorPanel(Professor &professor, bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "Welcome to Professor Panel!" << endl;
    cout << "******************************************" << endl;
    cout << "1. View Courses" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "3. Exit the system" << endl;

    unsigned short number = 0;
    do
    {
        cout << "Enter the yout choice: ";
        cin >> number;
    } while (number < 0  || number > 3);
    
    if(number == 1)
    {
        cout << "Courses: " << endl;
        for(unsigned int i = 0; i < professor.getSizeCourseProf(); i++)
        {
            cout << "Course ID: " << professor.courseProf[i].getId() << endl;
        }
        return professorPanel(professor, isSystemOpen);
    }

    if(number == 2)
    {
        
    }

    if(number == 3)
    {
        isSystemOpen = false;
    }
}

Professor *readAllProfessor(const string &fileName, int &numberOfProfessor)
{
    Professor* tab;

    ifstream file(fileName, ios::binary | ios::ate);
    if(file.is_open())
    {   
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char[fileSize];
        file.read(mBlock, fileSize);
        file.close();
        char* p = mBlock;
        char* end = fileSize + mBlock;

        while(p < end)
        {
            size_t sizeUsername = *((size_t*)p);
            p+=sizeof(size_t);

            p += sizeUsername;

            size_t sizePassword = *((size_t*)p);
            p+=sizeof(size_t);

            p += sizePassword;

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p+=sizeof(unsigned int);

            p+=sizeOfCourses * sizeof(int) ;
            numberOfProfessor++;
        }

        p = mBlock;
        end = fileSize + mBlock;
        tab = new Professor[numberOfProfessor];

        for(int i = 0; i<numberOfProfessor; i++)
        {
           
            size_t sizeUsername = *((size_t*)p);
            p+=sizeof(size_t);

            char* bufferUsername = new char[sizeUsername + 1];
        
            for (size_t i = 0; i < sizeUsername; ++i) {
                bufferUsername[i] = *p++;
            }

            bufferUsername[sizeUsername] = '\0';
            string usernameString = bufferUsername;
            delete[] bufferUsername;

            size_t sizePassword = *((size_t*)p);
            p+=sizeof(size_t);

            char* bufferPassword = new char[sizePassword + 1];

            for (size_t i = 0; i < sizePassword; ++i) {
                bufferPassword[i] = *p++;
            }

            bufferPassword[sizePassword] = '\0';
            string passwordString = bufferPassword;
            delete[] bufferPassword;

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p+=sizeof(unsigned int);

            tab[i].setUsername(usernameString);
            tab[i].setPassword(passwordString);
            tab[i].setSizeCourseProf(sizeOfCourses);
            tab[i].courseProf = new Course[sizeOfCourses];
            for(unsigned int j = 0; j < sizeOfCourses; j++)
            {
                int id = *((int*)p);
                p+=sizeof(int);
                tab[i].courseProf[j].setId(id);
            }

        }
        delete[] mBlock;
    }
    else
        cout << "Couldn't open the file!" << endl;

    return tab;
}

bool doesCourseHaveProfessor(const string filename, int courseID)
{
    ifstream file(filename, ios::binary | ios::ate);
 
    if(file.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char [fileSize];
        file.read(mBlock, fileSize);
        file.close();

        char* p = mBlock;
        char* end = mBlock + fileSize;

        while(p < end)
        {
            size_t sizeUsername = *((size_t*)p);
            p += sizeof(size_t);
            p += sizeUsername;

            size_t sizePassword = *((size_t*)p);
            p += sizeof(size_t);
            p += sizePassword;

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p += sizeof(unsigned int);

            for(unsigned int i = 0; i < sizeOfCourses; i++)
            {
                int fileCourseID = *((int*)p);
                p += sizeof(int);

                if(fileCourseID == courseID)
                {
                    delete[] mBlock;
                    return true;
                }
            }
        }

        delete[] mBlock;
    }

    else
    {
        cout << "File couldn't opened." << endl;
    }

    return false;
}

void removeProfessor(const string &fileName, const string &username)
{
    ifstream file(fileName, ios::binary | ios::ate);
    ofstream temp("temp.bin", ios::binary);

    if(file.is_open() && temp.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char [fileSize];
        file.read(mBlock, fileSize);
        file.close();
        char* p = mBlock;
        char* end = mBlock + fileSize;
        
        while(p < end)
        {
            size_t sizeUsername = *((size_t*)p);
            p += sizeof(size_t);

            char* bufferUsername = new char[sizeUsername + 1];
        
            for (size_t i = 0; i < sizeUsername; ++i) {
                bufferUsername[i] = *p++;
            }

            bufferUsername[sizeUsername] = '\0';
            string usernameString = bufferUsername;
            delete[] bufferUsername;

            size_t sizePassword = *((size_t*)p);
            p += sizeof(size_t);

            char* bufferPassword = new char[sizePassword + 1];

            for(size_t i = 0; i < sizePassword; ++i)
            {
                bufferPassword[i] = *p++;
            }

            bufferPassword[sizePassword] = '\0';
            string passwordString = bufferPassword;
            delete[] bufferPassword;

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p += sizeof(unsigned int);

            Course* courses = new Course [sizeOfCourses];

            for(unsigned int i = 0; i < sizeOfCourses; i++)
            {
                int id = *((int*)p);
                p += sizeof(int);
                courses[i].setId(id);
            }

            if(username != usernameString)
            {
                temp.write((char*)&sizeUsername, sizeof(size_t));
                temp.write(usernameString.data(), sizeUsername);
                temp.write((char*)&sizePassword, sizeof(size_t));
                temp.write(passwordString.data(), sizePassword);
                temp.write((char*)&sizeOfCourses, sizeof(unsigned int));

                for(unsigned int i = 0; i < sizeOfCourses; i++)
                {
                    int courseID = courses[i].getId();
                    temp.write((char*)&courseID, sizeof(int));
                }
            }
        }

        delete[] mBlock;
        temp.close();

        remove(fileName.data());
        rename("temp.bin", fileName.data());
    }

    else
    {
        cout << "Files couldn't opened!" << endl;
    }

    
}
#endif