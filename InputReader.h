#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include "Table.h"

using namespace std;
class InputReader {
	public:
		InputReader(string filename);
		void parse();
		Table getTable();
};