//1766 ¹®Á¦Áý

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;

vector<int> v[32005];
int result[32005];

int indegree[32005];

int main() {

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {

		int input1, input2;
		cin >> input1 >> input2;

		v[input1].push_back(input2);
		indegree[input2]++;
	}


	for (int i = 1; i <= n; i++) {
	
		if (indegree[i] == 0) {
			pq.push(i);
		}
	}

	while (!pq.empty()) {

		int tmp = pq.top();
		cout << tmp << " ";
		pq.pop();

		for (int i = 0; i < v[tmp].size(); i++) {
			int next = v[tmp][i];
			indegree[next]--;
			if (indegree[next] == 0) {
				pq.push(next);
			}
		}

	}


	return 0;
}