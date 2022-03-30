#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Value {
	int pos;
	long long money;
	long long borrow;
	int borrowpoint;
	long long cnt;
	Value(int a,int b,int c,int d,int e) : pos(a), money(b),borrow(c),borrowpoint(d),cnt(e) {}
};

int n,m,k;
vector<int> cost;
long long res = -1;

void dfs(Value value);

int refund(Value& value) {
	if(value.money >= value.borrow&& value.borrow != 0) {
		value.money -= value.borrow;
		value.borrow = 0;
	} 
	else return 1;
	return 0;
}
int borr(Value& value) {
	if(value.borrow == 0) {
		value.borrow = value.money*k;
		value.money += value.borrow;
	}
	else return 1;
	return 0;
}
int buy(Value& value) {
	if(value.money >= cost[value.pos]) {
		value.cnt += value.money/cost[value.pos];
		value.money -= cost[value.pos] * value.cnt;
	}
	else return 1;
	return 0;
}
int sell(Value& value) {
	if(value.cnt != 0) {
		value.money += cost[value.pos]*value.cnt;
		value.cnt = 0; 
	}
	else return 1;
	return 0;
}

void func(Value value,int chk) {
	if(chk%2) {
		if(sell(value)) return;
	}
	chk>>=1;
	if(chk%2) {
		if(refund(value)) return;
	}
	chk>>=1;
	if(chk%2) {
		if(borr(value)) return;
	}
	chk>>=1;
	if(chk%2) {
		if(buy(value)) return;
	}
	chk>>=1;
	value.pos++;
	dfs(value);
}

void dfs(Value value) {
	if(value.pos >= n-1) {
		if(res < value.money||res == -1) {
			if(value.cnt == 0) {
				res = value.money;
			}
		}
		return;
	}
	for(int i = 0;i<16;i++) {
		if((i>>2) == 1) {
			continue;
		}
		func(value,i);
	}	

}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	cost.resize(n);
	for(int i = 0;i<n;i++) {
		cin>>cost[i];
	}

	dfs(Value(0,m,0,k,0));
	cout<<res;
	return 0;
}