
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
	tree_id = 0;
	tree_dbh = 0;
	status = "";
	health = "";
	spc_common = "";
	zipcode = 0;
	address = "";
	boroname = "";
	latitude = 0;
}

//helper function that splits a string on commas
vector<string> split(string const& in) {
	vector<string> result;
	string s = "";
	for(int i = 0; i < in.size(); i++) {
		if (in[i] != ',') {
			s += in[i];
		} // takes care of the case if its two comma's next to each other
		else if (!s.empty()) {
			result.push_back(s);
			s = "";
		}
	}
	// last piece of data does not get loaded so we need to do it here
	if (!s.empty())
		result.push_back(s);

	return result;
}


Tree::Tree(const string& str) {
	ifstream csvfile;
	try {
		csvfile.open(str);
	}
	catch (int e) {
		cout << "cannot read from" << str << '\n';
	}

	string reader;

	// a vector to extra the file as a string
	vector<string> extractor;

	// retrieve file as single string
	while(getline(csvfile,reader)) {
		extractor.push_back(reader);
	}

	// vector to split the extractor by commas
	vector<string> splitter = split(extractor[0]);

	//load the values we extracted,
	this->tree_id = stoi(splitter[0]);
	this->tree_dbh = stoi(splitter[1]);
	this->status = splitter[2];
	this->health = splitter[3];
	this->spc_common = splitter[4];
	this->zipcode = stoi(splitter[5]);
	this->address = splitter[6];
	this->boroname = splitter[7];
	this->latitude = stod(splitter[8]);
	this->longitude = stod(splitter[9]);

	//TODO: VALIDATION
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
	tree_id = id;
	tree_dbh = diam;
	status = stat;
	health = hlth;
	spc_common = name;
	zipcode = zip;
	address = addr;
	boroname = boro;
	latitude = lat;
	longitude = longtd;

}

ostream& operator<<(ostream& os, const Tree& t) {
	os  << t.spc_common << t.tree_id
		<< t.tree_dbh << t.status
		<< t.health << t.zipcode
		<< t.address << t.boroname
		<< t.latitude << t.longitude;

	return os;
}

bool operator==(const Tree& t1, const Tree& t2) {
	return (samename(t1,t2) && t1.id() == t2.id());
}

bool operator<(const Tree t1, const Tree& t2) {
	return (t1.common_name() < t2.common_name() ||
	        (t1.common_name() == t2.common_name() &&
			(t1.id() < t2.id())));
}

bool samename(const Tree& t1, const Tree& t2) {
	bool same = true;

	// if length is different, then we already know they are not the same
	if (t1.spc_common.length() != t2.spc_common.length()) {
		same = false;
	} // else convert every character to lowercase (avoid case sensitivity) and compare them
	else {
		for (int i = 0; i < t1.spc_common.length(); i++) {
			if (tolower(t1.spc_common[i] != tolower(t1.spc_common[i])))
				same = false;
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

