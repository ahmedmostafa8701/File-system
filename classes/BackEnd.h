//
// Created by Dell on 12/8/2022.
//
#include<bits/stdc++.h>
#include "Utilities.h"
#include "Employee.h"
#include "AvailList.h"
#include "Index.h"
#include "Indexing.h"
#include "Department.h"
#include "Header.h"

using namespace std;
#ifndef FILESASSIGNMENT_BACKEND_H
#define FILESASSIGNMENT_BACKEND_H
class BackEnd{
private:
    File file;
public:
    BackEnd(const File &file) : file(file) {}

    // 1 add new employee
    void add_new_employee(Employee tmp_emp){
        if(getEmployeeByID(tmp_emp.getEmployeeId()).first != NULL){
            cout << "This Id is already exist\n";
            return;
        }
        if(getDepartmentWithId(tmp_emp.getDeptId()).first == NULL){
            cout << "This department isn't exist\n";
            return;
        }
        string pos = AvailList::addFirstFit(&tmp_emp, file.employeeDateFile);
        Index primary(tmp_emp.getEmployeeId(), pos);
        Index secondaryIndex(tmp_emp.getDeptId(), tmp_emp.getEmployeeId());
        Indexing::addIndex(primary, file.primaryIndexEmployeeID);
        Indexing::addSecondaryIndex(secondaryIndex, file.secondaryIndexDepartmentID, file.secondaryDeptIDList);
    }

    // 2 add new department
    void add_new_department(Department tmp_dept){
        if(getDepartmentWithId(tmp_dept.getDeptId()).first != NULL){
            cout << "This Id is already exist\n";
            return;
        }
        string pos = AvailList::addFirstFit(&tmp_dept, file.departmentDataFile);
        Index primary(tmp_dept.getDeptId(), pos);
        Index secondary(tmp_dept.getDeptName(), tmp_dept.getDeptId());
        Indexing::addIndex(primary, file.primaryIndexDepartmentID.c_str());
        Indexing::addSecondaryIndex(secondary, file.secondaryIndexDepartmentName, file.secondaryDeptNameList);
    }

