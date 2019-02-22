/*******************************************************************************
  Title          : tree.h
  Author         : Stewart Weiss
  Created on     : February  16, 2019
  Description    : The interface file for the Tree class
  Purpose        : To provide a minimal interface to be used to interact with 
                   the Tree objects.
  Usage          : 
  Build with     : No building
  Modifications  : 
 
*******************************************************************************/
#ifndef __Tree_H__
#define __Tree_H__

/******************************************************************************
Data Dictionary for Input File:
 Position   Type   Name        Description
 1          int    tree_id;    unique id that  identifies the tree
 4          int    tree_dbh;   specifies tree diameter
 7          string status;     valid values: ”Alive”, ”Dead”, ”Stump”, or the 
                               empty string 
 8          string health;     valid values: ”Good”, ”Fair”, ”Poor”, or the 
                               empty string
 10         string spc_common; the common name of the tree, such as “white oak” 
                               or a possibly empty string
 25         string  address;   the nearest street address to the tree
 26         int    zipcode;    positive five digit integer (This means that any 
                               number from 0 to 99999 is acceptable. The values 
                               that are shorter are treated as if they had 
                               leading zeroes
 30         string boroname;   valid values: ”Manhattan”, ”Bronx”, ”Brooklyn”, 
                               ”Queens”, ”Staten Island”
 40         double latitude     spatial coordinate specifying position in 
                               New York State state plane coordinates
 41         double longitude     spatial coordinate specifying position in 
                               New York State state plane coordinates

 ******************************************************************************/


#include <string>
#include <iostream>
using namespace std;

/** class Tree
 *  The Tree class represents an individual tree from the NYC Open Data
 *  2015 Tree Census. Only ten of the data members are stored in an object of
 *  class Tree, as described above.
 */
class Tree
{
public:
    /** Tree()
     *  A default constructor for the class, creating an empty Tree. 
     */
    Tree();

    /** Tree(str) is a constructor that expects a csv string.
     *  The string must contain 41 fields, separated by commas, in the order 
     *  specified in the Data Dictionary from the NYC Open Data website. The
     *  constructor extracts the ten fields listed above, validating each
     *  of them. Each field is expected to be of the correct type. If any are 
     *  invalid, it creates an empty tree.
     */
    Tree(const string & str) ;

    /** A constructor that expects ten values exactly as specified in the.
     *  data dictionary above. 
     *  This constructor does not validate the values - it assumes they have
     *  been validated before the call.
     */
    Tree(int id, int diam,  string stat, string hlth, string name, 
        int zip, string addr, string boro, double lat, double longtd);

    /** operator<<(os,t)  Overloaded stream insertion operator
     *  writes the Tree t onto the stream os as a comma-separated-values string
     *  converting the floats to fixed decimals with precision 5 digits.
     *  The members of the Tree object are  printed in the same 
     *  order as they are described in the Data Dictionary above, EXCEPT THAT
     *  the species common name is printed FIRST.
     *  @param ostream os [inout] 
     *  @param Tree    t  [in]    
     *  @return ostream&   
     */
    friend ostream& operator<< (ostream & os, const Tree & t);

    
    /** operator== (t1,t2)  compares two trees for key pair equality
     *  @param Tree   t1  [in] 
     *  @param Tree   t2  [in]
     *  @return bool  true iff t1 and t2 have the same common name and id 
     *                      case-insensitively
     */
    friend bool operator==(const Tree & t1, const Tree & t2);


    /** operator< (t1,t2)  checks if key pair of t1 is less than key pair of t2
     *  @param Tree   t1  [in] 
     *  @param Tree   t2  [in]
     *  @return bool  true if  the common name of t1 < common name of t2 
     *                case insensitively or they are the same but 
     *                t1's id < t2's id. 
     */
    friend bool operator<(const Tree & t1, const Tree & t2);


    /** samename(t1,t2)  checks if the names of t1 and t2 are identical
     *  @param Tree   t1  [in] 
     *  @param Tree   t2  [in]
     *  @return bool  true if  the common name of t1 equals common name of t2 
     *                case insensitively. 
     */
    friend bool samename(const Tree & t1, const Tree & t2);


    /** islessname(t1,t2)  checks if the name of t1 precedes name of t2 
     *  @param Tree   t1  [in] 
     *  @param Tree   t2  [in]
     *  @return bool  true if  the common name of t1 precedes common name of t2 
     *                case insensitively. 
     */
    friend bool islessname(const Tree & t1, const Tree & t2);

    /** A bunch of get-functions
     *  The next nine methods are accessor functions that retrieve the value
     *  of the corresponding private data member. Their meaning should be
     *  clear, possibly except for life_status(), which returns the tree's status
     *  member, and the tree_health() which returns its health member.
     */
    string common_name() const;
    string borough_name() const;
    string nearest_address() const;
    string life_status() const;
    string tree_health() const;
    int id()       const;
    int zip_code() const;
    int diameter() const;
    void get_position(double & latitude,double & longitude) const;


private:
    int    tree_id;    // unique id that  identifies the tree
    int    tree_dbh;   // specifies tree diameter
    string status;     // valid values: ”Alive”, ”Dead”, ”Stump”, or the 
                       //        empty string 
    string health;     // valid values: ”Good”, ”Fair”, ”Poor”, or the 
                       //         empty string
    string spc_common; // the common name of the tree, such as “white oak” 
                       //        or a possibly empty string
    int    zipcode;    // positive five digit integer (This means that any 
                       //         number from 0 to 99999 is acceptable. The values 
                       //         that are shorter are treated as if they had 
                       //         leading zeroes
    string address;    // street address nearest to tree

    string boroname;   // valid values: ”Manhattan”, ”Bronx”, ”Brooklyn”, 
                       //        ”Queens”, ”Staten Island”
    double latitude;   // x spatial coordinate specifying position in 
                       // New York State state plane coordinates
    double longitude;  // y spatial coordinate specifying position in 
                       //        New York State state plane coordinates
};

#endif /* __Tree_H__ */


