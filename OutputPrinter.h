#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>

using namespace std;

class OutputPrinter {
	private:
		ofstream fout;
	public:
		OutputPrinter(string filename);

		string joinByTab(vector<string> row);

		void addLine(string str);
};