    // 3 delete employee (ID)
    void delete_employee_ID(string employee_ID){
        employee_ID.erase(employee_ID.find_last_not_of(" \n\r\t")+1);
        Utilities utilities;
        pair<Employee *, int> res = getEmployeeByID(employee_ID);
        Employee *employee = res.first;
        int pos = res.second;
        if(employee == nullptr){
            cout << "not found" << endl;
            return;
        }
        int rrn = Header::getRRN(file.employeeDateFile);
        Deleted deleted('*', '|', employee->out().length(), rrn);
        deleted.writeToFile(file.employeeDateFile, pos);
        string header = to_string(pos);
        Header::addHeader(file.employeeDateFile, header);
        Indexing::deletePrimaryIndex(employee_ID, file.primaryIndexEmployeeID);
        pair<vector<string>, vector<int> > p = Indexing::searchSecondaryIndex(employee->getDeptId(),
                                                                                 file.secondaryIndexDepartmentID,
                                                                                 file.secondaryDeptIDList);
        for (int i = 0; i < p.first.size(); i++) {
            p.first[i].erase(p.first[i].find_last_not_of(" \n\r\t")+1);
            if(p.first[i] == employee_ID){
/*                Indexing::deletePrimaryIndex(p.second[i], file.secondaryDeptIDList);*/
                if(i > 0 && i < p.first.size() - 1){
                    pair<string, int> prev = {p.first[i - 1], p.second[i - 1]};
                    pair<string, int> after = {p.first[i + 1], p.second[i + 1]};
                    Index pIndex(prev.first, to_string(after.second));
                    pIndex.writeToFile(file.secondaryDeptIDList, prev.second, utilities.INDEXRECORDSIZE);
                }
                else if(p.first.size() == 1){
                    Indexing::deletePrimaryIndex(employee->getDeptId(), file.secondaryIndexDepartmentID);
                }
                else if(i == p.first.size() - 1){
                    pair<string, int> prev = {p.first[i - 1], p.second[i - 1]};
                    Index pIndex(prev.first, to_string(-1));
                    pIndex.writeToFile(file.secondaryDeptIDList, prev.second, utilities.INDEXRECORDSIZE);
                }
                else{
                    pair<string, int> after = {p.first[i + 1], p.second[i + 1]};
                    pair<string, int> head = Indexing::searchIndex(employee->getDeptId(),
                                                                   file.secondaryIndexDepartmentID);
                    Index index(employee->getDeptId(), to_string(after.second));
                    index.writeToFile(file.secondaryIndexDepartmentID, head.second, utilities.INDEXRECORDSIZE);
                }
                break;
            }
        }
    }
    // 4 delete department (ID)
    void delete_department_ID(string dept_ID){
        Utilities utilities;
        pair<Department *, int> res = getDepartmentWithId(dept_ID);
        Department *department = res.first;
        int pos = res.second;
        if(department == nullptr){
            cout << "not found" << endl;
            return;
        }
        pair<vector<string>, vector<int> > p2 = Indexing::searchSecondaryIndex(department->getDeptId(),
                                                                               file.secondaryIndexDepartmentID,
                                                                               file.secondaryDeptIDList);
        for (int i = 0; i < p2.first.size(); i++) {
            delete_employee_ID(p2.first[i]);
        }
        int rrn = Header::getRRN(file.departmentDataFile);
        Deleted deleted('*', '|', department->out().length(), rrn);
        deleted.writeToFile(file.departmentDataFile, pos);
        string header = to_string(pos);
        Header::addHeader(file.departmentDataFile, header);
        Indexing::deletePrimaryIndex(dept_ID, file.primaryIndexDepartmentID);
        pair<vector<string>, vector<int> > p = Indexing::searchSecondaryIndex(department->getDeptName(),
                                                                              file.secondaryIndexDepartmentName,
                                                                              file.secondaryDeptNameList);
        for (int i = 0; i < p.first.size(); i++) {
            p.first[i].erase(p.first[i].find_last_not_of(" \n\r\t")+1);
            if(p.first[i] == dept_ID){
                /*Indexing::deletePrimaryIndex(p.second[i], file.secondaryDeptNameList);*/
                if(i > 0 && i < p.first.size() - 1){
                    pair<string, int> prev = {p.first[i - 1], p.second[i - 1]};
                    pair<string, int> after = {p.first[i + 1], p.second[i + 1]};
                    Index pIndex(prev.first, to_string(after.second));
                    pIndex.writeToFile(file.secondaryDeptNameList, prev.second, utilities.INDEXRECORDSIZE);
                }
                else if(p.first.size() == 1){
                    Indexing::deletePrimaryIndex(department->getDeptName(), file.secondaryIndexDepartmentName);
                }
                else if(i == p.first.size() - 1){
                    pair<string, int> prev = {p.first[i - 1], p.second[i - 1]};
                    Index pIndex(prev.first, to_string(-1));
                    pIndex.writeToFile(file.secondaryDeptNameList, prev.second, utilities.INDEXRECORDSIZE);
                }
                else{
                    pair<string, int> after = {p.first[i + 1], p.second[i + 1]};
                    pair<string, int> head = Indexing::searchIndex(department->getDeptName(),
                                                                   file.secondaryIndexDepartmentName);
                    Index index(department->getDeptName(), to_string(after.second));
                    index.writeToFile(file.secondaryIndexDepartmentName, head.second, utilities.INDEXRECORDSIZE);
                }
                break;
            }
        }
    }
    pair<Employee*, int> getEmployeeByID(string employee_ID){
        Employee *employee = new Employee;
        string res = Indexing::searchIndex(employee_ID, file.primaryIndexEmployeeID).first;
        if(res == ""){
            return {nullptr, -1};
        }
        int pos = atoi(res.c_str());
        (*employee).readFromFile(file.employeeDateFile, pos);
        return {employee, pos};
    }
    vector<Employee> getEmployeeByDeptID(string dept_ID){
        vector<string> keys = Indexing::searchSecondaryIndex(dept_ID, file.secondaryIndexDepartmentID, file.secondaryDeptIDList).first;
        vector<int> positions = Indexing::getPositions(keys, file.primaryIndexEmployeeID);
        vector<Employee> employees(positions.size());
        int i = 0;
        for (auto position: positions){
            employees[i++].readFromFile(file.employeeDateFile, position);
        }
        return employees;
    }
    pair<Department*, int> getDepartmentWithId(string dept_ID){
        Department *department = new Department;
        string res = Indexing::searchIndex(dept_ID, file.primaryIndexDepartmentID).first;
        if(res == ""){
            return {nullptr, -1};
        }
        int pos = atoi(res.c_str());
        (*department).readFromFile(file.departmentDataFile, pos);
        return {department, pos};
    }
    vector<Department> getDepartmentWithName(string dept_name){
        vector<string> keys = Indexing::searchSecondaryIndex(dept_name, file.secondaryIndexDepartmentName, file.secondaryDeptNameList).first;
        vector<int> positions = Indexing::getPositions(keys, file.primaryIndexDepartmentID);
        vector<Department> departments(positions.size());
        int i = 0;
        for (auto position: positions){
            departments[i++].readFromFile(file.departmentDataFile, position);
        }
        return departments;
    }

