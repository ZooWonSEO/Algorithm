#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> v[32005];
bool visited[32005];

stack<int> s;

void dfs(int start) {

	visited[start] = true;

	for (int i = 0; i < v[start].size(); i++) {

		int next = v[start][i];
		if (visited[next] == false) {
			dfs(next);
		}

	}

	s.push(start);

}


int main() {

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int input1, input2;
		cin >> input1 >> input2;

		v[input1].push_back(input2);

	}

	for (int i = 1; i <= n; i++) {
		if (visited[i] == false) {
			dfs(i);
		}
	}

	while (!s.empty()) {

		cout << s.top() << " ";
		s.pop(); 

	}


	return 0;
}