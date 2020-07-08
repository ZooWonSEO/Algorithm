#include <iostream>
#include <string>
using namespace std;

struct node {
	
	int elem;
	node* next;
	node* pre;

};

class myQueue {

private:
	int sz;
	node* head;
	node* tail;

public:
	myQueue() {
		sz = 0;
		head = NULL;
		tail = NULL;
	}

	int size() {
		return sz;
	}

	int empty() {
		if (sz == 0) {
			return 1;
		}

		else {
			return 0;
		}

	}

	void push(int x) {

		node* tmp = new node();
		tmp->elem = x;
	

		if (sz == 0) {
			head = tmp;
			tail = tmp;
			head->next = tail;
			tail->pre = head;
		}

		else {
			tail->next = tmp;
			tail = tmp;
			tail->next = head;
		}

		sz++;

	}

	int pop() {

		if (sz==0) {
			return -1;
		}

		else {
			node* tmp = new node();
			tmp = head;
			head = head->next;
			sz--;
			return tmp->elem;
			
		}
	}

	int back() {

		if (sz == 0) {
			return -1;
		}

		else {
			return tail->elem;
		}
	}

	int front() {

		if (sz==0) {
			return -1;
		}

		else {
			return head->elem;
		}
	}
};


int main() {

	myQueue q;

	int n;
	cin >> n;
	int ret = 0;

	for (int i = 0; i < n; i++) {

		string input;
		cin >> input;

		if (input == "push") {
			int num;
			cin >> num;
			q.push(num);
		}

		else if (input == "front") {

			ret = q.front();
			cout << ret << endl;

		}

		else if (input == "back") {

			ret = q.back();
			cout << ret << endl;

		}

		else if (input == "size") {

			ret = q.size();
			cout << ret << endl;

		}

		else if (input == "empty") {

			ret = q.empty();
			cout << ret << endl;

		}

		else if (input == "pop") {
			
			ret = q.pop();
			cout << ret << endl;
		}

	}


	return 0;
}