#include<bits/stdc++.h>
#include <filesystem>
#include "classes/ManagementSystem.h"
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
void createFiles(){
    File file;
    for (const auto &item: file.dirs){
        mkdir(item.c_str());
    }
    for (const auto &item: file.files){
        fstream stream;
        stream.open(item.c_str(), ios::out | ios::app);
        stream.close();
    }
}
int main(){
    createFiles();
    ManagementSystem managementSystem;
    managementSystem.run();
    return 0;
}
