/******************************************************************************
  Title          : hash_item.h
  Author         : Marin Pavlinov Marinov
  Created on     : April 3, 2019
  Description    : header of disjoint sets
  Purpose        : implement the interface from Mark A. Weiss' datastructures textbook and make it work with NYC open data
  Usage          :
  Build with     : c++11
********************************************************************************/

#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H

#include <vector>

using namespace std;

// courtesy of Mark A. Weiss textbook implementation of
// disjoint sets

class DisjSets {
 public:
    explicit DisjSets(int num_elements);

    int find(int x) const;
    int find(int x);

    void unionSets(int root1, int root2);

 private:
    vector<int> s;
}

#endif
