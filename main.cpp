#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include "InputReader.h"
#include "OutputPrinter.h"
#include "DecisionTree.h"

using namespace std;

int main(int argc, const char * argv[]) {
	if(argc!=4) {
		cout << "[dt_train.txt] [dt_test.txt] [dt_answer.txt]";
		return 0;
	}

	string trainFileName = argv[1];
	InputReader trainInputReader(trainFileName);
	DecisionTree decisionTree(trainInputReader.getTable());

	string testFileName = argv[2];
	InputReader testInputReader(testFileName);
	Table test = testInputReader.getTable();

	string resultFileName = argv[3];
	OutputPrinter outputPrinter(resultFileName);
	outputPrinter.addLine(outputPrinter.joinByTab(test.attributeNames));
	for(int i=0;i < test.data.size(); i++) {
		vector<string> result = test.data[i];
		result.push_back(decisionTree.guess(test.data[i]));
		outputPrinter.addLine(outputPrinter.joinByTab(result));
	}

	InputReader answerInputReader("dt_answer1.txt");
	Table answer = answerInputReader.getTable();
	int totalCount = (int)answer.data.size();
	int hitCount = 0;
	for(int i=0;i < test.data.size(); i++) {
	if(answer.data[i].back() == decisionTree.guess(test.data[i])) {
	hitCount++;
	}
	}
	cout << "Accuracy: " << (double)hitCount/totalCount*100 << "%";
	cout << "(" << hitCount << "/" << totalCount << ")" << endl;
	   
	return 0;
}
