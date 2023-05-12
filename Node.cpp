#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
using namespace std;

class Node {
public:
    int criteriaIndex;
    string attributeValue;

    int treeIndex;
    bool isLeaf;
    string classification;

    vector<int> childIndices;

    Node() {
        isLeaf = false;
    }
};