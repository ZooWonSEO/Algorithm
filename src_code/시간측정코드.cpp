#include <iostream>
#include <time.h>
using namespace std;


int main() {


	int n;
	int sum = 0;
	cin >> n;





	clock_t start, end;
	double result;
	start = clock();

//-----측정 코드 작성 부분 --------

	for (int i = 1; i <= n; i++) {
		sum = sum + i;
	}





//-----------------------------------------

	end = clock();
	result = (double)(end - start);
	
	printf("%f", result / CLOCKS_PER_SEC);
	cout << "sec";





	return 0;
}



#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {







	return 0;
}