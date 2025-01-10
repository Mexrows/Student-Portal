#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "Person.h"
#include "Course.h"

using namespace std;

class Student: public Person
{
    private:
    unsigned int id;
    float gpa;
    unsigned int sizeCourseStudent;
    
    public:
    Course* courseStudent; // Student Course
    Student();
    ~Student();
    Student(const Student &obj);
    Student(string, string, unsigned int, float);
    void setId(unsigned int id);
    void setGpa(float gpa);
    void setSizeCourseStudent(unsigned int sizeCourseStudent);
    unsigned int getId();
    float getGpa();
    unsigned int getSizeCourseStudent();
    void registerToCourse(Course &course);

};


void writeStudentFile(const string &fileName, Student student);
bool readStudentFile(const string &fileName, string username, string password, Student &student, bool isExistCheck);
Student *readStudentFileForCourses(const string &fileName, int &numberOfStudent, int courseID);
void removeStudent(const string &fileName, const string &username);
void updateStudentCourse(Student &student);
void studentPanel(Student &student, bool &isSystemOpen);
Student *readAllStudents(const string &fileName, int &numberOfStudent);



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

    this->courseStudent = new Course[this->sizeCourseStudent];

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

void Student::setId(unsigned int id)
{
    this->id = id;
}

void Student::setGpa(float gpa)
{
    this->gpa = gpa;
}

void Student::setSizeCourseStudent(unsigned int sizeCourseStudent)
{
    this->sizeCourseStudent = sizeCourseStudent;
}

unsigned int Student::getId()
{
    return this->id;
}

float Student::getGpa()
{
    return this->gpa;
}

unsigned int Student::getSizeCourseStudent()
{
    return this->sizeCourseStudent;
}

void Student::registerToCourse(Course &course)
{
    for(unsigned int i = 0; i < this->sizeCourseStudent; i++)
    {
        if(this->courseStudent[i].getId() == course.getId())
        {
            cout << "You already registered!" << endl;
            return;
        }
    }

    unsigned int sizeOfCourse = this->sizeCourseStudent + 1;

    Course* courses = new Course [sizeOfCourse];

    for(unsigned int i = 0; i < this->sizeCourseStudent; i++)
    {
        courses[i] = this->courseStudent[i];
    }

    courses[this->sizeCourseStudent] = course;

    delete[] this->courseStudent;

    this->courseStudent = courses;
    this->sizeCourseStudent = sizeOfCourse;

    cout << "The register is completed!" << endl;
}

/*
1.username
2.password
3.id
4.gpa
5.sizeOfCourses
6.Course ID
*/
void writeStudentFile(const string &fileName, Student student)
{
    ofstream file(fileName, ios::binary | ios::app);

    if(file.is_open())
    {
        size_t size = student.getUsername().size();
        file.write((char*)&size, sizeof(size_t));
        file.write(student.getUsername().data(), size);

        size = student.getPassword().size();
        file.write((char*)&size, sizeof(size_t));
        file.write(student.getPassword().data(), size);

        unsigned int id = student.getId();
        file.write((char*)&id, sizeof(unsigned int));

        float gpa = student.getGpa();
        file.write((char*)&gpa, sizeof(float));

        unsigned int sizeCourseProf = student.getSizeCourseStudent();
        file.write((char*)&sizeCourseProf, sizeof(unsigned int));

        int courseID = 0;
        for(unsigned int i = 0; i < sizeCourseProf; i++)
        {
            courseID = student.courseStudent[i].getId();
            file.write((char*)&courseID, sizeof(int));
        }
        file.close();
    }

    else
        cout << "Couldn't open the file!" << endl;
}

bool readStudentFile(const string &fileName, string username, string password, Student &student, bool isExistCheck)
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
            if(usernameString == username)
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

            unsigned int id = *((unsigned int*)p);
            p += sizeof(int);

            float gpa = *((float*)p);
            p += sizeof(float);

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p+=sizeof(unsigned int);

            student.setUsername(usernameString);
            student.setPassword(passwordString);
            student.setId(id);
            student.setGpa(gpa);
            student.setSizeCourseStudent(sizeOfCourses);
            student.courseStudent = new Course[sizeOfCourses];
            for(unsigned int i = 0; i < sizeOfCourses; i++)
            {
                int courseId = *((int*)p);
                p+=sizeof(int);
                student.courseStudent[i].setId(courseId);
            }
            break;
        }

            p += sizeof(int);
            p += sizeof(float);

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

