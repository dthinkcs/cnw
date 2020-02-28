#include <vector>
#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int partition(vector<int>& array, int si, int ei) {
	int index = si;
	int count = 0;
	for (int i = si; i <= ei; i++){
		if (array[i] < array[index]) { // BUG1 correcthing array[i]
			count += 1;
		}
	}
			// 	for(int i = 0; i < array.size(); i++)
			// 		cout << array[i] << " ";
			// cout << endl;

	int correctIndex = si + count;
	swap(array[correctIndex], array[index]);
			// 	for(int i = 0; i < array.size(); i++)
			// 		cout << array[i] << " ";
			// cout << endl;

	int left = si;
	int right = ei;
	while (left < correctIndex && correctIndex < right) {
		if (array[right] < array[correctIndex]) { // we found a mismatch
			if (array[left] >= array[correctIndex]) {
				swap(array[left], array[right]);
				left += 1; 
				right -= 1;
			} else  {
				left += 1;
			}
		} else {
			right -= 1;
		}
		// if (array[left] <= array[correctIndex] && array[correctIndex] <= array[right]) {
		// 	left += 1;
		// 	right -= 1;
		// } else if (array[left] > array[correctIndex] && array[correctIndex] > array[right]){
		// 	swap(array[left], array[right]);
		// 	left += 1;
		// 	right -= 1;
		// } else if (array[left] > array[correctIndex]) {
		// 	right -= 1;
		// } else {
		// 	left += 1;
		// }
	}
	return correctIndex;
}

void quickSortHelper(vector<int>& array, int si, int ei) {

	if (si >= ei) {
		return;
	} else {
		int pivot = partition(array, si, ei);
			for(int i = 0; i < array.size(); i++)
					cout << array[i] << " ";
			cout << endl;

		quickSortHelper(array, si, pivot - 1);
		quickSortHelper(array, pivot + 1, ei);
  	
	}
}

vector<int> quickSort(vector<int> array) {
  // Write your code here.
	vector<int> result = array;
	quickSortHelper(result, 0, result.size() - 1);
	return result;
}
