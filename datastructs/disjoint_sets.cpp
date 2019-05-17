/******************************************************************************
Title          : disjoint_sets.cpp
Author         : Marin Pavlinov Marinov
Created on     : April 22, 2018
Description    : cpp file for Disjoint sets
Purpose        : Implements Disjoint sets class (courtesy of Mark A. Weiss)
Usage          :
Build with     :c++11
Modifications  :

******************************************************************************/


#include <vector>

// courtesy of Mark A. Weiss textbook implementation of
// disjoint sets

class DisjSets {
 public:
    explicit DisjSets(int num_elements);

    int find(int x) const;
    int find(int x);

    void unionSets(int root1, int root2);

 private:
	std::vector<int> s;
};


DisjSets::DisjSets(int num_elements): (s{num_elements, -1}) {}

int DisjSets::find(int x) {
	if (s[x] < 0)
		return x;
	else
		return s[x] = find(s[x]);
}

int DisjSets::find(int x) const {
	if (s[x] < 0)
		return x;
	else
		return find(s[x]);
}

void DisjSets::unionSets(int root1, int root2) {
	if (s[root2] < s[root1]) // root2 is deeper
		s[root2] += s[root1]; // Make root2 new root
		s[root1] = root2;
	else {
		// root1 is deeper
		s[root1] += s[root2];
		s[root2] = root1;
	}
}

