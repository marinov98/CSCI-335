/*******************************************************************************
  Title          : __tree_species.h
  Author         : Marin Pavlinov Marinov 
  Created on     : March 1st, 2019
  Description    : tree collection header file
  Purpose        : Inherit from the __tree_collection abstract class
*/
#ifndef Tree_Collection_H
#define Tree_Collection_H
#include "__tree_collection.h"
#include "tree.h"
#include "tree_species.h"
#include "AvlTree.h"

class TreeCollection : public __TreeCollection
{
public:

	/** total_tree_count() returns total number of trees in data set
	 *  @return int count of trees in collection
	 */
	int total_tree_count();

	/** count_of_tree_species(s) returns number of trees with name s
	 * @param  string species_name [in] species name to search for
	 * @return int the number of trees that have the given species name
	 */
	int count_of_tree_species ( const string & species_name );


	/** count_of_tree_species_in_boro(s,b) returns number of trees with name s
	 *                                     in boro b
	 * @note This returns the number of Tree objects in the collection whose
	 *       spc_common name matches the species_name specified by the
	 *       parameter s.
	 *       This method is case insensitive. If the method is
	 *       called with a non-existent species s, the return value should be 0.
	 * @param  string species_name [in] species name to search for
	 * @param  string boro_name [in] species borough to look in
	 * @return int the number of trees in boro that have the given species name
	 */
	int count_of_tree_species_in_boro ( const string & species_name,
	                                    const string & boro_name );


	/** get_counts_of_trees_by_boro(s,t) puts number of trees matching name s
	 *                                     in all boros into param t
	 * @note This puts the number of Tree objects in the collection whose
	 *       spc_common name matches the species_name specified by
	 *       parameter s into the boro_name array.
	 *       This method is case insensitive.
	 *       If the method is called with a non-existent species s,
	 *       the return value should be 0.
	 * @param  string species_name [in] species name to search for
	 * @param  boro boro_name[5] [in,out] array of boro structures
	 * @pre    boro_name[k].count ==0 for k = 0,...,4 and
	 *         boro_name[k].name is initialized with boro name[k]
	 * @post   boro_name[k].count has count of trees of given species in boro[k]
	 * @return int the total number of trees of given species in all boros
	 */
	int get_counts_of_trees_by_boro ( const string & species_name,
	                                  boro  tree_count[5] );


	/** count_of_trees_in_boro(b) returns number of trees of all types in boro b
	 * @param  string boro_name [in] species borough to look in
	 * @return int the number of trees in boro boro_name
	 */
	int count_of_trees_in_boro( const string & boro_name );

	/** add_tree(t) inserts Tree t into the collection, updates species list and
	 *              borough counts.
	 * @param Tree new_tree [in] the tree to be inserted
	 * @return int the number of trees inserted: 0 if none, 1 if inserted
	 */
	int add_tree( Tree & new_tree);


	/** print_all_species(out) prints all species names on out, one per line
	 *  This writes the set of all common names found in the data set to the
	 *  output stream out, one per line. The species names are printed in
	 *  lexicographic order, using the default string comparison ordering
	 *  @param ostream& [in,out]  out  the stream to be modified
	 */
	void print_all_species(ostream & out) const;

	/** print(out) prints all tree data on out, one tree per line, sorted
	 *  @notes
	 *  This writes the entire data set to the output stream out, one tree
	 *  per line, in sorted order by tree species common name as primary key,
	 *  and then by tree id as a secondary key.
	 *  The members of the Tree object are  printed in the same
	 *  order as they are described in the Tree class Data Dictionary, EXCEPT
	 *  THAT the species common name is printed FIRST.
	 *  @param ostream& [in,out]  out  the stream to be modified
	 */
	void print(ostream & out ) const;

	/** get_matching_species(s) returns a list<string> containing a list of all
	 *                  tree species common names that match species_name.
	 * @notes
	 *       This method is case insensitive.
	 *       The list returned by this function should not contain any
	 *       duplicate names and may be empty.
	 * @param string species_name [in] the partial name to match
	 * @return list<string> a list of species names that match species_name
	 */
	list<string> get_matching_species(
			const string & species_name) const;


	/** get_all_in_zipcode(z) returns a list<string> containing a list of all
	 *                  tree species common names in zipcode z.
	 * @notes
	 *       This method is case insensitive.
	 *       The list returned by this function should not contain any
	 *       duplicate names and may be empty.
	 * @param int zipcode [in]  the zipcode in which to search
	 * @return list<string> a list of species names in zipcode
	 */
	list<string> get_all_in_zipcode(int zipcode) const;

	/** get_all_near(lat,lng,dist) returns a list<string> containing a list of
	 *                  all tree species within dist km of point (lat,lng)
	 * @notes
	 *       The list returned by this function should not contain any
	 *       duplicate names and may be empty.
	 * @param double latitude   [in]  the latitude
	 * @param double longitude  [in]  the longitude
	 * @param double distance   [in]  teh distance in kilometers
	 * @return list<string> a list of species names within distance km of
	 *                     GPS point (latitude,logitude)
	 */
	list<string> get_all_near(double latitude, double longitude,
	                          double  distance) const;



private:
	AvlTree<Tree> tree_collection_;
	int tree_count_;

	bool findSpecies(const string& species_name);

	vector<string> species_data;

	vector<Tree> treeVector;
	vector<boro> borough_list;


	TreeSpecies wrapper;


	int species_count_;

//	bool findSpecies(const string& species_name);

};


#endif /* ___Tree_Collection_H__ */
