
/*******************************************************************************
  Title          : tree_collection.h
  Author         : Marin Pavlinov Marinov
  Created on     : February 22, 2019
  Description    : Cpp file for the tree class
  Purpose        : Implement the tree class
  Usage          :
  Build with     : No building
  Modifications  :

*******************************************************************************/
#include "tree.h"
#include <fstream>
#include <vector>

Tree::Tree() {
	this->tree_id = -1;
	this->tree_dbh = -1;
	this->status = "";
	this->health = "";
	this->spc_common = "";
	this->zipcode = -1;
	this->address = "";
	this->boroname = "";
	this->latitude = 0;
	this->longitude = 0;
}

// function that checks if we are at the right position
bool isCorrectPosition(int pos) {
	return (pos == 1 || pos == 4 || pos == 7 || pos == 8 || pos == 10 || pos == 25 || pos == 26
	        || pos == 30 || pos == 38 || pos == 39);
}

//helper function that splits a string on commas
vector<string> split(string const& in) {
	int pos = 1;

	vector<string> result;
	// reserve 10 spots for the 10 fields (OPTIMIZATION REASONS ONLY)
	result.reserve(10);

	string s = "";
	for (int i = 0; i < in.size(); i++) {
		if (in[i] != ',' && isCorrectPosition(pos)) {
			s += in[i];
		}
		else { // only load into vector if we are at the right position
			if (isCorrectPosition(pos)) {
				result.push_back(s);
				s = "";
			} // increment the position whenever we encounter a comma
			pos++;
		}
	}

	if (!s.empty()) {
		result.push_back(s);
	}

	return result;
}

bool validate (int id,
           int diam,
           string stat,
           string hlth,
           string name,
           int zip,
           string addr,
           string boro,
           double lat,
           double longtd) {
	bool invalid = false;

	//diameter/id check
	if (diam < 0 || id < 0) {
		invalid = false;
	}

	//status check
	if (stat != "Alive" || stat != "Dead" ||
		stat != "Stump" || stat != "") {
		invalid = true;
	}

	// health check
	if (hlth != "Good" || hlth != "Fair" ||
		hlth != "Poor" || hlth != "") {
		invalid = true;
	}
	// address check
	if (!addr.empty()) {
		invalid = true;
	}

	// zipcode check
	if (zip < 0 || zip > 99999) {
		invalid = true;
	}

	// borough check
	if(boro != "Manhattan" || boro != "Bronx" ||
		boro != "Queens" || boro != "Brooklyn" ||
		boro != "Staten Island") {
		invalid = true;
	}

	return invalid;
}

Tree::Tree(const string& str) {
	ifstream csvfile;
	try {
		csvfile.open(str);
	}
	catch (int e) {
		cout << "cannot read from" << str << '\n';
	}

	// variable to help extract entire string from file
	string reader;

	// a vector to extra the file as a string
	vector<string> extractor;

	// retrieve file as single string
	while(getline(csvfile,reader)) {
		extractor.push_back(reader);
	}

	// vector to split the extractor by commas
	vector<string> splitter = split(extractor[0]);

	// Validate
	if (validate(stoi(splitter[0]),stoi(splitter[1]),splitter[2],splitter[3],
			splitter[4],stoi(splitter[5]),splitter[6],splitter[7],
			stod(splitter[8]),stod(splitter[9]))) {
		// If the values were validated, then create new tree object with them
		Tree(stoi(splitter[0]),stoi(splitter[1]),splitter[2],splitter[3],
		         splitter[4],stoi(splitter[5]),splitter[6],splitter[7],
		         stod(splitter[8]),stod(splitter[9]));
	}
	else { // if they are not valid then create empty tree
		Tree();
	}

}

Tree::Tree(int id,
           int diam,
           string stat,
           string hlth,
           string name,
           int zip,
           string addr,
           string boro,
           double lat,
           double longtd) {
	this->tree_id = id;
	this->tree_dbh = diam;
	this->status = stat;
	this->health = hlth;
	this->spc_common = name;
	this->zipcode = zip;
	this->address = addr;
	this->boroname = boro;
	this->latitude = lat;
	this->longitude = longtd;

}

ostream& operator<<(ostream& os, const Tree& t) {
	os  << " common name:" << t.spc_common
		<< " id:" << t.tree_id
		<< " diameter: " << t.tree_dbh
		<< " status:" << t.status
		<< " health:" << t.health
		<< " zipcode:" << t.zipcode
		<< " address:" << t.address
		<< " borough:" << t.boroname
		<< " latitude:" << t.latitude
		<< " longitude:" << t.longitude;

	return os;
}

bool operator==(const Tree& t1, const Tree& t2) {
	return (samename(t1,t2) && t1.id() == t2.id());
}

bool operator<(const Tree& t1, const Tree& t2) {
	return (islessname(t1,t2) ||
	        (samename(t1,t2) && (t1.id() < t2.id())));
}

bool samename(const Tree& t1, const Tree& t2) {
	bool same = true;

	// if length is different, then we already know they are not the same
	if (t1.spc_common.size() != t2.spc_common.size()) {
		same = false;
	} // else convert every character to lowercase (to avoid case sensitivity) and compare them
	else {
		for (int i = 0; i < t1.spc_common.size(); i++) {
			if (tolower(t1.spc_common[i] != tolower(t2.spc_common[i]))) {
				same = false;
				break;
			}
		}
	}

	return same;
}

bool islessname(const Tree& t1, const Tree& t2) {
	string t1common = "";
	string t2common = "";
	// fill the two strings with the lowercase version of the common names
	for (int i = 0; i < t1.spc_common.length(); i++)
		t1common += (char)tolower(t1.spc_common[i]);

	for (int j = 0; j < t2.spc_common.length(); j++)
		t2common += (char)tolower(t2.spc_common[j]);
	// compare the strings without worrying about case
	return (t1common < t2common);
}

string Tree::common_name() const {
	return spc_common;
}

string Tree::borough_name() const {
	return boroname;
}

string Tree::nearest_address() const {
	return address;
}

string Tree::life_status() const {
	return status;
}

string Tree::tree_health() const {
	return health;
}

int Tree::id() const {
	return tree_id;
}

int Tree::zip_code() const {
	return zipcode;
}

int Tree::diameter() const {
	return tree_dbh;
}

void Tree::get_position(double &latitude, double &longitude) const {
	 latitude = this->latitude;
	 longitude = this->longitude;
}

