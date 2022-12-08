//
// Created by Dell on 12/8/2022.
//
#include "Utilities.h"
#include "FileObject.h"
#include "Deleted.h"
#include "Header.h"
#include<bits/stdc++.h>
using namespace std;
#ifndef FILESASSIGNMENT_AVAILLIST_H
#define FILESASSIGNMENT_AVAILLIST_H
class AvailList{
public:
    const static int END = -1;
    static string addFirstFit(FileObject *object, const string &fileName){
        Utilities utilities;
        int length = (*object).out().length();
        string s = Header::getHeader(fileName);
        int pos = atoi(s.c_str());
        int prev = pos;
        int prevLen = -1;
        while(pos != -1){
            Deleted deleted('*', '|');
            deleted.readFromFile(fileName, pos);
            if(deleted.length >= length){
                if(prevLen == -1){
                    Header::addHeader(fileName, to_string(deleted.RRN));
                }
                else{
                    Deleted added('*', '|', prevLen, deleted.RRN);
                    added.writeToFile(fileName, prev);
                }
                (*object).writeToFile(fileName, pos);
                return to_string(pos);
            }
            prev = pos;
            prevLen = deleted.length;
            pos = deleted.RRN;
        }
        return (*object).writeToFile(fileName, FileObject::END);
    }
    static void addAvailList(string fileName, int pos){
        Utilities utilities;
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary | ios :: out);
        stream.seekp(pos , ios::beg);
        stream.write(utilities.DEFAULT_RRN.c_str(), utilities.DEFAULT_RRN.length());
        stream.close();
    }
};
#endif //FILESASSIGNMENT_AVAILLIST_H
