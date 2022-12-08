//
// Created by Dell on 12/8/2022.
//
#include "FileObject.h"
#include<bits/stdc++.h>
using namespace std;
#ifndef FILESASSIGNMENT_EMPLOYEE_H
#define FILESASSIGNMENT_EMPLOYEE_H
class Employee : public FileObject{
private:
    string employee_ID;
    string dept_ID;
    string employee_name;
    string employee_position;
public:

    Employee(const string &employeeId = "", const string &deptId = "", const string &employeeName = "", const string &employeePosition = "")
            : employee_ID(employeeId), dept_ID(deptId), employee_name(employeeName),
              employee_position(employeePosition) {}
    string out() override {
        return getEmployeeId() + "|" + getDeptId() + "|" + getEmployeeName() + "|" + getEmployeePosition() + "|";
    }

    void in(string s) override {
        int i = 0;
        employee_ID = "";
        while (i < s.length() && s[i] != '|'){employee_ID += s[i++];}
        i++;
        dept_ID = "";
        while (i < s.length() && s[i] != '|'){dept_ID += s[i++];}
        i++;
        employee_name = "";
        while (i < s.length() && s[i] != '|'){employee_name += s[i++];}
        i++;
        employee_position = "";
        while (i < s.length() && s[i] != '|'){
            employee_position += s[i++];
        }
    }
    const string &getEmployeeId() const {
        return employee_ID;
    }

    void setEmployeeId(const string &employeeId) {
        employee_ID = employeeId;
    }

    const string &getDeptId() const {
        return dept_ID;
    }

    void setDeptId(const string &deptId) {
        dept_ID = deptId;
    }

    const string &getEmployeeName() const {
        return employee_name;
    }

    void setEmployeeName(const string &employeeName) {
        employee_name = employeeName;
    }

    const string &getEmployeePosition() const {
        return employee_position;
    }

    void setEmployeePosition(const string &employeePosition) {
        employee_position = employeePosition;
    }
    friend ostream& operator<<(ostream &out, const Employee &employee){
        out << "Employee ID: " << employee.employee_ID << " "
            << "Employee name: " << employee.employee_name << " "
            << "Employee position: " << employee.employee_position << " "
            << "Department ID: " << employee.dept_ID << "\n";
        return out;
    }
    friend istream& operator>>(istream &in, Employee &employee){
        string read_data;
        cout<<"Enter Employee ID: ";
        in>>read_data;
        employee.setEmployeeId(read_data);
        cout<<"Enter Employee Department ID: ";
        in>>read_data;
        employee.setDeptId(read_data);
        cout<<"Enter Employee Name: ";
        in>>read_data;
        employee.setEmployeeName(read_data);
        cout<<"Enter Employee Position: ";
        in>>read_data;
        employee.setEmployeePosition(read_data);
        return in;
    }
};
#endif //FILESASSIGNMENT_EMPLOYEE_H
