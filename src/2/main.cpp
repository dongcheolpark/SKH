#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n,w,t,k;

void giveWood(vector<int> &v,int pos) {
	vector<int> cnt(n,0);
	for(int i = 0;i<n;i++) {
		if(i != 0) {
			if(v[i-1]>0)  {
				cnt[i]++;
			}
		}
		if(i != n-1) {
			if(v[i+1]>0) cnt[i]++;
		}
	}
	for(int i = 0;i<n;i++) {
		if(pos == i) continue;
		v[i] -= 3-cnt[i];
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin>>n>>w>>t>>k;

	vector<int> v;

	v.resize(n);

	for(int i = 0;i<n;i++) {
		cin>>v[i];
	}	
	queue<pair<int,vector<int>>> q;
	q.push(make_pair(-1,v));
	for(int i = 0;i<t-1;i++) {
		int m = q.size();
		for(int i = 0;i<m;i++) {
			auto front = q.front();
			q.pop();
			giveWood(front.second,front.first);
			int next = (i == 0)? w : front.first;

			q.push(make_pair(next,front.second));
			if(!((next+1)>=n)) 
			q.push(make_pair(next+1,front.second));
			if(!(next-1<0))
			q.push(make_pair(next-1,front.second));

		}
	}

	int res = 0;
	while(!q.empty()) { 
		auto front = q.front();
		q.pop();
		int cnt = 0;
		giveWood(front.second,front.first);
		for(auto item : front.second) {
			if(item > 0) cnt++;
		}
		if(cnt >= k) res++;

		/*cout<<front.first<<" ";
		for(auto item : front.second) {
			cout<<item<<' ';
		}
		cout<<'\n';*/
	}
	cout<<res;
	return 0;
}