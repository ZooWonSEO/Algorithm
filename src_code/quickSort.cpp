#include <iostream>
#include <algorithm>
using namespace std;

int arr[10000];

void swap(int a, int b) {

	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;

}


int partition(int left, int right) {

	int x = arr[right]; // pivot
	int i = left - 1; //pivot 보다 작은 원소들의 개수 -> 이 위치로 pivot보다 작은 원소를 현재 있는 위치에서 swap시켜준다.
	
	for (int j = left; j <= right - 1; j++) {

		if (arr[j] <= x) {
			i++;
			swap(i, j);
		}

	}

	swap(i + 1, right);


	return i + 1; // 정렬 후 pivot의 위치


}

void quickSort(int left, int right) {

	if (left < right) {

		int q = partition(left, right);
		quickSort(left, q - 1);
		quickSort(q + 1, right);


	}

	return;


}


int main() {

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {

		cin >> arr[i];

	}

	for (int i = 0; i < n; i++) {

		cout <<  arr[i] << " ";

	}

	cout << endl << endl;

	quickSort(0, n - 1);
	
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	
	return 0;
}