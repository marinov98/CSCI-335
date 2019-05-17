#include <vector>
std::vector<int> a{4,5,8,11,15,21,345,66};
// BASIC INSERTION SORT
for(size_t i = 0; i < a.size(); i++) {
	int tmp = a[i];

	for(size_t j = i; j >= 1 && tmp < a[j -1]; j--)
		a[j] = a[j -1]

	a[j] = tmp;
}

// GENERALIZED INSERTION SORT (Shell Sort with gap 1)
int gap = 1;
for (int i = gap; i < a.size(); i++) {
	tmp = a[i];

	for(j = i; j >= gap && tmp < a[j-gap]; j -= gap) {
		a[j] = a[j - gap];
	}
	a[j] = tmp;
}

// SHELL'S ORIGINAL ALGORITHM
for (int gap = a.size() / 2; gap > 0; gap /= 2) {
	for (int i = gap; j >= gap && tmp < a[j - gap]; j -= gap)
		a[j] = a[j - gap];

	a[j] = tmp;
}

// HEAPSORT
#define LEFT(i)  2*(i) + 1
#define RIGHT(i) 2*(i) + 2
#define PARENT(i) ((i) - 1)/2

template <class Comparable>
void PercolateDown(std::vector<Comparable>& array, int hole, int last) {
	int child;
	Comparable temp = array[hole];

	while (LEFT(hole) < last) {
		child = LEFT(hole);
		if (child < last - 1 && array[child] < array[child + 1])
			child++;
		if (temp < array[child])
			array[hole] = array[child];
		else
			break;

		hole = child;
	}

	array[hole] = temp;

}

template<class Comparable>
void heapsort(std::vector<Comparable>& a) {
	// build heap
	int N = a.size();
	for (int i = (N/2) - 1; i >= 0; i--)
		PercolateDown(a,i,N);

	//a is now a heap
	// Now repeatedly swap the max element with the last element in the heap
	for (int j = N - 1; j > 0; j--) {
		std::swap(a[0],a[1]);
		PercolateDown(a,0,j);
	} 
}

// Non-Iterative Quick sort
/* This function is same in both iterative and recursive*/
int partition(int arr[], int l, int h) 
{ 
    int x = arr[h]; 
    int i = (l - 1); 
  
    for (int j = l; j <= h - 1; j++) { 
        if (arr[j] <= x) { 
            i++; 
	    std::swap(arr[i],arr[j]); 
        } 
    }
    std::swap(arr[i + 1],arr[h]); 
    return (i + 1); 
} 
  
/* A[] --> Array to be sorted,  
l --> Starting index,  
h --> Ending index */
void quickSortIterative(int arr[], int l, int h) 
{ 
    // Create an auxiliary stack 
    int stack[h - l + 1]; 
  
    // initialize top of stack 
    int top = -1; 
  
    // push initial values of l and h to stack 
    stack[++top] = l; 
    stack[++top] = h; 
  
    // Keep popping from stack while is not empty 
    while (top >= 0) { 
        // Pop h and l 
        h = stack[top--]; 
        l = stack[top--]; 
  
        // Set pivot element at its correct position 
        // in sorted array 
        int p = partition(arr, l, h); 
  
        // If there are elements on left side of pivot, 
        // then push left side to stack 
        if (p - 1 > l) { 
            stack[++top] = l; 
            stack[++top] = p - 1; 
        } 
  
        // If there are elements on right side of pivot, 
        // then push right side to stack 
        if (p + 1 < h) { 
            stack[++top] = p + 1; 
            stack[++top] = h; 
        } 
    } 
} 
  
