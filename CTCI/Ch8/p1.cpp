#include<iostream>

using namespace std;
//basic recursive solution...
long steps(long n) {
	
	if(n<0){
		return 0;
	} else if(n==0){
		return 1;
	} else {
		return steps(n-1)+steps(n-2)+steps(n-3);
	}
}

int main(){
	long n;
	cin>>n;
	cout<<steps(n);
	return 0;
}