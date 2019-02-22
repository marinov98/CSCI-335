/*******************************************************************************
  Title          : __tree_species.h
  Author         : Stewart Weiss
  Created on     : February 16, 2019
  Description    : The interface file for the __TreeSpecies abstract class
  Purpose        : Encapsulates a container that represents the set of tree
                   names and the methods that interact with that set


  Matching Rules
  string tree_to_find matches the species common name tree_type if any of the 
  following conditions are true:

  tree_to_find is exactly the same string as tree_type, ignoring case.

  If tree_to_find has no whitespace or hyphen characters (it is one word) then 
  if tree_type contains white space characters or hyphens and consists of the
  words 
      w_{1}, w_{2}, ..., w_{k}
  then tree_to_find is exactly one of the words 
      w_{1}  , w_{2} , ..., w_{k}.
  For example if tree_to_find is "Japanese", and tree_type is 
   "Japanese tree lilac", then tree_to_find matches tree_type.

  If tree_to_find has whitespace or hyphen characters, then then if tree_type 
  contains white space characters or hyphens and consists of the words
      w_{1}, w_{2}, ..., w_{k}
  then tree_to_find is some subsequence w_{i}w_{i+1}...w_{j}
  of the sequence of words
      w_{1}, w_{2}, ..., w_{k}
  So "tree lilac" matches "Japanese tree lilac", but "tree lilac" does not 
  match "lilac".

  Otherwise tree_to_find does not match tree_type. 
*******************************************************************************/


#ifndef ___Tree_Species_H__
#define ___Tree_Species_H__

#include <string>
#include <iostream>
#include <list>

using namespace std;



/** class __TreeSpecies is an abstract class encapsulating tree species names.
 *  This class provides methods to print all species names, to return how many
 *  species names have been found, but most importantly, it has a method, which
 *  when given a species partial name, returns a list of all species whose
 *  common names matches that partial name according to the Matching Rules above.
 */
class __TreeSpecies
{
public:

	/** print_all_species(out) prints all species names on out, one per line
     *  This writes the set of all common names found in the data set to the 
     *  output stream out, one per line. The species names are printed in 
     *  lexicographic order, using the default string comparison ordering
     *  @param ostream& [in,out]  out  the stream to be modified
     */
    virtual void print_all_species(ostream & out) const = 0; 	

    /** number_of_species() returns the number of distinct species names
     *  This returns the total number of distinct species common names found in 
     *  the data set.
     *  @return int  The number of species common names
     */
    virtual int number_of_species() const = 0;	

    /** add_species(s)  inserts species s into the container
     *  This adds the species to the TreeSpecies container. 
     *  @param string s [in]  the string to be added.
     *  @return int It returns a 0 if the species was already in the 
     *              TreeSpecies container and a 1 if it was not.
     */
    virtual int add_species( const string & species) = 0;	

    /** get_matching_species(s) returns a list of species that match s
     * @note This returns a list<string> object containing a list of all of the 
     * actual tree species that match a given parameter string partial_name. 
     * This method should be case insensitive. The list returned by this 
     * function should not contain any duplicate names and may be empty.
     * The rules for matching are those described above.
     * @param string partial_name [in] string to match
     * @return list<string> list of matching species names
     */
    virtual list<string> get_matching_species(const string & partial_name) const = 0; 	

};

#endif /* ___Tree_Species_H__ */

