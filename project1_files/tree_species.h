#include "__tree_species.h"

/*******************************************************************************
  Title          : __tree_species.h
  Author         : Marin Pavlinov Marinov 
  Created on     : March 1st, 2019
  Description    : tree species header file
  Purpose        : Inherit from the __tree_species abstract class
*/

#ifndef Tree_Species_H
#define Tree_Species_H

#include <vector>

class TreeSpecies : public __TreeSpecies
{
public:
	// Constructors:
	TreeSpecies();

	TreeSpecies(const string &species);

	/** print_all_species(out) prints all species names on out, one per line
     *  This writes the set of all common names found in the data set to the
     *  output stream out, one per line. The species names are printed in
     *  lexicographic order, using the default string comparison ordering
     *  @param ostream& [in,out]  out  the stream to be modified
     */
	 void print_all_species(ostream & out) const;

	/** number_of_species() returns the number of distinct species names
	 *  This returns the total number of distinct species common names found in
	 *  the data set.
	 *  @return int  The number of species common names
	 */
	 int number_of_species() const;

	/** add_species(s)  inserts species s into the container
	 *  This adds the species to the TreeSpecies container.
	 *  @param string s [in]  the string to be added.
	 *  @return int It returns a 0 if the species was already in the
	 *              TreeSpecies container and a 1 if it was not.
	 */
	int add_species( const string & species);

	/** get_matching_species(s) returns a list of species that match s
	 * @note This returns a list<string> object containing a list of all of the
	 * actual tree species that match a given parameter string partial_name.
	 * This method should be case insensitive. The list returned by this
	 * function should not contain any duplicate names and may be empty.
	 * The rules for matching are those described above.
	 * @param string partial_name [in] string to match
	 * @return list<string> list of matching species names
	 */
	list<string> get_matching_species(const string & partial_name) const;

	friend bool operator<(const string& s1, const string& s2);

	friend bool operator==(const string& s1, const string& s2);

	vector<string> get_species_vector();

private:
	bool has_white_space(const string &species_name) const;

	bool binary_insert(vector<string>& v, int begin, int end, const string item_to_insert);

	int get_number_of_words(const string &fullString) const;

	string get_nth_word(const string &s, int n) const;

	bool find(const string& name) const;

	bool in_list(list<string> list, const string &item) const;

	vector<string> spc_names;

	int _species_size;

};

#endif /* ___Tree_Species_H__ */
