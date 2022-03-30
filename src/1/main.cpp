#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	char n;
	cin>>n;
	if(n == 'N'||n == 'n') {
		cout<<"Naver D2";
	}
	else {
		cout<<"Naver Whale";
	}
		
	return 0;
}