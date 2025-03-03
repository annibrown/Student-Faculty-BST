// Annika Brown
// 2428684
// annbrown@chapman.edu
// CPSC350
// PA5
// faculty class
// creates a faculty member, 
// and modifies member variables

#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <list>
#include <iostream>
#include "DblList.h"

class Faculty {
    public:
        // default constructor
        Faculty();
        // overload constructor
        Faculty(int ID, std::string name, std::string level, std::string department);
        // overload constructor
        Faculty(int ID);
        // default destructor
        ~Faculty();
        // prints an advisee's info
        void print(std::ostream &os);
        // updates strAdvisees to match m_advisees
        void updateStrAdvisees();
        void addAdvisee(int ID);
        void removeAdvisee(int ID);

        // overload equality, less than, greater than operators
        bool operator== (const Faculty& other){return this->m_facultyID == other.m_facultyID;}
        bool operator< (const Faculty& other){return this->m_facultyID < other.m_facultyID;}
        bool operator> (const Faculty& other){return this->m_facultyID > other.m_facultyID;}

        // overload !=
        bool operator!= (const Faculty& other){return this->m_facultyID != other.m_facultyID;}

        // overload <<
        friend std::ostream& operator<<(std::ostream &s, const Faculty &faculty) {
            return s << "\n" << faculty.m_name << "\nFaculty ID: " << faculty.m_facultyID << "\nLevel: " << faculty.m_level << "\nDepartment: " << faculty.m_department << "\nAdvisee ID(s): " << faculty.strAdvisees->data();
        }

        // integer Faculty ID
        int m_facultyID;
        // string name
        std::string m_name;
        // string level (lecturer, assistant prof, associate prof, etc.)
        std::string m_level;
        // string department
        std::string m_department;
        // list of integers corresponding to all of the faculty member’s advisees’ ids
        DblList<int>* m_advisees;
        std::string* strAdvisees;
};
#endif
