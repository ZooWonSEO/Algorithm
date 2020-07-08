#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Vertex structure
struct Vertex {

    int city_num;
    string city_name;
    int population;
    long long int leader_cost;
    int leader_size;

    Vertex(int num, string name, int pop) {
        this->city_num = num;
        this->city_name = name;
        this->population = pop;
        this->leader_cost = 0;
        this->leader_size = 1;
    }

    Vertex() {
        city_num = 0;;
        city_name = "";
        population = 0;
        leader_cost = 0;
        leader_size = 0;
    }
};

// Edge structure
struct Edge {

    int v1, v2;
    long long int cost;

    Edge(int v1, int v2, long long int cost) {
        this->v1 = v1;
        this->v2 = v2;
        this->cost = cost;
    }

    Edge() {
        v1 = 0;
        v2 = 0;
        cost = 0;
    }
};

Vertex city[1000003]; // 도시(Vetex) 배열, 각 번호에 속하는 vertex에 바로 접근하기 위해서 도시번호 범위만큼 생성
Edge road[500003]; // 도로(Edge) 배열
vector<list<int>> sets; // disjoint sets
int set_pos[1000003]; // 도시가 속한 집합이 몇번째 집합인지 저장하는 table
int union_cnt = 0; // union 성공횟수, N-1이 되면 모든 집합이 union 되었다는 것이므로 알고리즘 종료
int edge_cnt = 0; // edge의 가중치가 제일 적은 것 부터 접근하기 위한 index 변수 

int N = 0;
int M = 0;
int q = 0;

// 조건 2를 만족시키기 위한 compare함수 
bool compare(Edge a, Edge b) {

    // 두 Edge의 cost가 같을경우
    if (a.cost == b.cost) {

        int tmp1 = 0; // Edge a에 연결된 두 도시의 인구수의 합
        int tmp2 = 0; // Edge b에 연결된 두 도시의 인구수의 합

        tmp1 = city[a.v1].population + city[a.v2].population;
        tmp2 = city[b.v1].population + city[b.v2].population;

        // 두 도시의 인구수의 합도 같을 경우 
        if (tmp1 == tmp2) {

            int comp1 = 0;
            int comp2 = 0;

            if (a.v1 < a.v2) {
                comp1 = a.v1;
            }
            else {
                comp1 = a.v2;
            }

            if (b.v1 < b.v2) {
                comp2 = b.v1;
            }
            else {
                comp2 = b.v2;
            }
            return comp1 < comp2; // Edge 양 끝을 구성하는 두 도시의 가장 작은 city_num에 대해서 오름차순 정렬
        }
        return tmp1 > tmp2; // Edge 양 끝에 연결된 두 도시의 인구합의 대해서 내림차순 정렬
    }
    // Edge의 cost가 다를경우 cost에 대해서 오름차순 정렬
    else {
        return a.cost < b.cost;
    }
}

// Union-Find의 find연산, num이 속한 집합을 retrun  
list<int> myfind(int num) {

    list<int> lt;
    lt = sets[set_pos[num]];
    return lt;
}

// splice되는 list의 원소들의 leader table을 붙여지는 집합의 leader로 update
void move_leader(list<int> lt, int new_pos) {

    list<int> ::iterator iter;
    iter = lt.begin();
    for (iter; iter != lt.end(); iter++) {
        int tmp = *iter;
        set_pos[tmp] = new_pos;
    }
}

