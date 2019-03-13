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
	for(int i = 0; i < spc_names.size(); i++)
		out << spc_names[i] << '\n';
}

int TreeSpecies::number_of_species() const {
	return _species_size;
}

bool TreeSpecies::find(const string &name) const {
	bool found = false;

	for (int i = 0; i < spc_names.size(); i++) {
		if (spc_names[i] == name) {
			found = true;
			break;
		}
	}

	return found;
}

// Helper functions
bool TreeSpecies::has_white_space(const string &species_name) const {
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
int TreeSpecies::get_number_of_words(const string &fullString) const {
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
string TreeSpecies::get_nth_word(const string &s, int n) const {
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
bool operator==(const string& s1,const string& s2)  {
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

bool operator<(const string& s1, const string& s2) {
	string t1common = "";
	string t2common = "";
	// fill the two strings with the lowercase version of the common names
	for (int i = 0; i < s1.size(); i++)
		t1common += (char)tolower(s1[i]);

	for (int j = 0; j < s2.size(); j++)
		t2common += (char)tolower(s2[j]);
	// compare the strings without worrying about case
	return (t1common < t2common);
}

// insert at a certain position in the dataset
bool TreeSpecies::binary_insert(vector<string>& v, int begin, int end, const string item_to_insert) {
	int mid = (begin + end) / 2;

	vector<string>::iterator it;
	it = v.begin();

	if (v[mid] < item_to_insert && item_to_insert < v[mid + 1]) {
		v.insert(it + mid + 1, item_to_insert);
		return true;
	}
	else if (item_to_insert < v[mid] && item_to_insert < v[mid + 1]) {
		end = mid - 1;
		return binary_insert(v, begin, end, item_to_insert);
	}
	else if (item_to_insert > v[mid] && item_to_insert > v[mid + 1]) {
		begin = mid + 1;
		return binary_insert(v, begin, end, item_to_insert);
	}

	return false;
}

int TreeSpecies::add_species(const string &species) {
	int i = 1;

	 //case where we it is not in the dataset
	if (!find(species)) {
		// case 1.0: empty dataset and case 1.1: species is higher than (lexigraphically) last item in dataset
		if (spc_names.empty() || spc_names[spc_names.size() - 1] < species) {
			spc_names.push_back(species);
		}
		// case 1.2 species is lexigraphically lower than the first item in dataset
		else if (species < spc_names[0]) {
			spc_names.insert(spc_names.begin(), species);
		} // case 1.3 it is somewhere in the dataset (because the dataset is sorted we can binary search the place)
		else {
			binary_insert(spc_names,0,spc_names.size() - 1, species);
		}
		_species_size++;
	} // case 2: species already in dataset
	else {
		// add nothing
		i = 0;
	}

	return i;
}

// function to check if item is found in the list
bool TreeSpecies::in_list(list<string> list, const string &item) const {
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

	string s = "";

	// convert partial to a string without any '-'
	for (int x = 0; x < partial_name.size(); x++) {
		if (partial_name[x] != '-')
			s += partial_name[x];
		if (partial_name[x] == '-')
			s  += ' ';
	}

	// case 1: partial has one word
	if (get_number_of_words(s) == 1) {
		for(int i = 0; i < spc_names.size(); i++) {
			for(int j = 0; j < get_number_of_words(spc_names[i]); j++) {
				if (get_nth_word(spc_names[i], j) == s &&
					!in_list(result, spc_names[i])) {
					result.push_back(spc_names[i]);
				}
			}
		}
	} // case 2: more than two words
	else if (get_number_of_words(s) > 1){
		for(int k = 0; k < spc_names.size(); k++) {
			// case where partial name and a species name have the same number of words
			if (get_number_of_words(s) == get_number_of_words(spc_names[k])) {
				if (spc_names[k] == s && !in_list(result, spc_names[k])) {
					result.push_back(spc_names[k]);
				}
			}
			// case where species name also
			else if(get_number_of_words(spc_names[k]) > get_number_of_words(s)) {
				for(int l = 0; l < get_number_of_words(spc_names[k]); l++) {
					for (int m = l + 1; m < get_number_of_words(spc_names[k]); m++) {
						// create sequences and find the right combination
						string sequence = get_nth_word(spc_names[k], l) + " "
								+ get_nth_word(spc_names[k], m);
						if (sequence == s && !in_list(result, spc_names[k])) {
							result.push_back(spc_names[k]);
						}
					}
				}
			}
		}
	}
	return result;
}
