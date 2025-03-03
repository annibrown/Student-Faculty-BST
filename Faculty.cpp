// Annika Brown
// 2428684
// annbrown@chapman.edu
// CPSC350
// PA5
// faculty class
// creates a faculty member, 
// and modifies member variables

#include <iostream>
#include <list>
#include <string>
#include "Faculty.h"

// default constructor
Faculty::Faculty() {
    m_facultyID = 0;
    m_name = "Faculty";
    m_level = "worm";
    m_department = "sleep";
    m_advisees = new DblList<int>;
    strAdvisees = new std::string();
}

// overload constructor
Faculty::Faculty(int ID, std::string name, std::string level, std::string department) {
    m_facultyID = ID;
    m_name = name;
    m_level = level;
    m_department = department;
    m_advisees = new DblList<int>;
    strAdvisees = new std::string();
}

// overload constructor
Faculty::Faculty(int ID) {
    m_facultyID = ID;
    m_name = "";
    m_level = "";
    m_department = "";
    m_advisees = new DblList<int>;
    strAdvisees = new std::string();
}

// default destructor
Faculty::~Faculty() {
    
}

// print method
// prints out faculty member's info
// @param os, out stream
// @return void
void Faculty::print(std::ostream &os) {
    os << m_name << std::endl
    << "Faculty ID: " << m_facultyID << std::endl
    << "Level: " << m_level << std::endl
    << "Department: " << m_department << std::endl
    << "Advisee ID(s): ";
    m_advisees->print(os);
}

// updates StrAdvisees to match m_advisees
void Faculty::updateStrAdvisees() {
    strAdvisees->clear();
    if (m_advisees->isEmpty()) {
        return;
    }
    for (int i = 0; i < m_advisees->size(); i++) {
        strAdvisees->append(std::to_string(m_advisees->get(i)));
        if (i < m_advisees->size()-1) {
            strAdvisees->append(", ");
        }
    }
}

// adds an advisee to m_advisees
// @param ID, student ID to add
void Faculty::addAdvisee(int ID) {
    m_advisees->addBack(ID);
    updateStrAdvisees();
}

// removes an advisee from m_advisees
// @param ID, student ID to remove
void Faculty::removeAdvisee(int ID) {
    m_advisees->removeData(ID);
    updateStrAdvisees();
}
