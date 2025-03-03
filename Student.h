// Annika Brown
// 2428684
// annbrown@chapman.edu
// CPSC350
// PA5

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    public:
        // default constructor
        Student();
        // overload constructor
        Student(int id, std::string name, std::string level, std::string major, double GPA, int advisor);
        // overload constructor
        Student(int id);
        // default destructor
        ~Student();
        // prints student's info
        void print();

        // overload equality, less than, greater than operators
        bool operator== (const Student& other){return this->m_ID == other.m_ID;}
        bool operator< (const Student& other){return this->m_ID < other.m_ID;}
        bool operator> (const Student& other){return this->m_ID > other.m_ID;}

        // overload !=
        bool operator!= (const Student& other){return this->m_ID != other.m_ID;}

        // overload <<
        friend std::ostream& operator<<(std::ostream &s, const Student &student);

        // unique student ID (an integer)
        int m_ID;
        // string name field
        std::string m_name;
        // string level field (Freshman, Sophomore, etc.)
        std::string m_level;
        // string major field
        std::string m_major;
        // double GPA field
        double m_GPA;
        // integer advisor field, Faculty ID of their advisor
        int m_advisor;
};
#endif
