#include <iostream>
#include <map>
#include <vector>
#include <bits/stdc++.h> 
#include <queue>
#include <string>

using namespace std;


struct node{
	vector<int> permutation;
	int depth;
	vector<vector<int> > adjacent;
};

vector<int> getpermutation(int n){
	vector<int> v;
	for(int i=1;i<n+1;i++){
		v.push_back(i);
	}
	return v;
}

int main(){

	int n,k;
	cin>>n>>k;
	map<vector<int>, node > pancakegraph;
	vector<int> perm=getpermutation(n);
	node temp;
	temp.permutation=perm;
	temp.depth=0;

	pancakegraph[perm] = temp;
	queue<vector<int> > q;
	q.push(perm);

	int count=0;
	while(!q.empty()){
		if(pancakegraph[q.front()].depth == k){
			break;
		}
		else{
			for(int i=1;i<n;i++){
				vector<int> temp=q.front();
				
				reverse(temp.begin(),temp.begin()+i+1);
				
				if(pancakegraph.count(temp) == 0){
					
					node t;
					t.permutation = temp;
					t.depth = pancakegraph[q.front()].depth+1;
					pancakegraph[temp]=t;
					if(t.depth==k)count++;
					pancakegraph[q.front()].adjacent.push_back(temp);
					q.push(temp);

				}				
			}
			q.pop();
		}
	}

	cout<<count<<endl;



	return 0;
}