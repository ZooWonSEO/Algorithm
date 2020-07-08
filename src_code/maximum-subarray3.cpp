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


	//3. dynamic programing


	int sum = -999999;
	int ret = -999999;


	for (int i = 0; i < n; i++) {


		sum = max(0, sum) + arr[i];		//sum의 값이 0보다 작으면 0으로 reset, +arr[i]를 하는 이유는 값이 음수만 나올수도 있기 때문
		ret = max(ret, sum);


	}




	cout << ret << "\n";

	end = clock();
	result = (double)(end - start);

	cout << "수행시간 : ";
	printf("%f", result / CLOCKS_PER_SEC);
	cout << "sec";



	return 0;
}