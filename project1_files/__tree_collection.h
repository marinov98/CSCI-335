/*******************************************************************************
  Title          : tree_collection.h
  Author         : Stewart Weiss
  Created on     : February 18, 2019
  Description    : The header file for the TreeCollection class
  Purpose        : Encapsulates the containers that represent the set of trees
                   and the collections properties
  Usage          : 
  Build with     : No building
  Modifications  : 
 
*******************************************************************************/


#ifndef ___Tree_Collection_H__
#define ___Tree_Collection_H__

#include <string>
#include <iostream>
#include <list>
#include "tree.h"

using namespace std;

struct boro {
    int  count;
    string name;
};



class __TreeCollection
{
public:

    /** total_tree_count() returns total number of trees in data set
     *  @return int count of trees in collection  
     */
    virtual int total_tree_count() = 0; 

    /** count_of_tree_species(s) returns number of trees with name s
     * @param  string species_name [in] species name to search for
     * @return int the number of trees that have the given species name
     */ 
    virtual int count_of_tree_species ( const string & species_name ) = 0;


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
    virtual int count_of_tree_species_in_boro ( const string & species_name,
                                        const string & boro_name ) = 0; 


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
    virtual int get_counts_of_trees_by_boro ( const string & species_name,
                                       boro  tree_count[5] ) = 0;


    /** count_of_trees_in_boro(b) returns number of trees of all types in boro b
     * @param  string boro_name [in] species borough to look in
     * @return int the number of trees in boro boro_name
     */ 
    virtual int count_of_trees_in_boro( const string & boro_name ) = 0; 

    /** add_tree(t) inserts Tree t into the collection, updates species list and
     *              borough counts. 
     * @param Tree new_tree [in] the tree to be inserted
     * @return int the number of trees inserted: 0 if none, 1 if inserted
     */
    virtual int add_tree( Tree & new_tree) = 0;


    /** print_all_species(out) prints all species names on out, one per line
     *  This writes the set of all common names found in the data set to the 
     *  output stream out, one per line. The species names are printed in 
     *  lexicographic order, using the default string comparison ordering
     *  @param ostream& [in,out]  out  the stream to be modified
     */
    virtual void print_all_species(ostream & out) const = 0;

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
    virtual void print(ostream & out ) const = 0;

    /** get_matching_species(s) returns a list<string> containing a list of all
     *                  tree species common names that match species_name. 
     * @notes 
     *       This method is case insensitive. 
     *       The list returned by this function should not contain any 
     *       duplicate names and may be empty.
     * @param string species_name [in] the partial name to match
     * @return list<string> a list of species names that match species_name
     */
    virtual list<string> get_matching_species(
                           const string & species_name) const = 0; 


    /** get_all_in_zipcode(z) returns a list<string> containing a list of all
     *                  tree species common names in zipcode z. 
     * @notes 
     *       This method is case insensitive. 
     *       The list returned by this function should not contain any 
     *       duplicate names and may be empty.
     * @param int zipcode [in]  the zipcode in which to search
     * @return list<string> a list of species names in zipcode
     */
    virtual list<string> get_all_in_zipcode(int zipcode) const = 0;

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
    virtual list<string> get_all_near(double latitude, double longitude, 
                         double  distance) const = 0;

};


#endif /* ___Tree_Collection_H__ */

