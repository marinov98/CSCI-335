/*******************************************************************************
  Title          : tree_collection.h
  Author         : Marin Pavlinov Marinov
  Created on     : February 22, 2019
  Description    : The header file for the TreeCollection class
  Purpose        : Encapsulates the containers that represent the set of trees
                   and the collections properties
  Usage          :
  Build with     : No building
  Modifications  :

*******************************************************************************/

#include "tree_collection.h"

int TreeCollection::total_tree_count() {
	return tree_count_;
}

int TreeCollection::count_of_tree_species(const string& species_name) {}

int TreeCollection::count_of_tree_species_in_boro(const string& species_name,
                                                  const string& boro_name) {}

int TreeCollection::get_counts_of_trees_by_boro(const string& species_name, boro tree_count[5]) {}

int TreeCollection::count_of_trees_in_boro(const string& boro_name) {}

bool TreeCollection::findSpecies(const string& species_name) {
	bool find = false;
	for (int i = 0; i < species_data.size(); i++) {
		if (species_data[i] == species_name) {
			find = true;
			break;
		}
	}
	return find;
}

int TreeCollection::add_tree(Tree& new_tree) {
	int i = 1;
	// check to see if tree is valid
	if (new_tree.id() == -1) {
		i = 0;
	} // if valid insert tree and update boro
	else {
		tree_count_++;
		tree_collection_.insert(new_tree);

		// empty list means we have have not seen that boro yet
		if (borough_list.empty()) {
			borough_list.push_back({1, new_tree.borough_name()});
		} // check to see if that borough has been added already
		else {
			bool added = false;
			for (int k = 0; k < borough_list.size(); k++) {
				if (borough_list[i].name != new_tree.borough_name()) {
					borough_list.push_back({1, new_tree.borough_name()});
					added = true;
				}
			}
			if (!added) {
				for (int i = 0; i < borough_list.size(); i++) {
					if (borough_list[i].name == new_tree.borough_name()) {
						borough_list[i].count++;
					}
				}
			}
		}

		// species insertion:
		// if the dataset is empty or the species name is unique, add it to the data set
		// if (species_data.empty() || !findSpecies(new_tree.common_name())) {
		//	species_count_++;
		return wrapper.add_species(new_tree.common_name());
		/*
		species_data.push_back(new_tree.common_name());
		species_count_++;
		 */
	}

	return i;
}

void TreeCollection::print_all_species(ostream& out) const {
	return wrapper.print_all_species(out);
}

void TreeCollection::print(ostream& out) const {
    out << tree_collection_.display(out);
}

list<string> TreeCollection::get_matching_species(const string& species_name) const {
	return wrapper.get_matching_species(species_name);
}

list<string> TreeCollection::get_all_in_zipcode(int zipcode) const {}

double TreeCollection::haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6372.8;
    const double TO_RAD = M_PI / 180.0;

    lat1 = TO_RAD * lat1;
    lat2 = TO_RAD * lat2;
    lon1 = TO_RAD * lon1;
    lon2 = TO_RAD * lon2;
    double dLat = (lat2 - lat1)/2;
    double dLon = (lon2 - lon1)/2;
    double a = sin(dLat);
    double b = sin(dLon);

    return 2 * R * asin(sqrt(a*a + cos(lat1)*cos(lat2)*b*b));
}

list<string> TreeCollection::get_all_near(double latitude,
                                          double longitude,
                                          double distance) const {}
