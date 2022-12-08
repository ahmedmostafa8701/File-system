//
// Created by Dell on 12/7/2022.
//
#include<bits/stdc++.h>
using namespace std;
#ifndef FILESASSIGNMENT_UTILITIES_H
#define FILESASSIGNMENT_UTILITIES_H


class Utilities {
public:
    const int INDEXFIELDSIZE = 20;
    const int INDEXRECORDSIZE = INDEXFIELDSIZE * 2;
    const int LENGTHOFLENGTH = 2;
    const int HEADER_LENGTH = 20;
    const int RRN_LENGTH = HEADER_LENGTH;
    const int HEADER_POSITION = 0;
    const int RRN_POSITION = 0;
    string RRN = "-1";
    string DEFAULT_RRN = RRN.insert(RRN.length(), Utilities::RRN_LENGTH - RRN.length(), ' ');
};


#endif //FILESASSIGNMENT_UTILITIES_H
