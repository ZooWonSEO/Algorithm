#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

// test case
// -2 5 3 -4 7 10 2 8 -3 -5
// -1 1 4 5 -3 7 -2 5 4 -3
// 13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7


int arr[10000];


int main() {


	clock_t start, end;
	double result;
	start = clock();

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}


	//1.brute- force solution -> O(n^2) time
	// (n^2+n)/2 =>O(n^2)


	int ret = -999999;
	for (int i = 0; i < n; i++) {			//O(n) time

		int sum = 0;							// sum 초기화

		for (int j = i; j < n; j++) {		//O(n) time
			sum = sum + arr[j];
			ret = max(ret, sum);

		}
	}

	cout << ret << "\n";

	end = clock();
	result = (double)(end - start);

	cout << "수행시간 : ";
	printf("%f", result / CLOCKS_PER_SEC);
	cout << "sec";



	return 0;
}