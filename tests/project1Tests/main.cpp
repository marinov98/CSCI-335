/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool isCorrectPosition(int pos) {
	return (pos == 1 || pos == 4 || pos == 7 || pos == 8 || pos == 10 || pos == 25 || pos == 26
	        || pos == 30 || pos == 38 || pos == 39);
}

vector<string> split(string const& in) {
	int pos = 1;
	vector<string> result;
	string s = "";
	for (int i = 0; i < in.size(); i++) {
		if (in[i] != ',' && isCorrectPosition(pos)) {
			s += in[i];
		}
		else {
			if (isCorrectPosition(pos)) {
				result.push_back(s);
				s = "";
			}
			pos++;
		}
	}

	if (!s.empty()) {
		result.push_back(s);
	}

	return result;
}

int main() {
	ifstream parser;
	parser.open("testcsv.txt");
	string reader;

	vector<string> extractor;
	while (getline(parser, reader)) {
		extractor.push_back(reader);
	}

	vector<string> tester = split(extractor[0]);

	int i = 0;
	for (string s : tester) {
		cout << " index:" << i++ << " value:" << s << '\n';
	}

	return 0;
}
