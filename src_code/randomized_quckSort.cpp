#include <iostream>
#include <ctime>
#include <Windows.h>
#include <stdio.h>
using namespace std;

int arr[10000];

void swap(int a, int b) {

	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;

}


int random(int left, int right) {


	return (int)(rand() % (right - left + 1)) + left;

}

int random_partition(int left, int right) {

	int ran = random(left, right);
	cout << "·£´ý Index ÀÔ´Ï´Ù : " << ran << endl;
	swap(ran, right);

	int x = arr[right];
	int i = left - 1;

	for (int j = left; j <= right - 1; j++) {

		if (arr[j] <= x) {
			i++;
			swap(i, j);
		}
		

	}

	swap(i + 1, right);
	return i + 1;


}

void quickSort(int left, int right) {

	if (left < right) {

		int q = random_partition(left, right);


		quickSort(left, q - 1);
		quickSort(q + 1, right);


	}

	return;

}


int main() {


	srand(GetTickCount());

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	cout << endl << endl;

	quickSort(0, n - 1);

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}



	return 0;
}