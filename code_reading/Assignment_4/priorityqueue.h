/*
 *   libpal - Automated Placement of Labels Library
 *
 *   Copyright (C) 2008 Maxence Laurent, MIS-TIC, HEIG-VD
 *                      University of Applied Sciences, Western Switzerland
 *                      http://www.hes-so.ch
 *
 *   Contact:
 *      maxence.laurent <at> heig-vd <dot> ch
 *    or
 *      eric.taillard <at> heig-vd <dot> ch
 *
 * This file is part of libpal.
 *
 * libpal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libpal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpal.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
/*
    Name: Marin Pavlinov Marinov
*/

#ifndef PAL_PRIORITYQUEUE_H
#define PAL_PRIORITYQUEUE_H

#define SIP_NO_FILE

#include <iostream>

#define LEFT(x) (2 * x + 1)
#define RIGHT(x) (2 * x + 2)
#define PARENT(x) ((x - 1) / 2)

namespace pal {

/**
 * \ingroup core
 * \class pal::PriorityQueue
 * \note not available in Python bindings
 */
class PriorityQueue {
  public:
	/**
	 * \brief Create a priority queue of max size n
	 * \\param n max size of the queuet
	 * \\param p external vector representing the priority
	 * \\param min best element has the smalest p when min is True ans has the biggest when min is
	 * false
	 */
	PriorityQueue(int n, int maxId, bool min);
	~PriorityQueue();

	//! PriorityQueue cannot be copied.
	PriorityQueue(const PriorityQueue&) = delete;
	//! PriorityQueue cannot be copied.
	PriorityQueue& operator=(const PriorityQueue&) = delete;

	void print();

	int getSize();
	int getSizeByPos();

	bool isIn(int key);

	/* Assignment Q5 start
	    part 1: getBest()

	    Pre:
	    Heap is nonempty

	    Post:
	    Gets the item with highest priority (the 0th index which is the root)
	   The index is then replaced with -1 and size is decremented which is a form of lazy deletion
	   indicating that that current index is deleted

	    The root is swapped with last element.
	   The function then perculates the last element down until heap order property is preserved
	   Finally, it returns the value of highest priority that was originally stored at the root.
	*/
	int getBest(); // O(log n)

	/// part 2: remove
	/*
	    Pre:
	    key is not already deleted or greated than the maximum capacity

	    Post:
	    If the key and the item the key corresponds to are not deleted/empty, then
	    the size is decremented and the position of the key is marked with -1 (indicating that
	        it is deleted) and it is placed
	    at the end of the heap and has least priority.

	    The deleted element is then perculated down as it has less
	    priority now.
	*/
	void remove(int key);

	/// Part 3: Insert
	/*
	Pre:
	Checks if heap is full or if the key is  negative. Throws full exception if either is true

	Post:
	    Adds the new key at the end of the heap, makes it least priority , and increments the size.
	Then perculates the key up and adjusts priority accordingly if needed to make the structure
	satisfy heap order property.
	*/
	void insert(int key, double p);

	void sort(); // O(n log n)

	// Part 4: Downheap (perculate down)
	/*
	Pre#1:
	id must not be a leaf

	Pre#2:
	checks if the value of the parent is greater than the value of the child

	Post#1:
	the minimum child becomes the lesser/greater (depending if min is true or false) of the value of
	the two (right child and left child of the parent) If there is not right child then then the
	value is automatically assigned to the left child of the parent

	Post#2:
	The id of the parent gets moved down until heap order property is preserved
	*/
	void downheap(int id);

	// Part 5: Upheap (perculate up)
	/*
	Pre:
	 key is not empty and less than the maximum capacity. Then it
	checks if the contents that the key points to are either deleted(-1) or a valid value
	>= to 0.

	Post:
	The key is perculated up until heap order property is satisfied.
	*/
	void upheap(int key);

	// Part 6: Decrease Key
	/*
	Pre:
	Checks if the key is not empty and if the key exceeds the capacity and returns
	if either condition is met.

	Post:
	if the value of the key  is empty then the function returns
	else the priority of the key's value is diminished.

	The key is then perculated up so that it's in a position that corresponds to its new priority
	The position of the key is then perculated down as it has less priority now.
	*/
	void decreaseKey(int key);

	/// Part 7: setPriority
	/*
	Pre:
	Makes sure that the key is nonempty and less than or equal to the maxId

	Post:
	If the position of the key is empty then the function inserts the key into the heap

	else it perculates the key up until its in a place that corresponds to the priority inputted
	in the second parameter
	and then perculates down the position of the value the key.
	*/
	void setPriority(int key, double new_p);

	int getId(int key);

  private:
	int size;
	int maxsize;
	int maxId;
	int* heap = nullptr;
	double* p = nullptr;
	int* pos = nullptr;

	bool (*greater)(double l, double r);
};

} // namespace pal

#endif
