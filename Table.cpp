#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
using namespace std;

class Table {
public:
    vector<string> attributeNames;
    vector<vector<string>> data;
    vector<vector<string>> attributeValues;

    void extractAttributeValues() {
        attributeValues.resize(attributeNames.size());

        for (int i = 0; i < attributeNames.size(); ++i) {
            map<string, int> values;
            for (int j = 0; j < data.size(); ++j) {
                values[data[j][i]] = 1;
            }

            for (const auto& val : values) {
                attributeValues[i].push_back(val.first);
            }
        }
    }
};