#include <iostream>
#include <string>

using namespace std;


void PrintArray(int *arr, int len) {

	for (int i = 0; i < len; i++)
		cout << arr[i] << ' ';

	cout << endl;
}

void DirectSort(int *arr, int len) {
	int i, j, tmp;
	for (i = 1; i < len; i++) {
		tmp = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (tmp < arr[j])
				arr[j + 1] = arr[j];
			else
				break;
		}
		arr[j + 1] = tmp;
	}
}

void DichotomySort(int *arr, int len, int x) {

	int left = 0, right = len - 1, stInx;
	int mid = (left + right) / 2;

	while (left != right) {
		
		if (arr[mid] < x)
			left = mid + 1;
		else
			right = mid - 1;

		mid = (left + right) / 2;
	}

	stInx = (arr[left] > x) ? left : left + 1;
	for (int i = len - 1; i >= stInx; i--)
		arr[i + 1] = arr[i];
	arr[stInx] = x;
}

void BubbleSort(int *arr, int len) {
	int i, j, tmp;
	for (i = 0; i < len - 1; i++) {
		for (j = 0; j < len - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}

		}
	}
}

void FastSortA(int *arr, int st, int end) {

	if (st == end)
		return;

	int pivot = arr[st], left = st, right = end;

	while (left != right) {

		while (arr[right] > pivot && right != left) {right--;}
		if (right != left)
			arr[left] = arr[right];
		while (arr[left] < pivot && left != right) { left++; }
		if (left != right)
			arr[right] = arr[left];
	}

	arr[left] = pivot;
	if(left - 1 >= st)
		FastSortA(arr, st, left - 1);
	if(left + 1 <= end)
		FastSortA(arr, left + 1, end);

}

void FastSortB(int *arr, int st, int end) {

	if (st == end)
		return;

	int pivot = arr[st], left = st + 1, right = end, tmp;

	while (left <= right) {
		while (arr[right] > pivot && right >= left) { right--; }
		while (arr[left] < pivot && left <= right) { left++; }
		if (right > left) {
			tmp = arr[right];
			arr[right] = arr[left];
			arr[left] = tmp;
		}
	}

	arr[st] = arr[right];
	arr[right] = pivot;

	if (right - 1 >= st)
		FastSortA(arr, st, right - 1);
	if (right + 1 <= end)
		FastSortA(arr, right + 1, end);

}


class MinHeap {

public:

	int *HeapArr;
	int curCount;

	MinHeap() { this->HeapArr = new int[36]; }
	~MinHeap() { delete[] HeapArr; }

	void Build(int *arr, int num);
	void Insert(int x);
	void SiftDown(int inx);
	void SiftUp();
	int RemoveMin();
};

void MinHeap::Build(int *arr, int num) {

	this->curCount = num;
	for (int i = 0; i < this->curCount; i++)
		HeapArr[i] = arr[i];

	for (int i = this->curCount / 2 - 1; i >= 0; i--)
		SiftDown(i);
}

void MinHeap::SiftDown(int inx) {

	int j = 2 * inx + 1, tmp = HeapArr[inx];

	while (j < curCount) {
		if (j < curCount - 1 && HeapArr[j] > HeapArr[j + 1])
			j++;

		if (tmp > HeapArr[j]) {
			HeapArr[inx] = HeapArr[j];
			inx = j;
			j = 2 * inx + 1;

		}
		else
			break;
	}

	HeapArr[inx] = tmp;
}

void MinHeap::Insert(int x) {

	HeapArr[curCount] = x;
	SiftUp();
	curCount++;
}

void MinHeap::SiftUp() {

	int inx = this->curCount, int tmp = HeapArr[inx], int parent;

	while (inx != 0) {
		parent = (inx / 2) - 1 + (inx % 2);
		if (tmp < HeapArr[parent]) {
			HeapArr[inx] = HeapArr[parent];
			inx = parent;
		}
		else
			break;
	}
	HeapArr[inx] = tmp;
}

int MinHeap::RemoveMin() {
	
	if (this->curCount == 0)
		return -1;

	int resMin = this->HeapArr[0];
	HeapArr[0] = HeapArr[curCount - 1];
	curCount--;

	for (int i = this->curCount / 2 - 1; i >= 0; i--)
		SiftDown(i);
	
	return resMin;
}


void main() {

	int arr[6] = {32, 18, 65, 48, 27, 9};
	cout << "Direct Sort: " << endl;
	DirectSort(arr, 6);
	PrintArray(arr, 6);

	cout << "Dichotomy Sort" << endl;
	int arr1[6] = { 1, 3, 5, 7, 9, -1 };
	DichotomySort(arr1, 5, 10);
	PrintArray(arr1, 6);

	cout << "Bubble Sort" << endl;
	int arr2[6] = { 9, 6, 8, 7, 5, 10 };
	BubbleSort(arr2, 6);
	PrintArray(arr2, 6);

	cout << "Fast Sort" << endl;
	int arr3[8] = { 45, 32, 61, 98, 27, 17, 22, 53 };
	FastSortB(arr3, 0, 7);
	PrintArray(arr3, 8);


	system("pause");

}