#include <iostream>
#include <algorithm>
using namespace std;


int input[1000];
int b[1000];
int c[10];
int n;

int mx = -1;

void init() {

	for (int i = 0; i < 1000.; i++) {
		b[i] = 0;
	}

	for (int i = 0; i < 10; i++) {
		c[i] = 0;
	}

}

void countingSort(int digit) {

	init();

	for (int i = 1; i <= n; i++) {
		c[(input[i] / digit) % 10] ++;
	}

	for (int i = 0; i < 10; i++) {
		c[i] = c[i] + c[i - 1];
	}


	for (int i = n; i >= 1; i--) {
		b[c[(input[i]/digit) % 10]] = input[i];
		c[(input[i] / digit) % 10]--;
	}

	for (int i = 1; i <= n; i++) {
		input[i] = b[i];
	}

	cout << "sorting Сп : ";
	for (int i = 1; i <= n; i++) {
		
		cout << input[i] << " ";

	}

	cout << endl;
}



int main() {


	cin >> n;


	for (int i = 1; i <= n; i++) {
		cin >> input[i];
	}

	cout << "Before : ";
	for (int i = 1; i <= n; i++) {
		
		cout << input[i] << " ";
	}
	cout << endl;

	for (int i = 1; i<= n; i++) {
		mx = max(mx, input[i]);
	}

	for (int e = 1; mx / e > 0; e = e * 10) {
		countingSort(e);
	}



	return 0;
}