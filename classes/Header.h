//
// Created by Dell on 12/7/2022.
//
#include<bits/stdc++.h>
#include "Utilities.h"
using namespace std;
#ifndef FILESASSIGNMENT_HEADER_H
#define FILESASSIGNMENT_HEADER_H
class Header{
public:
    static void addHeader(string fileName, string s = ""){
        Utilities utilities;
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary | ios::out);
        stream.seekp(utilities.HEADER_POSITION, ios::beg);
        if(s.empty()){
            stream.write(utilities.DEFAULT_RRN.c_str(), utilities.DEFAULT_RRN.length());
        }
        else{
            stream.write(s.c_str(), s.length());
        }
        stream.close();
    }
    static void addHeader(list<string> fileNames){
        for (const auto &item: fileNames){
            addHeader(item);
        }
    }
    static string getHeader(string fileName){
        Utilities utilities;
        fstream stream;
        stream.open(fileName.c_str(), ios::in| ios::binary | ios::out);
        stream.seekg(utilities.HEADER_POSITION, ios::beg);
        char header[utilities.HEADER_LENGTH];
        stream.read(header, utilities.HEADER_LENGTH);
        stream.close();
        return header;
    }
    static int getRRN(string fileName){
        string header = getHeader(fileName);
        return atoi(header.c_str());
    }
};
#endif //FILESASSIGNMENT_HEADER_H
