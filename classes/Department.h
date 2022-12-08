//
// Created by Dell on 12/8/2022.
//
#include "FileObject.h"
#include<bits/stdc++.h>
using namespace std;
#ifndef FILESASSIGNMENT_DEPARTMENT_H
#define FILESASSIGNMENT_DEPARTMENT_H
class Department : public FileObject{
private:
    string dept_ID;
    string dept_name;
    string dept_manager;
public:
    Department(const string &deptId = "", const string &deptName = "", const string &deptManager = "") : dept_ID(deptId),
                                                                                                         dept_name(deptName),
                                                                                                         dept_manager(deptManager) {}
    string out() override {
        return getDeptId() + "|" + getDeptName() + "|" + getDeptManager() + "|";
    }

    void in(string s) override {
        int i = 0;
        dept_ID = "";
        while (i < s.length() && s[i] != '|'){dept_ID += s[i++];}
        i++;
        dept_name = "";
        while (i < s.length() && s[i] != '|'){dept_name += s[i++];}
        i++;
        dept_manager = "";
        while (i < s.length() && s[i] != '|'){dept_manager += s[i++];}
    }

    const string &getDeptId() const {
        return dept_ID;
    }

    void setDeptId(const string &deptId) {
        dept_ID = deptId;
    }

    const string &getDeptName() const {
        return dept_name;
    }

    void setDeptName(const string &deptName) {
        dept_name = deptName;
    }

    const string &getDeptManager() const {
        return dept_manager;
    }

    void setDeptManager(const string &deptManager) {
        dept_manager = deptManager;
    }
    friend ostream& operator<<(ostream &out, const Department &department){
        out << "department ID: " << department.dept_ID << " "
            << "department name: " << department.dept_name << " "
            << "department manager: " << department.dept_manager << "\n";
        return out;
    }
    friend istream& operator>>(istream &in, Department &department){
        string read_data;
        cout<<"Enter Department ID: ";
        in>>read_data;
        department.setDeptId(read_data);
        cout<<"Enter Department Name: ";
        in>>read_data;
        department.setDeptName(read_data);
        cout<<"Enter Department Manager: ";
        in>>read_data;
        department.setDeptManager(read_data);
        return in;
    }
};
#endif //FILESASSIGNMENT_DEPARTMENT_H
