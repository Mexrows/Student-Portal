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
    if(courseStudent != nullptr)
    {
        delete[] courseStudent;
        courseStudent = nullptr;
    }
    
    if(courseProf != nullptr)
    {
        delete[] courseProf;
        courseProf = nullptr;
    }
}

Assistant::Assistant(const Assistant &obj)
:Student(obj), Professor(obj)
{

}

Assistant::Assistant(string password, string username, unsigned int id, float gpa)
:Student(password, username, id, gpa), Professor(password, username) 
{

};

void writeAssistantFile(const string &fileName, Assistant assistant);
bool readAssistantFile(const string &fileName, string username, string password, Assistant &assistant);
void assitantPanel(Assistant &assistant, bool &isSystemOpen);

/*
    1.username
    2.password
    3.id
    4.gpa
    5.sizeOfCoursesProf
    6.Course ID Prof
    7.sizeOfCoursesStudent
    8.Course ID Student
*/

void writeAssistantFile(const string &fileName, Assistant assistant)
{
    ofstream file(fileName, ios::binary | ios::app);

    if(file.is_open())
    {
        size_t size = assistant.Student::getUsername().size();
        file.write((char*)&size, sizeof(size_t));
        file.write(assistant.Student::getUsername().data(), size);

        size = assistant.Student::getPassword().size();
        file.write((char*)&size, sizeof(size_t));
        file.write(assistant.Student::getPassword().data(), size);

        unsigned int id = assistant.getId();
        file.write((char*)&id, sizeof(unsigned int));

        float gpa = assistant.getGpa();
        file.write((char*)&gpa, sizeof(float));

        unsigned int sizeCourseProf = assistant.getSizeCourseProf();
        file.write((char*)&sizeCourseProf, sizeof(unsigned int));

        int courseIDProf = 0;
        for(unsigned int i = 0; i < sizeCourseProf; i++)
        {
            courseIDProf = assistant.courseProf[i].getId();
            file.write((char*)&courseIDProf, sizeof(int));
        }

        unsigned int sizeCourseStudent = assistant.getSizeCourseStudent();
        file.write((char*)&sizeCourseStudent, sizeof(unsigned int));

        int courseIDStudent = 0;
        for(unsigned int i = 0; i < sizeCourseStudent; i++)
        {
            courseIDStudent = assistant.courseStudent[i].getId();
            file.write((char*)&courseIDStudent, sizeof(int));
        }


        file.close();
        
    }

    else
        cout << "Couldn't open the file!" << endl;
}

/*
    1.username
    2.password
    3.id
    4.gpa
    5.sizeOfCoursesProf
    6.Course ID Prof
    7.sizeOfCoursesStudent
    8.Course ID Student
*/

bool readAssistantFile(const string &fileName, string username, string password, Assistant &assistant)
{
    ifstream file(fileName, ios::binary | ios::ate);

    if(file.is_open())
    {
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);
        char* mBlock = new char[fileSize];
        file.read(mBlock, fileSize);
        char *p = mBlock;
        char* endOfFile = mBlock + fileSize;

        bool isExist = false;
        while(p < endOfFile)
        {
            size_t sizeUsername = *((size_t*)p);
            p+=sizeof(size_t);

            string usernameString(p, sizeUsername);
            p+=sizeUsername;

            //Password
            size_t sizePassword = *((size_t*)p);
            p += sizeof(size_t);

            string passwordString(p, sizePassword);
            p += sizePassword;

            //Check username and password
            if (usernameString == username && passwordString == password)
            {
                isExist = true;

                unsigned int id = *((unsigned int*)p);
                p += sizeof(unsigned int);

                float gpa = *((float*)p);
                p += sizeof(float);

                unsigned int sizeCoursesProf = *((unsigned int*)p);
                p += sizeof(unsigned int);

                assistant.Student::setUsername(usernameString);
                assistant.Student::setPassword(password);
                assistant.setId(id);
                assistant.setGpa(gpa);
                assistant.setSizeCourseProf(sizeCoursesProf);
                assistant.courseProf = new Course [sizeCoursesProf];

                for(unsigned int i = 0; i < sizeCoursesProf; i++)
                {
                    int courseID = *((int*)p);
                    p += sizeof(int);

                    assistant.courseProf[i].setId(courseID);
                }

                unsigned int sizeCoursesStudent = *((unsigned int*)p);
                p += sizeof(unsigned int);

                assistant.setSizeCourseStudent(sizeCoursesStudent);
                assistant.courseStudent = new Course [sizeCoursesStudent];

                for(unsigned int i = 0; i < sizeCoursesStudent; i++)
                {
                    int courseID = *((int*)p);
                    p += sizeof(int);

                    assistant.courseStudent[i].setId(courseID);
                }

                break;
            }

            p += sizeof(unsigned int);
            p += sizeof(float);

            unsigned int sizeCoursesProf = *((unsigned int*)p);
            p += sizeof(unsigned int);
            p += sizeCoursesProf * sizeof(int);

            unsigned int sizeCoursesStudent = *((unsigned int*)p);
            p += sizeof(unsigned int);
            p += sizeCoursesStudent * sizeof(int);

        }

        delete[] mBlock;

        return isExist;
    }

    else
    {
        cout << "Couldn't open the file" << endl;
        return false;
    }
}

void assitantPanel(Assistant &assistant, bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "Welcome to Assistant Panel!" << endl;
    cout << "******************************************" << endl;
    cout << "1. View Courses" << endl;
    cout << "2. View Personal Information" << endl;
    cout << "3. Back to main menu" << endl;
    cout << "4. Exit the system" << endl;

    unsigned short number = 0;
    do
    {
        cout << "Enter the your choice: ";
        cin >> number;
    } while (number > 4);
    
    if(number == 1)
    {
        cout << "Courses that you learn: " << endl;
        for(unsigned int i = 0; i < assistant.getSizeCourseStudent(); i++)
        {
            cout << "Course ID: " << assistant.courseStudent[i].getId() << endl;
        }

        cout << "Courses that you teach: " << endl;
        for(unsigned int i = 0; i < assistant.getSizeCourseProf(); i++)
        {
            cout << "Course ID: " << assistant.courseProf[i].getId() << endl;
        }

        return assitantPanel(assistant, isSystemOpen);
    }

    if(number == 2)
    {
        cout << "Assistant ID: " << assistant.getId() << endl;
        cout << "Assistant Username: " << assistant.Student::getUsername() << endl;
        cout << "Student GPA: " << assistant.getGpa() << endl;
        return assitantPanel(assistant, isSystemOpen);
    }

    if(number == 3)
    {

    }

    if(number == 4)
    {
        isSystemOpen = false;
    }
}

#endif