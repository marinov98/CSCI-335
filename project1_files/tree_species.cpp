/******************tree_collection.h
  Author         : Marin Pavlinov Marinov
  Created on     : February 22, 2019
  Description    : Cpp file for the tree_species class
  Purpose        : Implements the tree species class
  Usage          : 
  Build with     : No building
  Modifications  : 
 
*******************************************************************************/
#include "tree_species.h"


TreeSpecies::TreeSpecies() {
	_species_size = 0;
}

TreeSpecies::TreeSpecies(const string &species){
	add_species(species);
	_species_size = 1;
}

void TreeSpecies::print_all_species(ostream &out) const {
	out <<  '\n';
}

int TreeSpecies::number_of_species() const {
	return _species_size;
}

bool TreeSpecies::find(const string &name) {
	bool found = false;

	for (int i = 0; i < spc_names.size(); i++) {
		if (spc_names[i] == name) {
			found = true;
			break;
		}
	}

	return found;
}

int TreeSpecies::add_species(const string &species) {
	int i = 1;

	if (find(species)) {
		i = 0;
	}
	else {
		spc_names.push_back(species);
		_species_size++;
	}

	return i;
}

// Helper functions
bool hasWhiteSpace(const string& species_name) {
	bool has = false;
	for (int i = 0; i < species_name.size(); i++) {
		if (species_name[i] == ' ' || species_name[i] == '-') {
			has = true;
			break;
		}
	}

	return has;
}

// returns the number of words in a given string
int getNumberOfWords(const string& fullString) {
	int words = 1;

	for (int i = 0; i < fullString.size(); i++) {
		if ((i - 1) < fullString.size() &&
			(fullString[i] == ' ' || fullString[i] == '-') &&
			(fullString[i - 1] != ' ' || fullString[i - 1] != '-')) {
			words++;
		}
	}
	return words;
}

// returns the nth word in a string (0 being the first)
string getNthword(const string& s, int n) {
	int x = 0;
	string sub = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != ' ' || s[i] != '-') {
			sub += s[i];
		}
		else if (!sub.empty()) {
			if(x == n) {
				return sub;
			}
			sub = "";
			x++;
		}
	}
	return sub;
}
// make equals operator case insensitive
bool operator==(const string& s1,const string& s2) {
	bool result = true;
	if (s1.size() != s2.size()) {
		result = false;
	}
	else {
		for(int i = 0; i < s1.size(); i++) {
			if(tolower(s1[i]) != tolower(s2[i])) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool inList(list<string> list, string item) {
	bool found = false;

	for(::list<string>::iterator iterator = list.begin();iterator != list.end(); iterator++) {
		if(*iterator == item) {
			found = true;
			break;
		}
	}
	return found;
}

list<string> TreeSpecies::get_matching_species(const string &partial_name) const {
	list<string> result;
	// case 1: partial has one word
	if (getNumberOfWords(partial_name) == 1) {
		for(int i = 0; i < spc_names.size(); i++) {
			for(int j = 0; j < getNumberOfWords(spc_names[i]); j++) {
				if (getNthword(spc_names[i],j) == partial_name &&
					!inList(result,spc_names[i])) {
					result.push_back(spc_names[i]);
				}
			}
		}
	} // case 2: more than two words
	else if (getNumberOfWords(partial_name) > 1){
		for(int k = 0; k < spc_names.size(); k++) {
			// case where partial name and a species name have the same number of words
			if (getNumberOfWords(partial_name) == getNumberOfWords(spc_names[k])) {
				if (spc_names[k] == partial_name && !inList(result,spc_names[k])) {
					result.push_back(spc_names[k]);
				}
			}
			// case where species name also
			else if(getNumberOfWords(spc_names[k]) > getNumberOfWords(partial_name)) {
				for(int l = 0; l < getNumberOfWords(spc_names[k]); l++) {
					for (int m = l + 1; m < getNumberOfWords(spc_names[k]); m++) {
						// create sequences and find the right combination
						string sequence = getNthword(spc_names[k],l) + " "
								+ getNthword(spc_names[k],m);
						if (sequence == partial_name && !inList(result,spc_names[k])) {
							result.push_back(spc_names[k]);
						}
					}
				}
			}
		}
	}
	return result;
}
