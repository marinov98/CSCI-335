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

int TreeCollection::total_tree_count() {}

int TreeCollection::count_of_tree_species(const string &species_name) {}

int TreeCollection::get_counts_of_trees_by_boro(const string &species_name, boro *tree_count) {}

int TreeCollection::count_of_trees_in_boro(const string &boro_name) {}

int TreeCollection::add_tree(Tree &new_tree) {}

void TreeCollection::print_all_species(ostream &out) const {}

void TreeCollection::print(ostream &out) const {}

list<string> TreeCollection::get_matching_species(const string &species_name) const {}

list<string> TreeCollection::get_all_in_zipcode(int zipcode) const {}

list<string> TreeCollection::get_all_near(double latitude, double longitude, double distance) const {}

