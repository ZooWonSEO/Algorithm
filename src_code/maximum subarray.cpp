#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

/*
1. brute-force 
2. divide and conquer
3. dynamic programming

*/




int arr[10000];
int res = -999999;

//divide and conquer
int recur(int low, int high) {


	if (low == high) {
		return arr[low];
	}


	int mid = (low + high) / 2;

	int left = -999999;
	int right = -999999;

	int sum = 0;

	for (int i = mid; i >= low; i--) {
		sum = sum + arr[i];
		left = max(left, sum);

	}

	sum = 0;
	for (int i = mid + 1; i <= high; i++) {
		sum = sum + arr[i];
		right = max(right, sum);
	}


	int single = max(recur(low, mid), recur(mid + 1, high));


	int tmp= max(single, max(right, left));

	return max(right + left, tmp);

}



int main() {

	int n;
	cin >> n;



	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	// -2 5 3 -4 7 10 2 8 -3 -5
	// -1 1 4 5 -3 7 -2 5 4 -3


	//brute-force solution



	for (int i = 0; i < n; i++) {

		int sum = 0;

		for (int j = i; j < n; j++) {

			sum = sum + arr[j];
			res = max(sum, res);
			
		}
	}
	cout << res << "\n";


	cout << endl;


	//divide and conquer solution

	res = -999999;

	res = recur(0, n - 1);

	cout << res << endl;


	// dynamic programing

	int ret = -999999;
	int psum = -999999;

	for (int i = 0; i < n; i++) {

		psum = max(psum, 0) + arr[i];
		ret = max(ret, psum);

	}


	cout << ret << endl;




	return 0;
}