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

    string getName();
    int getId();
    void setId(int id);
    void setName(string name);


    
};


Course::Course()
{
    this->name = "";
    this->id = 0;
}

Course::~Course()
{

}

Course::Course(const Course &obj)
{
    this->name = obj.name;
    this->id = obj.id;
}

Course::Course(string name, int id)
{
    this->name = name;
    this->id = id;
}

string Course::getName()
{
    return this->name;
}

int Course::getId()
{
    return this->id;
}

void Course::setId(int id)
{
    this->id = id;
}

void Course::setName(string name)
{
    this->name = name;
}

void writeCourseFile(const string &fileName, Course &course);
bool readCourseFile(const string &fileName, int id, Course &course);
void coursePanel();
Course* readAllCourseFile(const string &fileName, unsigned int &numberOfCourses, bool &isExist);

/*
1. Name
2. Id
*/
void writeCourseFile(const string &fileName, Course &course)
{
    ofstream file(fileName, ios::binary | ios::app);

    if(file.is_open())
    {
        size_t size = course.getName().size();
        file.write((char*)&size, sizeof(size_t));
        file.write(course.getName().data(), size);

        int id = course.getId();
        file.write((char*)&id, sizeof(int));
        
        file.close();
    }

    else
        cout << "Couldn't open the file!" << endl;
}

bool readCourseFile(const string &fileName, int id, Course &course)
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
        //Course Name
        size_t sizeName = *((size_t*)p);
        p+=sizeof(size_t);

        string nameString(p, sizeName);
        p+=sizeName;

        //Course ID
        int id = *((int*)p);
        p += sizeof(int);
        
        if(id == course.getId() || nameString == course.getName())
        {
            isExist = true;
            course.setId(id);
            course.setName(nameString);
            delete[] mBlock;
            return isExist;
        }
        }
        delete[] mBlock;
        return isExist;
    }
    else
        cout << "Couldn't open the file!" << endl;

    return false;
}

void coursePanel()
{
    unsigned short number = 0;

    cout << "******************************************" << endl;
    cout << "Welcome to Course Panel!" << endl;
    cout << "******************************************" << endl;
    cout << "1. View Courses" << endl;

    do
    {
        if(number < 0 || number > 1)
        {
            cout << "Enter the number between 1 and 1" << endl;
        }
        cout << "Enter the your choice: ";
        cin >> number;
    } while (number < 0 || number > 1);
    
    if(number == 1)
    {
        unsigned int numberOfCourses = 0;
        bool isExist = false;
        Course* allCourses = readAllCourseFile("coursedb.bin", numberOfCourses, isExist);
        if(isExist)
        {
            cout << "******************************************" << endl;
            for(int i = 0; i<numberOfCourses; i++)
            {
                cout << i+1 << ". Course: "<< allCourses[i].getName() << ", " << allCourses[i].getId() << endl;
            }
            /*
            cout << "******************************************" << endl;
            unsigned short number2 = 0;
            do
            {
                cout << "Select the course that you want to view";
                cin >> number2;
            } while (number < 0 || number > numberOfCourses);
            
            cout << "Course Name: " << allCourses[number2-1].getName() << endl;
            cout << "Course Id: " << allCourses[number2-1].getId() << endl;
            int numberOfStudent = 0;
            Student* studentList = readStudentFileForCourses("studentdb.bin", numberOfStudent, allCourses[number2-1].getId());
            cout << "Course Student List: " << endl;
            for(int j = 0; j<numberOfStudent; j++)
            {
                cout << j+1 << ". Student: " << studentList[j].getUsername() << endl;
            }
            */
        
        }
        else
            cout << "Course not found!" << endl;
    }

}
Course *readAllCourseFile(const string &fileName, unsigned int &numberOfCourses, bool &isExist)
{
    Course* tab;
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
        if(fileSize != 0)
            isExist = true;

        while(p < end)
        {
        //Course Name
        size_t sizeName = *((size_t*)p);
        p+=sizeof(size_t);

        string nameString(p, sizeName);
        p+=sizeName;

        //Course ID
        int id = *((int*)p);
        p += sizeof(int);
        numberOfCourses++;
        }

        p = mBlock;
        tab = new Course[numberOfCourses];
        for(int i = 0; i<numberOfCourses; i++)
        {
            //Course Name
            size_t sizeName = *((size_t*)p);
            p+=sizeof(size_t);

            string nameString(p, sizeName);
            p+=sizeName;

            //Course ID
            int id = *((int*)p);
            p += sizeof(int);
            tab[i].setId(id);
            tab[i].setName(nameString);
        }
        delete[] mBlock;
    }
    else
        cout << "Couldn't open the file!" << endl;
    return tab;
}
#endif