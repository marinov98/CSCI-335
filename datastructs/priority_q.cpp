#include <vector>

template <typename Comparable>
class Priority_Queue {
  public:
	explicit Priority_Queue(int capacity = 100);
	explicit Priority_Queue(const vector<Comparable>& items);

	bool isEmpty() const;

	const Comparable& findMin() const;

	void insert(const Comparable& x);
	void insert(Comparable&& x);

	void deleteMin();
	void deleteMin(const Comparable& minItem);

	void makeEmpty();

  private:
	int currentSize;
	vector<Comparable> array;

	void buildHeap();

	void percolateDown(int hole);
};
