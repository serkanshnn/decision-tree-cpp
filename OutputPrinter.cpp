#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include "Table.h"
#include "Node.h"

using namespace std;

class OutputPrinter {
	private:
		ofstream fout;
	public:
		OutputPrinter(string filename) {
			fout.open(filename);
			if(!fout) {
				cout << filename << " file could not be opened\n";
				exit(0);
			}
		}

		string joinByTab(vector<string> row) {
			string ret = "";
			for(int i=0; i< row.size(); i++) {
				ret += row[i];
				if(i != row.size() -1) {
					ret += '\t';
				}
			}
			return ret;
		}

		void addLine(string str) {
			fout << str << endl;
		}
};