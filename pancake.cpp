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

	int k;
	cout<<"Enter k\n";
	cin>>k;

	int min_n,max_n;
	cout<<"Enter minimum value of n\n";
	cin>>min_n;
	cout<<"Enter maximum value of n\n";
	cin>>max_n;


	int type;

	cout<<"Enter 0 for Pancake and 1 for Burnt Pancake\n";
	cin>>type;

	if(type != 0 && type != 1){
		cout<<"Invalid Type"<<endl;
		exit(0);
	}

	for(int n=min_n;n<=max_n;n++){

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
				for(int i=1-type;i<n;i++){
					vector<int> temp=q.front();
					
					if(type==0){
						reverse(temp.begin(),temp.begin()+i+1);
					}
					else{
						reverse(temp.begin(),temp.begin()+i+1);
						for(int k=0;k<i+1;k++){
							temp[k]=temp[k]*(-1);
						}
						/*cout << i <<"\t";
						for(int k=0;k<n;k++){
							cout<<temp[k];
						}
						cout<<endl;*/
					}
					
					
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

		cout<<"n = "<<n<<" -> count = "<<count<<endl;
	}



	return 0;
}