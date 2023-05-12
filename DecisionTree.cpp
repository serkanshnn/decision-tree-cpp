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

		DecisionTree(Table table) {
			initialTable = table;
			initialTable.extractAttributeValues();

			Node root;
			root.treeIndex=0;
			tree.push_back(root);
			run(initialTable, 0);
			printTree(0, "");

			cout<< "<-- finish generating decision tree -->" << endl << endl;
		}

		string guess(vector<string> row) {
			string label = "";
			int leafNode = dfs(row, 0);
			if(leafNode == -1) {
				return "dfs failed";
			}
			label = tree[leafNode].classification;
			return label;
		}

		int dfs(vector<string>& row, int here) {
			if(tree[here].isLeaf) {
				return here;
			}

			int criteriaAttrIndex = tree[here].criteriaIndex;

			for(int i=0;i<tree[here].childIndices.size(); i++) {
				int next = tree[here].childIndices[i];

				if (row[criteriaAttrIndex] == tree[next].attributeValue) {
					return dfs(row, next);
				}
			}
			return -1;
		}

		void run(Table table, int nodeIndex) {
			if(isLeafNode(table) == true) {
				tree[nodeIndex].isLeaf = true;
				tree[nodeIndex].classification = table.data.back().back();
				return;
			}

			int selectedAttrIndex = getSelectedAttribute(table);

			map<string, vector<int> > attrValueMap;
			for(int i=0;i<table.data.size();i++) {
				attrValueMap[table.data[i][selectedAttrIndex]].push_back(i);
			}

			tree[nodeIndex].criteriaIndex = selectedAttrIndex;

			pair<string, int> majority = getMajorityLabel(table);
			if((double)majority.second/table.data.size() > 0.8) {
				tree[nodeIndex].isLeaf = true;
				tree[nodeIndex].classification = majority.first;
				return;
			}

			for(int i=0;i< initialTable.attributeValues[selectedAttrIndex].size(); i++) {
				string attrValue = initialTable.attributeValues[selectedAttrIndex][i];

				Table nextTable;
				vector<int> candi = attrValueMap[attrValue];
				for(int i=0;i<candi.size(); i++) {
					nextTable.data.push_back(table.data[candi[i]]);
				}

				Node nextNode;
				nextNode.attributeValue = attrValue;
				nextNode.treeIndex = (int)tree.size();
				tree[nodeIndex].childIndices.push_back(nextNode.treeIndex);
				tree.push_back(nextNode);

				// for empty table
				if(nextTable.data.size()==0) {
					nextNode.isLeaf = true;
					nextNode.classification = getMajorityLabel(table).first;
					tree[nextNode.treeIndex] = nextNode;
				} else {
					run(nextTable, nextNode.treeIndex);
				}
			}
		}

		double getEstimatedError(double f, int N) {
			double z = 0.69;
			if(N==0) {
				cout << ":: getEstimatedError :: N is zero" << endl;
				exit(0);
			}
			return (f+z*z/(2*N)+z*sqrt(f/N-f*f/N+z*z/(4*N*N)))/(1+z*z/N);
		}

		pair<string, int> getMajorityLabel(Table table) {
			string majorLabel = "";
			int majorCount = 0;

			map<string, int> labelCount;
			for(int i=0;i< table.data.size(); i++) {
				labelCount[table.data[i].back()]++;

				if(labelCount[table.data[i].back()] > majorCount) {
					majorCount = labelCount[table.data[i].back()];
					majorLabel = table.data[i].back();
				}
			}

			return {majorLabel, majorCount};
		}


		bool isLeafNode(Table table) {
			for(int i=1;i < table.data.size();i++) {
				if(table.data[0].back() != table.data[i].back()) {
					return false;
				}
			}
			return true;
		}

		int getSelectedAttribute(Table table) {
			int maxAttrIndex = -1;
			double maxAttrValue = 0.0;

			// except label
			for(int i=0; i< initialTable.attributeNames.size()-1; i++) {
				if(maxAttrValue < getGainRatio(table, i)) {
					maxAttrValue = getGainRatio(table, i);
					maxAttrIndex = i;
				}
			}

			return maxAttrIndex;
		}

		double getGainRatio(Table table, int attrIndex) {
			return getGain(table, attrIndex)/getSplitInfoAttrD(table, attrIndex);
		}

		double getInfoD(Table table) {
			double ret = 0.0;

			int itemCount = (int)table.data.size();
			map<string, int> labelCount;

			for(int i=0;i<table.data.size();i++) {
				labelCount[table.data[i].back()]++;
			}

			for(auto iter=labelCount.begin(); iter != labelCount.end(); iter++) {
				double p = (double)iter->second/itemCount;

				ret += -1.0 * p * log(p)/log(2);
			}

			return ret;
		}

		double getInfoAttrD(Table table, int attrIndex) {
			double ret = 0.0;
			int itemCount = (int)table.data.size();

			map<string, vector<int> > attrValueMap;
			for(int i=0;i<table.data.size();i++) {
				attrValueMap[table.data[i][attrIndex]].push_back(i);
			}

			for(auto iter=attrValueMap.begin(); iter != attrValueMap.end(); iter++) {
				Table nextTable;
				for(int i=0;i<iter->second.size(); i++) {
					nextTable.data.push_back(table.data[iter->second[i]]);
				}
				int nextItemCount = (int)nextTable.data.size();

				ret += (double)nextItemCount/itemCount * getInfoD(nextTable);
			}

			return ret;
		}

		double getGain(Table table, int attrIndex) {
			return getInfoD(table)-getInfoAttrD(table, attrIndex);
		}

		double getSplitInfoAttrD(Table table, int attrIndex) {
			double ret = 0.0;

			int itemCount = (int)table.data.size();

			map<string, vector<int> > attrValueMap;
			for(int i=0;i<table.data.size();i++) {
				attrValueMap[table.data[i][attrIndex]].push_back(i);
			}

			for(auto iter=attrValueMap.begin(); iter != attrValueMap.end(); iter++) {
				Table nextTable;
				for(int i=0;i<iter->second.size(); i++) {
					nextTable.data.push_back(table.data[iter->second[i]]);
				}
				int nextItemCount = (int)nextTable.data.size();

				double d = (double)nextItemCount/itemCount;
				ret += -1.0 * d * log(d) / log(2);
			}

			return ret;
		}

		/*
		 * Enumerates through all the nodes of the tree and prints all the branches 
		 */
		void printTree(int nodeIndex, string branch) {
			if (tree[nodeIndex].isLeaf == true)
				cout << branch << "Label: " << tree[nodeIndex].classification << "\n";

			for(int i = 0; i < tree[nodeIndex].childIndices.size(); i++) {
				int childIndex = tree[nodeIndex].childIndices[i];

				string attributeName = initialTable.attributeNames[tree[nodeIndex].criteriaIndex];
				string attributeValue = tree[childIndex].attributeValue;

				printTree(childIndex, branch + attributeName + " = " + attributeValue + ", ");
			}
		}
};