    // 9 write a query
    void writeQuery(){
        string select;
        cin >> select;
        trans(select);
        if(select != "select"){
            cout << "invalid input\n";
            return;
        }
        string selection;
        cin >> selection;
        trans(selection);
        string from;
        cin >> from;
        trans(from);
        string table;
        cin >> table;
        trans(table);
        string where;
        cin >> where;
        trans(where);
        string attribute;
        cin >> attribute;
        trans(attribute);
        char eq;
        cin >> eq;
        string value;
        cin >> value;
        if(from != "from" || eq != '=' || where != "where"){
            cout << "invalid input\n";
            return;
        }
        if(table == "employee"){
            vector<Employee> employees;
            if(attribute == "employee_id"){
                Employee *res = getEmployeeByID(value).first;
                if(res != nullptr){
                    Employee employee = *res;
                    employees.push_back(employee);
                }
            }
            else if(attribute == "dept_id"){
                vector<Employee> res = getEmployeeByDeptID(value);
                for (const auto &item: res){
                    employees.push_back(item);
                }
            }
            else{
                cout << "invalid input\n";
                return;
            }
            if(selection == "all"){
                for (const auto &item: employees){
                    cout << item;
                }
            }
            else if(selection == "employee_id"){
                for (const auto &item: employees){
                    cout << item.getEmployeeId() << endl;
                }
            }
            else if(selection == "dept_id"){
                for (const auto &item: employees){
                    cout << item.getDeptId() << endl;
                }
            }
            else if(selection == "employee_position"){
                for (const auto &item: employees){
                    cout << item.getEmployeePosition() << endl;
                }
            }
            else if(selection == "employee_name"){
                for (const auto &item: employees){
                    cout << item.getEmployeeName() << endl;
                }
            }
            else{
                cout << "invalid input\n";
                return;
            }
        } else if(table == "department"){
            vector<Department> departments;
            if(attribute == "dept_id"){
                Department *res = getDepartmentWithId(value).first;
                if(res != nullptr){
                    Department department = *res;
                    departments.push_back(department);
                }
            }
            else if(attribute == "dept_name"){
                vector<Department> res = getDepartmentWithName(value);
                for (const auto &item: res){
                    departments.push_back(item);
                }
            }
            else{
                cout << "invalid input\n";
                return;
            }
            if(selection == "all"){
                for (const auto &item: departments){
                    cout << item;
                }
            }
            else if(selection == "dept_id"){
                for (const auto &item: departments){
                    cout << item.getDeptId() << endl;
                }
            }
            else if(selection == "dept_name"){
                for (const auto &item: departments){
                    cout << item.getDeptName() << endl;
                }
            }
            else if(selection == "dept_manager"){
                for (const auto &item: departments){
                    cout << item.getDeptManager() << endl;
                }
            }
            else{
                cout << "invalid input\n";
                return;
            }
        }
        else{
            cout << "invalid input\n";
            return;
        }
    }
    static void trans(string &s){
        transform(s.begin(), s.end(), s.begin(), ::tolower);
    }
};
#endif //FILESASSIGNMENT_BACKEND_H
