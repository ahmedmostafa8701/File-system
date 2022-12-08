//
// Created by Dell on 12/7/2022.
//
#include<bits/stdc++.h>
using namespace std;
#ifndef FILESASSIGNMENT_DELETED_H
#define FILESASSIGNMENT_DELETED_H
class Deleted{
public:
    char mark;
    char delimet;
    int length;
    int RRN;

    Deleted(char mark, char delimet, int len, int rrn) : mark(mark), delimet(delimet), length(len), RRN(rrn) {}
    Deleted(char mark, char delimet = '|'){
        this->mark = mark;
        this->delimet = delimet;
    }
    void writeToFile(string fileName, int pos){
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary | ios::out);
        stream.seekp(pos);
        string s = "";
        s += mark;
        s += to_string(RRN);
        s += delimet;
        s += to_string(length);
        s += delimet;
        stream.write(s.c_str(), s.length());
        stream.close();
    }
    void readFromFile(string fileName, int pos) {
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary | ios::out);
        stream.seekg(pos);
        stream >> mark;
        string s = "";
        char ch;
        while (true){
            stream >> ch;
            if(ch == delimet){
                break;
            }
            s += ch;
        }
        RRN = atoi(s.c_str());
        string len = "";
        while (true){
            stream >> ch;
            if(ch == delimet){
                break;
            }
            len += ch;
        }
        length = atoi(len.c_str());
        stream.close();
    }
};
#endif //FILESASSIGNMENT_DELETED_H
