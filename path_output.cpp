#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

vector<int> getpermutation(int n){
	vector<int> v;
	for(int i=1;i<n+1;i++){
		v.push_back(i);
	}
	return v;
}

void print(vector<int> v){
	for(int i=0;i<v.size();i++)
		cout<<v[i];
}

int main(){
    int n;cin>>n;
    string path;cin>>path;
    vector<int> perm;
    perm = getpermutation(n);
    for(int i=1;i<path.length();i=i+2){
        reverse(perm.begin(),perm.begin()+path[i]-'0');
    }
    print(perm);
    cout<<endl;
    return 0;
}