// Union-Find의 union연산, 두 개의 집합을 확인해서 사이클이 생기지 않으면 union
int myunion(list<int> l1, list<int> l2, long long int cost) {

    // 두 도시가 속한 집합의 leader 도시 번호 파악
    int leader1 = 0;
    int leader2 = 0;

    // myfind연산으로 받은 집합의 head가 도시가 속한 집합의 leader 도시 번호 
    leader1 = l1.front();
    leader2 = l2.front();


    int size1 = 0;
    int size2 = 0;

    size1 = city[leader1].leader_size;
    size2 = city[leader2].leader_size;

    list<int> ::iterator iter;

    int type = 0;

    // l1의 집합의 개수가 l2의 집합의 개수보다 많으면 l2 집합을 l1 집합의 tail에 연결
    if (size1 > size2) {
        type = 1;
    }

    // l1의 집합의 개수와 l2의 집합의 개수가 같다면 집합의 leader 도시 번호를 비교해서 도시 번호가 더 작은 집합의 tail에 도시 번호가 더 큰 집합을 연결
    else if (size1 == size2) {

        // 이 경우 leader1이 속한 집합의 tail에 leader2가 속한 집합을 연결 
        if (leader1 < leader2) {
            type = 1;
        }

        // 이 경우 leader2가 속한 집합의 tail에 leader1이 속한 집합을 연결 
        else if (leader1 > leader2) {
            type = 2;
        }
    }

    // l2의 집합의 개수가 l1의 집합의 개수보다 많으면 l1 집합을 l2 집합의 tail에 연결
    else if (size1 < size2) {
        type = 2;
    }

    // 집합이 구성하는 MST의 비용계산 
    long long int total_cost = 0;
    total_cost = cost + city[leader1].leader_cost + city[leader2].leader_cost;

    int res = 0; // 새로 형성된 집합의 leader 도시 번호 

    if (type == 1) {

        move_leader(l2, set_pos[leader1]);   // 가중치-유니온 휴리스틱 적용
        iter = l1.end(); // leader1이 속한 집합의 tail pointer
        l1.splice(iter, l2); // l1의 tail에 l2를 연결
        sets[set_pos[leader1]] = l1;

        city[leader1].leader_cost = total_cost; // leader1이 새로운 집합의 leader가 되었으므로 leader1의 도시에 cost정보 저장
        city[leader1].leader_size += city[leader2].leader_size;

        res = leader1;

    }

    else if (type == 2) {

        move_leader(l1, set_pos[leader2]);   // 가중치-유니온 휴리스틱 적용
        iter = l2.end(); // leader1이 속한 집합의 tail pointer
        l2.splice(iter, l1); // l2의 tail에 l1을 연결
        sets[set_pos[leader2]] = l2;

        city[leader2].leader_cost = total_cost; // leader2가 새로운 집합의 leader가 되었으므로 leader2의 도시에 cost정보 저장
        city[leader2].leader_size += city[leader1].leader_size;

        res = leader2;

    }
    return res;
}

