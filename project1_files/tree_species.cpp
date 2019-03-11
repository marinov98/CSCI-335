/*******************************************************************************
  Title          : tree_collection.h
  Author         : Marin Pavlinov Marinov
  Created on     : February 22, 2019
  Description    : Cpp file for the tree_species class
  Purpose        : Implements the tree species class
  Usage          : 
  Build with     : No building
  Modifications  : 
 
*******************************************************************************/
#include "tree_species.h"


void TreeSpecies::print_all_species(ostream &out) const {}

int TreeSpecies::number_of_species() const {}

int TreeSpecies::add_species(const string &species) {}

list<string> TreeSpecies::get_matching_species(const string &partial_name) const {}
