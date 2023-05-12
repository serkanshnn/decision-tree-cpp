#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include "Table.h"
#include "Node.h"

using namespace std;

class DecisionTree {
	public:
		Table initialTable;
		vector<Node> tree;

		DecisionTree(Table table);

		string guess(vector<string> row);

		int dfs(vector<string>& row, int here);

		void run(Table table, int nodeIndex);

		double getEstimatedError(double f, int N);

		pair<string, int> getMajorityLabel(Table table);

		bool isLeafNode(Table table);

		int getSelectedAttribute(Table table);

		double getGainRatio(Table table, int attrIndex);

		double getInfoD(Table table);

		double getInfoAttrD(Table table, int attrIndex);

		double getGain(Table table, int attrIndex);

		double getSplitInfoAttrD(Table table, int attrIndex);

		void printTree(int nodeIndex, string branch);
};
