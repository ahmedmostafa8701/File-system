//
// Created by Dell on 12/7/2022.
//
#include<bits/stdc++.h>
#include "Utilities.h"
#ifndef FILESASSIGNMENT_FILEOBJECT_H
#define FILESASSIGNMENT_FILEOBJECT_H
using namespace std;

class FileObject {
public:
    static const int LEN = -1;
    static const int BEG = -1;
    static const int END = -2;
    virtual string out() = 0;
    virtual void in(string s) = 0;
    string writeToFile(string fileName, int pos, int len = LEN){
        static Utilities utilities;
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary| ios::out);
        if(pos == BEG){
            stream.seekp(0, ios::beg);
        }
        else if(pos == END){
            stream.seekp(0, ios::end);
            stream.seekg(0, ios::end);
        }
        else{
            stream.seekp(pos);
        }
        pos = stream.tellp();
        string buffer = out();
        if(len == LEN){
            len = (int) buffer.length();
            string lenOut = to_string(len);
            while(lenOut.size() < utilities.LENGTHOFLENGTH){
                lenOut += " ";
            }
            stream << lenOut;
        }
        stream.write(buffer.c_str(),len);
        stream.close();
        return to_string(pos);
    }
    bool readFromFile(string fileName, int pos, int len = LEN){
        static Utilities utilities;
        fstream stream;
        stream.open(fileName.c_str(), ios::in | ios::binary| ios::out);
        stream.seekg(pos);
        if(stream.peek() == std::ifstream::traits_type::eof()){
            stream.close();
            return false;
        }
        if(len == LEN){
            char lenChar[utilities.LENGTHOFLENGTH];
            stream.read(lenChar, utilities.LENGTHOFLENGTH);
            if(strlen(lenChar) == 0){
                stream.close();
                return false;
            }
            len = atoi(lenChar);
        }
        char buffer[len];
        stream.read(buffer,len);
        if(strlen(buffer) == 0){
            stream.close();
            return false;
        }
        in(buffer);
        stream.close();
        return true;
    }

};


#endif //FILESASSIGNMENT_FILEOBJECT_H
