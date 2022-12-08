//
// Created by Dell on 12/8/2022.
//
#include "Utilities.h"
#include "Index.h"
#include "File.h"
#include<bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <experimental/filesystem>
using namespace std;
#ifndef FILESASSIGNMENT_INDEXING_H
#define FILESASSIGNMENT_INDEXING_H
class Indexing {
public:
    static const int NOT_FOUND = -1;
    static int addIndex(Index index, string fileName){
        Utilities utilities;
        int pos = 0;
        Index temp;
        while(true){
            bool res = temp.readFromFile(fileName, pos, utilities.INDEXRECORDSIZE);
            if(!res){
                index.writeToFile(fileName, pos, utilities.INDEXRECORDSIZE);
                return pos;
                break;
            }
            else if(index.key <= temp.key){
                do{
                    index.writeToFile(fileName, pos, utilities.INDEXRECORDSIZE);
                    index = temp;
                    pos += utilities.INDEXRECORDSIZE;
                } while (temp.readFromFile(fileName, pos, utilities.INDEXRECORDSIZE));
                index.writeToFile(fileName, pos, utilities.INDEXRECORDSIZE);
                return pos;
                break;
            }
            pos += utilities.INDEXRECORDSIZE;
        }
    }
    static void addSecondaryIndex(Index index, string fileNameIndex, string fileListName){
        Utilities utilities;
        pair<string, int> res = searchIndex(index.key, fileNameIndex);
        string RRN = res.first;
        int pos = res.second;
        if(RRN == ""){
            Index inList(index.value, "-1");
            string posInList = inList.writeToFile(fileListName, FileObject::END, utilities.INDEXRECORDSIZE);
            Index inIndex(index.key, posInList);
            addIndex(inIndex, fileNameIndex);
        }
        else{
            Index inList(index.value, RRN);
            string posInList = inList.writeToFile(fileListName, FileObject::END, utilities.INDEXRECORDSIZE);
            Index inIndex(index.key, posInList);
            inIndex.writeToFile(fileNameIndex, pos, utilities.INDEXRECORDSIZE);
        }
    }
    static pair<string, int> searchIndex(string key, string fileName){
        Utilities utilities;
        File file;
        int n = file.records(fileName, utilities.INDEXRECORDSIZE);
        int start = 0;
        int end = n - 1;
        key.erase(key.find_last_not_of(" \n\r\t")+1);
        Index index;
        while(start <= end){
            int pos = (start + end) / 2;
            index.readFromFile(fileName, pos * utilities.INDEXRECORDSIZE, utilities.INDEXRECORDSIZE);
            index.key.erase(index.key.find_last_not_of(" \n\r\t")+1);
            if(key == index.key){
                return {index.value, pos * utilities.INDEXRECORDSIZE};
            }
            else if(key < index.key){
                end = pos - 1;
            }
            else{
                start = pos + 1;
            }
        }
        return {"", -1};
    }
    static pair< vector<string>, vector<int> > searchSecondaryIndex(string key, string fileNameIndex, string fileNameList){
        Utilities utilities;
        vector<string> myList;
        vector<int> positions;
        pair<string, int> res = searchIndex(key, fileNameIndex);
        string RRN = res.first;
        if(RRN == ""){
            return {myList, positions};
        }
        Index index;
        while (atoi(RRN.c_str()) != -1){
            if(!index.readFromFile(fileNameList, atoi(RRN.c_str()), utilities.INDEXRECORDSIZE)){
                return {myList, positions};
            }
            positions.push_back(atoi(RRN.c_str()));
            myList.push_back(index.key);
            RRN = index.value;
        }
        return {myList, positions};
    }
    static vector<int> getPositions(vector<string> keys, string filePrimaryIndex){
        vector<int> myList;
        pair<string, int> p;
        for(string key : keys){
            p = searchIndex(key, filePrimaryIndex);
            myList.push_back(atoi(p.first.c_str()));
        }
        return myList;
    }
    static void deletePrimaryIndex(string key, string fileName){
        pair<string, int> res = searchIndex(key, fileName);
        deletePrimaryIndex(res.second, fileName);
    }
    static void deletePrimaryIndex(int del, string fileName){
        File file;
        Utilities utilities;
        int pos = del + utilities.INDEXRECORDSIZE;
        Index temp;
        while(temp.readFromFile(fileName, pos, utilities.INDEXRECORDSIZE)){
            temp.writeToFile(fileName, del, utilities.INDEXRECORDSIZE);
            del = pos;
            pos += utilities.INDEXRECORDSIZE;
        }
        int newSize = file.fileSize(fileName) - utilities.INDEXRECORDSIZE;
        filesystem::resize_file(fileName.c_str(), newSize);
    }
};
#endif //FILESASSIGNMENT_INDEXING_H
