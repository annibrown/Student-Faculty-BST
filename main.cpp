// Annika Brown
// 2428684
// annbrown@chapman.edu
// CPSC350
// PA5
// main method

#include <iostream>
#include <fstream>
#include "TreeNode.h"
#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

int main() {
    // keep references to both the faculty and student tables in memory - references are simply LazyBST instances
    // Once the tables have been created, a menu should be presented to the user to allow them to manipulate the database
    LazyBST<Student>* students = new LazyBST<Student>();
    LazyBST<Faculty>* faculty = new LazyBST<Faculty>();
    Student newStudent;
    Student tempStudent;
    Faculty newFaculty;
    Faculty tempFaculty;
    int input = 0;
    int ID;
    int fID;
    int oldAdvisor;
    std::string name;
    std::string level;
    std::string major;
    double GPA;
    int advisorID;
    std::string department;
    // opens output file
    std::ofstream outFS;
    outFS.open("runLog.txt");
    // if output file is open it's very sad
    if (!outFS.is_open()) {
        std::cout << "Could not open file :(" << std::endl;
        return 1;
    }

    while (input != 11) {
        std::cout << std::endl;
        std::cout << "MENU: (enter an integer value)" << std::endl;
        std::cout << "1. Print all students and their information (sorted by ascending id #)" << std::endl;
        std::cout << "2. Print all faculty and their information (sorted by ascending id #)" << std::endl;
        std::cout << "3. Find and display student information given the student id" << std::endl;
        std::cout << "4. Find and display faculty information given the faculty id" << std::endl;
        std::cout << "5. Add a new student" << std::endl;
        std::cout << "6. Delete a student given the id" << std::endl;
        std::cout << "7. Add a new faculty member" << std::endl;
        std::cout << "8. Delete a faculty member given the id" << std::endl;
        std::cout << "9. Change a student’s advisor given the student id and the new faculty id" << std::endl;
        std::cout << "10. Remove an advisee from a faculty member given the ids" << std::endl;
        std::cout << "11. Exit" << std::endl;

        std::cin >> input;
        switch (input) {
            case 1:
                students->printInOrder();
                break;
            case 2:
                faculty->printInOrder();
                break;
            case 3:
                std::cout << "Enter Student ID: ";
                std::cin >> ID;
                tempStudent = Student(ID);
                if (students->contains(tempStudent)) {
                    students->get(tempStudent).print();
                } else {
                    std::cout << "That student doesn't exist" << std::endl;
                }
                break;
            case 4:
                std::cout << "Enter Faculty ID: ";
                std::cin >> ID;
                tempFaculty = Faculty(ID);
                if (faculty->contains(tempFaculty)) {
                    std::cout << faculty->get(tempFaculty);
                } else {
                    std::cout << "That faculty member doesn't exist" << std::endl;
                }
                break;
            case 5:
            // Add a new student
                std::cout << "Enter Student ID: ";
                std::cin >> ID;
                std::cout << std::endl;
                std::cout << "Enter Student Name: ";
                std::cin >> name;
                std::cout << std::endl;
                std::cout << "Enter Student Level (freshman, sophmore, etc.): ";
                std::cin >> level;
                std::cout << std::endl;
                std::cout << "Enter Student Major: ";
                std::cin >> major;
                std::cout << std::endl;
                std::cout << "Enter Student GPA: ";
                std::cin >> GPA;
                std::cout << std::endl;
                std::cout << "Enter Advisor ID: ";
                std::cin >> advisorID;
                if (faculty->contains(Faculty(advisorID))) {
                    newStudent = Student(ID, name, level, major, GPA, advisorID);
                    students->insert(newStudent, false);

                    // add student to faculty
                    tempFaculty = Faculty(advisorID);
                    faculty->get(tempFaculty).addAdvisee(ID);

                } else {
                    std::cout << "That faculty member doesn't exist, please create the faculty member first" << std::endl;
                }
                break;
            case 6:
            // Delete a student given the id
                std::cout << "Enter Student ID: ";
                std::cin >> ID;
                tempStudent = Student(ID);
                if (students->contains(tempStudent)) {
                    tempStudent = students->get(tempStudent);
                    oldAdvisor = tempStudent.m_advisor;
                    students->remove(tempStudent, false);

                    // remove from advisor's list
                    tempFaculty = Faculty(oldAdvisor);
                    faculty->get(tempFaculty).removeAdvisee(ID);
                } else {
                    std::cout << "That student doesn't exist" << std::endl;
                }
                break;
            case 7:
            // Add a new faculty member
                std::cout << "Enter Faculty ID: ";
                std::cin >> ID;
                std::cout << std::endl;
                std::cout << "Enter Faculty Name: ";
                std::cin >> name;
                std::cout << std::endl;
                std::cout << "Enter Faculty Level (lecturer, assistant prof, associate prof, etc.): ";
                std::cin >> level;
                std::cout << std::endl;
                std::cout << "Enter Faculty Department: ";
                std::cin >> department;
                std::cout << std::endl;
                newFaculty = Faculty(ID, name, level, department);
                faculty->insert(newFaculty, false);
                break;
            case 8:
            // Delete a faculty member given the id
                std::cout << "Enter Faculty ID: ";
                std::cin >> ID;
                tempFaculty = Faculty(ID);
                if (faculty->contains(tempFaculty)) {
                    tempFaculty = faculty->get(tempFaculty);
                    if (!(tempFaculty.m_advisees->isEmpty())) {
                    // assign their students new advisors
                        std::cout << "Who should be the new advisor for advisor " << ID << "'s students?" << std::endl;
                        std::cout << "Enter Faculty ID: ";
                        std::cin >> fID;
                        if (faculty->contains(Faculty(fID)) && fID != ID) {
                            for (int i = 0; i < tempFaculty.m_advisees->size(); i++) {
                                tempStudent = Student(tempFaculty.m_advisees->get(i));
                                tempStudent = students->get(tempStudent);
                                students->remove(tempStudent, true);
                                tempStudent = Student(tempStudent.m_ID, tempStudent.m_name, tempStudent.m_level, tempStudent.m_major, tempStudent.m_GPA, fID);
                                students->insert(tempStudent, true);
                                newFaculty = Faculty(fID);
                                faculty->get(newFaculty).addAdvisee(tempStudent.m_ID);
                            }
                        } else {
                            std::cout << "Not a valid Faculty ID" << std::endl;
                        }
                    }
                    faculty->remove(tempFaculty, false);
                } else {
                    std::cout << "That faculty member doesn't exist" << std::endl;
                }
                break;
            case 9:
            // Change a student’s advisor given the student id and the new faculty id
                std::cout << "Enter Student ID: ";
                std::cin >> ID;
                std::cout << std::endl << "Enter New Faculty ID: ";
                std::cin >> fID;
                if (students->contains(Student(ID)) && faculty->contains(Faculty(fID))) {
                    tempStudent = Student(ID);
                    tempStudent = students->get(tempStudent);
                    oldAdvisor = tempStudent.m_advisor;
              
                    students->remove(tempStudent, true);
                    tempStudent = Student(ID, tempStudent.m_name, tempStudent.m_level, tempStudent.m_major, tempStudent.m_GPA, fID);
                    students->insert(tempStudent, true); // goose dissappears :(

                    // delete student from old advisor
                    tempFaculty = Faculty(oldAdvisor);
                    faculty->get(tempFaculty).removeAdvisee(ID);

                    // add student to new advisor
                    tempFaculty = Faculty(fID);
                    faculty->get(tempFaculty).addAdvisee(ID);
                } else {
                    std::cout << "One of those people doesn't exist" << std::endl;
                }
        
                break;
            case 10:
            // Remove an advisee from a faculty member given the ids
                std::cout << "Enter Student ID: ";
                std::cin >> ID;
                std::cout << std::endl << "Enter Faculty ID: ";
                std::cin >> fID;
                if (students->contains(Student(ID)) && faculty->contains(Faculty(fID))) {
                    tempFaculty = Faculty(fID);
                    faculty->get(tempFaculty).removeAdvisee(ID);

                    // assign student new advisor
                    tempStudent = Student(ID);
                    tempStudent = students->get(tempStudent);
                    students->remove(tempStudent, true);
                    tempStudent.m_advisor = faculty->median().m_facultyID;
                    students->insert(tempStudent, false);
                } else {
                    std::cout << "One of those people doesn't exist" << std::endl;
                }
                break;
            case 11:
            // Exit
                students->outputInOrder(outFS);
                faculty->outputInOrder(outFS);
                break;
            default:
                std::cout << "invalid choice :(" << std::endl;
        }
    }
}