Student *readStudentFileForCourses(const string &fileName, int &numberOfStudent, int courseID)
{
    Student* tab;
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

        while(p < end)
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
            p += sizeof(size_t);

            char* bufferPassword = new char[sizePassword + 1];

            for (size_t i = 0; i < sizePassword; ++i) {
                bufferPassword[i] = *p++;
            }

            bufferPassword[sizePassword] = '\0';
            string passwordString = bufferPassword;
            delete[] bufferPassword;

            p += sizeof(int);
            p += sizeof(float);

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p+=sizeof(unsigned int);

            for(unsigned int i = 0; i < sizeOfCourses; i++)
            {
                int courseId = *((int*)p);
                p+=sizeof(int);
                if(courseId == courseID)
                    numberOfStudent++;
            }
        }

        tab = new Student[numberOfStudent];
        p = mBlock;
        end = mBlock + fileSize;
        int indexStudent = 0;

        while(p < end)
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
            p += sizeof(size_t);

            char* bufferPassword = new char[sizePassword + 1];

            for (size_t i = 0; i < sizePassword; ++i) {
                bufferPassword[i] = *p++;
            }

            bufferPassword[sizePassword] = '\0';
            string passwordString = bufferPassword;
            delete[] bufferPassword;

            unsigned int id = *((unsigned int*)p);
            p += sizeof(int);

            p += sizeof(float);

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p+=sizeof(unsigned int);
            
            for(unsigned int i = 0; i < sizeOfCourses; i++)
            {
                int courseId = *((int*)p);
                p+=sizeof(int);
                if(courseId == courseID)
                {
                    tab[indexStudent].setUsername(usernameString);
                    tab[indexStudent].setId(id);
                    indexStudent++;
                }

            }
        }
        delete[] mBlock;
        return tab;
    }
    else
        cout << "Couldn't open the file!" << endl;

    return nullptr;
}

void removeStudent(const string &fileName, const string &username)
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

            unsigned int id = *((unsigned int*)p);
            p += sizeof(unsigned int);

            float gpa = *((float*)p);
            p += sizeof(float);

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
                temp.write((char*)&id, sizeof(unsigned int));
                temp.write((char*)&gpa, sizeof(float));
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


void updateStudentCourse(Student &student)
{
    removeStudent("studentdb.bin", student.getUsername());
    writeStudentFile("studentdb.bin", student);
}

void studentPanel(Student &student, bool &isSystemOpen)
{
    cout << "******************************************" << endl;
    cout << "Welcome to Student Panel!" << endl;
    cout << "******************************************" << endl;
    cout << "1. View Courses" << endl;
    cout << "2. View Personal Information" << endl;
    cout << "3. Register to a course" << endl;
    cout << "4. Back to main menu" << endl;
    cout << "5. Exit the system" << endl;

    unsigned short number = 0;
    do
    {
        cout << "Enter the your choice: ";
        cin >> number;
    } while (number < 0  || number > 5);
    
    if(number == 1)
    {
        cout << "Courses: " << endl;
        for(unsigned int i = 0; i < student.getSizeCourseStudent(); i++)
        {
            cout << "Course ID: " << student.courseStudent[i].getId() << endl;
        }
        return studentPanel(student, isSystemOpen);
    }

    if(number == 2)
    {
        cout << "Student ID: " << student.getId() << endl;
        cout << "Student Username: " << student.getUsername() << endl;
        cout << "Student GPA: " << student.getGpa() << endl;
        return studentPanel(student, isSystemOpen);
    }

    if(number == 3)
    {
        int courseID;

        cout << "Enter the course ID: ";
        cin >> courseID;

        Course course;
        bool isExist = readCourseFile("coursedb.bin", courseID, course);

        if(isExist)
        {
            student.registerToCourse(course);
            updateStudentCourse(student);
        }

        else
        {
            cout << "This course doens't exist!" << endl;
        }

        return studentPanel(student, isSystemOpen);
    }

    if(number == 5)
    {
        isSystemOpen = false;
    }
}
Student *readAllStudents(const string &fileName, int &numberOfStudent)
{
    Student* tab;

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

            p+=sizeUsername;

            size_t sizePassword = *((size_t*)p);
            p+=sizeof(size_t);

            p+=sizePassword;

            p += sizeof(int);

            p += sizeof(float);

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p+=sizeof(unsigned int);

            p+=sizeOfCourses * sizeof(int);
            numberOfStudent++;
        }

        p = mBlock;
        end = fileSize + mBlock;
        tab = new Student[numberOfStudent];

        for(int i = 0; i<numberOfStudent; i++)
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

            unsigned int id = *((unsigned int*)p);
            p += sizeof(int);

            float gpa = *((float*)p);
            p += sizeof(float);

            unsigned int sizeOfCourses = *((unsigned int*)p);
            p+=sizeof(unsigned int);

            tab[i].setUsername(usernameString);
            tab[i].setPassword(passwordString);
            tab[i].setId(id);
            tab[i].setGpa(gpa);
            tab[i].setSizeCourseStudent(sizeOfCourses);
            tab[i].courseStudent = new Course[sizeOfCourses];
            for(unsigned int j = 0; j < sizeOfCourses; j++)
            {
                int id = *((int*)p);
                p+=sizeof(int);
                tab[i].courseStudent[j].setId(id);
            }

        }
        delete[] mBlock;
    }
    else
        cout << "Couldn't open the file!" << endl;

    return tab;
}
#endif