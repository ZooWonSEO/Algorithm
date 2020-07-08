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


		sum = max(0, sum) + arr[i];		//sum�� ���� 0���� ������ 0���� reset, +arr[i]�� �ϴ� ������ ���� ������ ���ü��� �ֱ� ����
		ret = max(ret, sum);


	}




	cout << ret << "\n";

	end = clock();
	result = (double)(end - start);

	cout << "����ð� : ";
	printf("%f", result / CLOCKS_PER_SEC);
	cout << "sec";



	return 0;
}