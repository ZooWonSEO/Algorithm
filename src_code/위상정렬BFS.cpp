#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> v[32005];
bool visited[32005];

queue<int> q;

int indegree[32005];

int result[32005];
int idx = 0;

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
			q.push(i);
		}
	}

	while (!q.empty()) {

		int now = q.front();
		visited[now] = true;
		q.pop();
		cout << now << " ";
		for (int i = 0; i < v[now].size(); i++) {
			int next = v[now][i];
			indegree[next] --;
			if (visited[next] == false && indegree[next]==0) {
				q.push(next);
			}
		}

	}



	return 0;
}