#include <iostream>
#include <algorithm>
using namespace std;

int arr[100000];

int recurBinarySearch(int left, int right, int find) {

	if (left > right) {
		return -1;
	}

	int mid = (left + right )/ 2;

	if (arr[mid] == find) {
		return mid;
	}

	else {

		if (find<arr[mid]) {
			return recurBinarySearch(left, mid - 1, find);
		}

		else if (find>arr[mid]) {
			return recurBinarySearch(mid + 1, right, find);
		}

	}

}


int main() {

	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {

		cin >> arr[i];

	}

	sort(arr, arr + n);

	int k;
	cin >> k;

	int ret =recurBinarySearch(0, n - 1, k);

	cout << ret;


	return 0;
}