#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

// test case
// -2 5 3 -4 7 10 2 8 -3 -5
// -1 1 4 5 -3 7 -2 5 4 -3
// 13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7


int arr[10000];

int recur(int left, int right) {

	int sum = 0;

	//base case  : divide 되어서 1개가 될 때까지 나눈것
	if (left == right) {
		return arr[left];
	}

	//divide 해서 구하기 위해 mid value 구하기
	int mid = (left + right) / 2;

	int left_sum = -99999;
	int right_sum = -99999;

	//mid -> left 방향으로 더해준다
	//왜 left->"mid 방향으로 하면 안되냐? 할 수 있는데 maximum-subarray problem은 연속된 부분배열에 최댓값을 구하는 것이다.

	//이부분 test case 로 예시 들어주자


	for (int i = mid; i >= left; i--) {
		sum = sum + arr[i];
		left_sum = max(left_sum, sum);
	}

	sum = 0;
	for (int i = mid + 1; i <= right; i++) {
		sum = sum + arr[i];
		right_sum = max(right_sum, sum);
	}



	int single = max(recur(left, mid), recur(mid + 1, right));


	return max(left_sum + right_sum, single);


}


int main() {


	clock_t start, end;
	double result;
	start = clock();

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}


	//2. divide and conquer solution


	int ret = -999999;


	ret = recur(0, n - 1);




	cout << ret << "\n";

	end = clock();
	result = (double)(end - start);

	cout << "수행시간 : ";
	printf("%f", result / CLOCKS_PER_SEC);
	cout << "sec";



	return 0;
}