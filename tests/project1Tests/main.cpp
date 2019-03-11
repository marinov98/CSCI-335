/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string> split(string const& in) {
	vector<string> result;
	string s = "";
	for (int i = 0; i < in.size(); i++) {
		if (in[i] != ',') {
			s += in[i];
		}

		else if (!s.empty()) {
			result.push_back(s);
			s = "";
		}
	}
	if (!s.empty()) {
		result.push_back(s);
	}

	return result;
}

int main() {
	const string Test = "5,,,4,,,Alive,,,Good,, Jap something,,,73";
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
		cout << " index:" << i++ << " value:" << s;
	}

	return 0;
}
