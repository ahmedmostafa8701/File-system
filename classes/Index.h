//
// Created by Dell on 12/7/2022.
//
#include "FileObject.h"
#include "Utilities.h"
#include<bits/stdc++.h>
using namespace std;
#ifndef FILESASSIGNMENT_INDEX_H
#define FILESASSIGNMENT_INDEX_H


class Index : public FileObject{
public:
    string  key;
    string value;
    Index() = default;

    Index(const string &key, const string &value){
        setKey(key);
        setValue(value);
    }

    void setKey(const string &key) {
        Utilities utilities;
        Index::key = key;
        while (Index::key.length() < utilities.INDEXFIELDSIZE){
            Index::key += " ";
        }
    }

    void setValue(const string &value) {
        Utilities utilities;
        Index::value = value;
        while (Index::value.length() < utilities.INDEXFIELDSIZE){
            Index::value += " ";
        }
    }

    void in(string s) override {
        Utilities utilities;
        if(s.length() == 0){
            key = "";
            value = "";
        }
        key = s.substr(0, utilities.INDEXFIELDSIZE);
        value = s.substr(utilities.INDEXFIELDSIZE, utilities.INDEXFIELDSIZE);
    }
    string out() override {
        return key + value;
    }
};


#endif //FILESASSIGNMENT_INDEX_H
