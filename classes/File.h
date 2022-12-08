//
// Created by Dell on 12/8/2022.
//
#include<bits/stdc++.h>
#include <filesystem>
using namespace std;
#ifndef FILESASSIGNMENT_FILE_H
#define FILESASSIGNMENT_FILE_H
class File{
public:
    string employeeDateFile;
    string departmentDataFile;
    string secondaryDeptNameList;
    string primaryIndexEmployeeID;
    string primaryIndexDepartmentID;
    string secondaryIndexDepartmentID;
    string secondaryIndexDepartmentName;
    string secondaryDeptIDList;
    list<string> dirs;
    list<string> files;
    File() {
        employeeDateFile = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\DataFiles\\EmployeesDataFile.txt";
        departmentDataFile = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\DataFiles\\DepartmentsDataFile.txt";
        secondaryDeptNameList = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\secondaryIndexList\\secondaryDeptNameList.txt";
        primaryIndexEmployeeID = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\Indexes\\Primary_Index_EmployeeID.txt";
        primaryIndexDepartmentID = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\Indexes\\Primary_Index_DepartmentID.txt";
        secondaryIndexDepartmentID = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\Indexes\\Secondary_Index_DepartmentID.txt";
        secondaryIndexDepartmentName = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\Indexes\\Secondary_Index_DepartmentName.txt";
        secondaryDeptIDList = "C:\\Users\\Dell\\Desktop\\FileAssignmet\\secondaryIndexList\\SecondaryDeptIDList.txt";
        dirs = {"C:\\Users\\Dell\\Desktop\\FileAssignmet",
                "C:\\Users\\Dell\\Desktop\\FileAssignmet\\DataFiles",
                "C:\\Users\\Dell\\Desktop\\FileAssignmet\\secondaryIndexList",
                "C:\\Users\\Dell\\Desktop\\FileAssignmet\\Indexes"};
        files = {employeeDateFile, departmentDataFile, secondaryDeptNameList, primaryIndexEmployeeID,
                 primaryIndexDepartmentID, secondaryIndexDepartmentID, secondaryIndexDepartmentName, secondaryDeptIDList};
    }

    int records(string fileName, int len){
        return fileSize(fileName) / len;
    }
    int fileSize(string fileName){
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary| ios::out);
        stream.seekg(0, ios::end);
        int n = (int) stream.tellg();
        return n;
    }
    bool isEmpty(string fileName){
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary | ios::out);
        bool empty = stream.peek() == std::ifstream::traits_type::eof();
        stream.close();
        if(stream.peek() == std::ifstream::traits_type::eof()){
            return true;
        }
        return false;
    }
};
#endif //FILESASSIGNMENT_FILE_H
