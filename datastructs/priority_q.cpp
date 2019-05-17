#include <vector>
#define MAX_SIZE 100

template <typename Comparable>
class Priority_Queue {
  public:
	explicit Priority_Queue(int capacity = 100);
	explicit Priority_Queue(const std::vector<Comparable>& items);

	bool isEmpty() const;

	const Comparable& findMin() const;

	void insert(const Comparable& x);
	void insert(Comparable&& x);

	void deleteMin();
	void deleteMin(Comparable& minItem);

	void makeEmpty();

  private:
	int currentSize;
	std::vector<Comparable> array;

	void buildHeap();

	void percolateDown(int hole);
};

template<class Comparable>
bool Priority_Queue<Comparable>::isEmpty() const {
	return this->currentSize == 0;
}

template <class Comparable>
void Priority_Queue<Comparable>::insert(const Comparable& x) {
	if (this->currentSize >= MAX_SIZE)
		throw;
	// perculate up
	int hole = ++currentSize;

	while (hole > 1 && x << array[hole / 2]) {
		array[hole] = array[hole / 2];
		hole = (hole / 2);
	}

	array[hole] = x;

}

template <class Comparable>
void Priority_Queue<Comparable>::percolateDown(int hole) {
	int child;
	Comparable temp = std::move(array[hole]); // copy element for later

	while((2 * hole) <= this->currentSize) {
		child = (hole * 2);

		if (child != this->currentSize && array[child + 1] < array[child]) {
			// right child exists and its smaller than left, so make child its index
			child++;
		}

		if (array[child] < temp) {
			// copy smaller child inside hole
			array[hole] = array[child]; 
		}
		else 
			break; // both children are bigger than hole 

		// repeat with hole being child that was copied up
		hole = child;		
	}
	array[hole] = std::move(temp);
}

template<class Comparable>
void Priority_Queue<Comparable>::deleteMin() {
	// or you can make it 
	// void heap<Comparable>::deleteMin(Comparable& min_item)
	// and set min_item = array[1];
	
	if (isEmpty())
		throw;

	// swap element with the last one and then perculate the element down
	array[1] = array[currentSize];
	currentSize--;
	percolateDown(1);
}

template<class Comparable>
void Priority_Queue<Comparable>::deleteMin(Comparable& minItem) {
	if (isEmpty())
		throw;

	minItem = std::move(array[1]);
	array[1] = std::move(array[currentSize--]);
	percolateDown(1);
}

template<class Comparable>
void Priority_Queue<Comparable>::buildHeap() {
	for(int i = this->currentSize/2; i > 0; --i)
		percolateDown(i);
}