// kruskal 알고리즘, ch에 따라서 1번 작동 또는 종료될 때 까지 작동 
void kruskal(char ch) {

    // edge_cnt번재 edge를 가져와서 edge에 저장된 정보 불러오기
    Edge tmp = road[edge_cnt];

    // Edge의 양 끝 vertex
    int city1 = 0;
    int city2 = 0;
    city1 = tmp.v1;
    city2 = tmp.v2;

    // Edge cost
    long long int w = 0;
    w = tmp.cost;

    // 두 도시가 속한 집합 받아오기
    list<int> set1;
    list<int> set2;

    set1 = myfind(city1);
    set2 = myfind(city2);

    //cout << set1.front() << " " << set2.front() << endl;

    // union이 실패했으면 실패 문구 출력
    if (set1.front() == set2.front()) {
        // query가 I일 경우에만 문구 출력
        if (ch == 'I') {
            cout << "not union" << '\n';
        }
        edge_cnt++; // 1개의 Edge에 대해서 확인했으므로 다음 edge_cnt 증가 
        return;
    }

    else {

        // union 연산 진행 
        int new_leader = -1;
        new_leader = myunion(set1, set2, w);
        edge_cnt++; // 1개의 Edge에 대해서 확인했으므로 다음 edge_cnt 증가 

        if (new_leader > 0) {
            union_cnt++; // union이 성공했으므로 union_cnt 증가

            int ID = 0;
            int S = 0;
            int v = 0;
            long long int D = 0;

            ID = new_leader;
            S = city[new_leader].leader_size; //new_leader 도시가 속한 집합의 개수 
            v = ID;
            D = city[v].leader_cost;

            // query가 'I'일 때 출력 문구
            if (ch == 'I') {

                if (union_cnt == (N - 1)) {
                    cout << ID << " " << S << " " << v << " " << D << endl;
                    exit(0);
                }
                else {
                    cout << ID << " " << S << '\n';
                    return;
                }
            }

            // query가 'Q'일 때 출력 문구
            else if (ch == 'Q' && (union_cnt == (N - 1))) {
                cout << ID << " " << D << '\n';
                return;
            }
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<int> set_id; // set_id 설정을 위한 vector

    cin >> N >> M >> q;

    int city_num = 0;
    int population = 0;
    string city_name = "";

    int vertex1 = 0;
    int vertex2 = 0;
    long long int cost = 0;

    for (int i = 0; i < 1000003; i++) {
        set_pos[i] = -1;
    }

    // 도시(vertex)입력
    for (int i = 0; i < N; i++) {
        cin >> city_num >> city_name >> population;
        city[city_num] = Vertex(city_num, city_name, population);
        set_id.push_back(city_num);
    }

    // 도로(edge)입력
    for (int i = 0; i < M; i++) {
        cin >> vertex1 >> vertex2 >> cost;
        road[i] = Edge(vertex1, vertex2, cost);
    }

    // kruskal 알고리즘을 진행하기 위해서 Edge의 cost에 대해서 오름차순으로 정렬
    // cost가 같을 경우 주어진 조건에 대해서 정렬하기 위한 기준 compare 사용
    sort(road, road + M, compare);

    // 입력받은 순서대로 disjoin sets 생성
    int v_sz = set_id.size();
    for (int i = 0; i < v_sz; i++) {
        list<int> init; // 초기 1개의 원소를 가지는 집합 생성
        init.push_back(set_id[i]);
        sets.push_back(init); // disjoint sets에 list 추가 

        set_pos[set_id[i]] = i; // city_num 집합의 sets의 순서 
    }

    for (int i = 0; i < q; i++) {

        char query;
        cin >> query;

        // query가 N일 때 : 특정 도시가 포함된 연결리스트의 내부 정보 파악 
        if (query == 'N') {

            int v_n = 0;
            int k_n = 0;
            int x = 0;
            string y = "";

            cin >> v_n >> k_n;

            list<int> n_lt;
            list<int>::iterator n_iter;
            n_lt = myfind(v_n); // v_n이 속한 집합을 불러오기

            int sz_n = 0;
            sz_n = city[n_lt.front()].leader_size; // v_n이 속한 집합의 크기 확인

            n_iter = n_lt.begin(); // n_lt의 head pointer

           // k_n이 v_n이 속한 집합의 크기보다 작으면 집합의 head에서 k_n번 만큼 tail쪽으로 이동
            if (k_n < sz_n) {
                for (int j = 0; j < k_n; j++) {
                    n_iter++;
                }

                x = *n_iter; // 도시 v_n이 포함된 리스트의 헤드로부터 k번째 도시의 번호 
                y = city[x].city_name;  // 도시 v_n이 포함된 리스트의 헤드로부터 k번째 도시명

                cout << x << " " << y << '\n';
            }

            // k_n이 v_n이 속한 집합의 크기보다 클 때의 출력문구
            else {
                cout << "no exist" << '\n';
            }
        }

        // query가 'L'일 때 : 특정 도시가 포함된 연결리스트의 크기 
        else if (query == 'L') {

            int v_l = 0;
            cin >> v_l;

            list<int> v_lt;
            v_lt = myfind(v_l); // v_l이 속한 집합을 불러오기

            int sz_l = 0;
            sz_l = city[v_lt.front()].leader_size; // v_l이 속한 집합의 크기 

            cout << sz_l << '\n';
        }

        // query가 'I'일 때 : Kruskal 알고리즘에서 하나의 반복 진행
        else if (query == 'I') {
            kruskal('I');
        }

        // query가 'F'일 때: 두 도시가 같은 집합에 속하는지 확인 
        else if (query == 'F') {

            int v_f1 = 0;
            int v_f2 = 0;

            cin >> v_f1 >> v_f2;

            list<int> f_lt1;
            list<int> f_lt2;

            f_lt1 = myfind(v_f1); // v_f1이 속한 집합을 불러오기
            f_lt2 = myfind(v_f2); // v_f2가 속한 집합을 불러오기

            // 두 집합의 leader가 같다면 
            if (f_lt1.front() == f_lt2.front()) {
                cout << "True" << " " << f_lt1.front() << '\n';
            }

            // 두 집합의 leader가 다르다면 
            else if (f_lt1.front() != f_lt2.front()) {
                cout << "False" << " " << f_lt1.front() << " " << f_lt2.front() << '\n';
            }
        }

        // query가 'W'일 때 : 임의의 도시를 포함하는 집합의 모든 포장도로의 길이 
        else if (query == 'W') {

            int v_w = 0;
            cin >> v_w;

            list<int> v_lt;
            v_lt = myfind(v_w); // v_w가 속한 집합을 불러오기

            long long int w_cost = 0;
            w_cost = city[v_lt.front()].leader_cost; // v_w가 속한 집합의 leader 도시 정보에 저장된 집합의 모든 포장도로의 길이 불러오기

            cout << w_cost << '\n';
        }

        // query가 'Q'일 때 : Kruskal 알고리즘의 나머지 단계 연속수행 및 프로그램 종료 
        else if (query == 'Q') {
            while (1) {
                if (union_cnt == (N - 1)) {
                    exit(0);
                }
                kruskal('Q');
            }
        }
    }

    return 0;
}