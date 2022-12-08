//
// Created by Dell on 12/8/2022.
//
#include<bits/stdc++.h>
using namespace std;
#ifndef FILESASSIGNMENT_FRONTEND_H
#define FILESASSIGNMENT_FRONTEND_H
class FrontEnd{
private:
    list<string> menu_list;
public:
    FrontEnd(){
        menu_list.emplace_back("Add new Employee");
        menu_list.emplace_back("Add new Department");
        menu_list.emplace_back("Delete Employee (ID)");
        menu_list.emplace_back("Delete Department (ID)");
        menu_list.emplace_back("Print Employee (ID)");
        menu_list.emplace_back("Print Employee (Dept_ID)");
        menu_list.emplace_back("Print Department (ID)");
        menu_list.emplace_back("Print Department (name)");
        menu_list.emplace_back("Write a Query");
        menu_list.emplace_back("Exit");
    }
    int show_menu(){
        int cnt = 1;
        for(auto & i : menu_list){
            cout<<cnt++;
            cout<<")";
            cout<<i+"\n";
        }
        int choice = -1;
        cout<<"Enter your Choice: ";
        cin>>choice;
        while(!(0<choice&&choice<=menu_list.size())){
            cout<<"*************************************\n";
            cout<<"Wrong choice number, please try again: ";
            cin>>choice;
        }
        return choice;
    }
};
#endif //FILESASSIGNMENT_FRONTEND_H
