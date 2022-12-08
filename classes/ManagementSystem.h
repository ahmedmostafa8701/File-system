//
// Created by Dell on 12/8/2022.
//
#include<bits/stdc++.h>
#include "Utilities.h"
#include "Employee.h"
#include "Department.h"
#include "FrontEnd.h"
#include "BackEnd.h"
using namespace std;
#ifndef FILESASSIGNMENT_MANAGEMENTSYSTEM_H
#define FILESASSIGNMENT_MANAGEMENTSYSTEM_H
class ManagementSystem{
private:
    string read_data;

public:

    void run(){
        FrontEnd front_end;
        File file;
        if(file.isEmpty(file.employeeDateFile)){
            Header::addHeader(file.employeeDateFile);
        }
        if(file.isEmpty(file.departmentDataFile)){
            Header::addHeader(file.departmentDataFile);
        }
        BackEnd back_end(file);
        while(true){
            int choice = front_end.show_menu();
            if(choice == 1){
                Employee employee;
                cin >> employee;
                back_end.add_new_employee(employee);
            }else if(choice == 2){
                Department department;
                cin >> department;
                back_end.add_new_department(department);
            }else if(choice == 3){
                cout<<"Enter Employee ID: ";
                cin>>read_data;
                back_end.delete_employee_ID(read_data);
            }else if(choice == 4){
                cout<<"Enter Department ID: ";
                cin>>read_data;
                back_end.delete_department_ID(read_data);
            }else if(choice == 5){
                Employee *res;
                cout<<"Enter employee ID: ";
                cin>>read_data;
                res = back_end.getEmployeeByID(read_data).first;
                if(res == nullptr){
                    cout << "not found\n";
                }
                else
                {
                    cout << *res;
                }
            }else if(choice == 6){
                vector<Employee> employees;
                cout<<"Enter Department ID: ";
                cin>>read_data;
                employees = back_end.getEmployeeByDeptID(read_data);
                if(employees.size() == 0){
                    cout << "not found\n";
                }
                else{
                    for (const auto &item: employees){
                        cout << item;
                    }
                }
            }else if(choice == 7){
                Department *res;
                cout<<"Enter Department ID: ";
                cin>>read_data;
                res = back_end.getDepartmentWithId(read_data).first;
                if(res == nullptr){
                    cout << "not found\n";
                }
                else
                {
                    cout << *res;
                }
            }else if(choice == 8){
                vector<Department> departments;
                cout<<"Enter Department Name: ";
                cin>>read_data;
                departments = back_end.getDepartmentWithName(read_data);
                if(departments.size() == 0){
                    cout << "not found\n";
                }
                else{
                    for (const auto &item: departments){
                        cout << item;
                    }
                }
            }else if(choice == 9){
                cout<<"Enter your Query: ";
                back_end.writeQuery();
            }else{
                cout<<"****************************************\n";
                cout<<"Program finished execution successfully\n";
                cout<<"****************************************\n";
                break;
            }
        }
    }
};
#endif //FILESASSIGNMENT_MANAGEMENTSYSTEM_H
