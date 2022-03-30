#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <limits.h>

using namespace std;

int n,m;
vector<vector<pair<int,int>>> dist;
vector<int> res2;
vector<int> res,dontgo;
vector<int> path,path2;
int path_size = 1,path2_size = 1,maximum = 0;


void print(int i) {
	if(i == 0) {
		cout<<i+1<<' ';
		return;
	}
	print(path[i]);
	if(i == n-1) {
		cout<<i+1;
		return;
	}
	cout<<i+1<<' ';
}

void dijkstra(int st,bool chk) {
	if(chk) {
		res[st] = 0;
	}
	else res2[st] = 0;
	priority_queue<pair<int,int>> pq;
	pq.push(make_pair(st,0));
	while(!pq.empty()) {
		int current = pq.top().first;
		int distance = -pq.top().second;
		pq.pop();
		if(res[current] < distance) continue;
		for(int i = 0;i<dist[current].size();i++) {
			int next = dist[current][i].first;
			int nextDistance = distance + dist[current][i].second;
			if(res[next] >= nextDistance) {
				if(res[next] == nextDistance) {
					if(dontgo[next] == 0) continue;
				}
				if(chk&&!dontgo[next]) {
					continue;
				}
				if(chk) {
					res[next] = nextDistance;
				}
				else res2[next] = nextDistance;
				pq.push(make_pair(next,-nextDistance));
				if(chk) {
					path[next] = current;
					path_size++;
				}
				else {
					path2[next] = current;
					path2_size++;

				}
			}
		}

	}
}


int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin>>n>>m;

	dist.resize(n);
	res.resize(n);
	res2.resize(n);
	path.resize(n);
	path2.resize(n);
	dontgo.resize(n);
	
	for(int i = 0;i<n;i++) {
		res[i] = INT_MAX;
		res2[i] = INT_MAX;
	}

	for(int i = 0;i<m;i++) {
		int a,b,k;
		cin>>a>>b>>k;
		dist[a-1].push_back(make_pair(b-1,k));
	}

	for(int i = 0;i<n;i++) {
		cin>>dontgo[i];
		if(dontgo[i]) maximum++;
	}

	dijkstra(0,1);
	dijkstra(0,0);
	int chk = 0;
	int size2 = 1;
	for(int i = n-1;i!=0;i = path2[i]) {
		if(dontgo[i]) {
			size2++;
		}
	}
	if(size2>=maximum) {
		chk = 1;
	}

	if(res[n-1] <= res2[n-1]||chk) {
		int size = 1;
		for(int i = n-1;i!=0;i = path[i]) {
			size++;
		}
		if(size < maximum) {
			cout<<-1;
			return 0;
		}
		cout<<size<<'\n';
		print(n-1);
	}
	else cout<<-1;

	return 0;
}