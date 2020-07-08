//2623번 음악 프로그램

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> v[1002];
int indegree[1002];

queue<int> q;

int arr[1002];
int result[1002];

void init() {
	for (int i = 0; i < 1002; i++) {
		
		arr[i] = 0;
	}
}

int main() {

	int n, m;
	cin >> n >> m;

	while (m--) {

		init();

		int time;
		cin >> time;

		for (int i = 0; i < time; i++) {
			cin >> arr[i];
		}

		for (int i = 0; i < time - 1; i++) {
			v[arr[i]].push_back(arr[i + 1]);
			indegree[arr[i+1]]++;
		}

	}
	 

	for (int i = 1; i <= n; i++) {
		if (indegree[i] == 0) {
			q.push(i);
		}
	}


	bool check = false;

	for (int i = 0; i < n; i++) {

		if (q.empty()==true) {
			check = true;
			break;
		}

		int now = q.front();
		q.pop();
		result[i] = now;
		
		for (int j = 0; j < v[now].size(); j++) {
			int next = v[now][j];
			indegree[next]--;

			if (indegree[next] == 0) {
				q.push(next);
			}
		}

	}

	if (check == true) {
		cout << 0;
	}

	else {
		for (int i = 0; i < n; i++) {
			cout << result[i] << '\n';
		}
	}
	

	return 0;
}