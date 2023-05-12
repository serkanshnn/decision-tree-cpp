#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
using namespace std;

#ifndef FILE_1_H
#define FILE_1_H
class Table
{
public:
    vector<string> attributeNames;
    vector<vector<string>> data;
    vector<vector<string>> attributeValues;
    void extractAttributeValues();
};
#endif
