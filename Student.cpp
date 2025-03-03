// Annika Brown
// 2428684
// annbrown@chapman.edu
// CPSC350
// PA5
// student class
// creates a student

#include <iostream>
#include "Student.h"

// default constructor
Student::Student() {
    m_ID = 0;
    m_name = "NO NAME";
    m_level = "graduate";
    m_major = "sleep";
    m_GPA = 10.0;
    m_advisor = 0;
}

// overload constructor
Student::Student(int id, std::string name, std::string level, std::string major, double GPA, int advisor) {
    m_ID = id;
    m_name = name;
    m_level = level;
    m_major = major;
    m_GPA = GPA;
    m_advisor = advisor;
}

// overload constructor
Student::Student(int id) {
    m_ID = id;
    m_name = "temp";
}

// default destructor
Student::~Student() {
    
}

// prints the student's info
void Student::print() {
    std::cout << m_name << std::endl
    << "Student ID: " << m_ID << std::endl
    << "Level: " << m_level << std::endl
    << "Major: " << m_major << std::endl
    << "GPA: " << m_GPA << std::endl
    << "Advisor ID: " << m_advisor << std::endl;
}

// overloads << operator
std::ostream& operator<<(std::ostream &s, const Student &student) {
    return s << "\n" << student.m_name << std::endl
    << "Student ID: " << student.m_ID << std::endl
    << "Level: " << student.m_level << std::endl
    << "Major: " << student.m_major << std::endl
    << "GPA: " << student.m_GPA << std::endl
    << "Advisor ID: " << student.m_advisor << std::endl;
}
