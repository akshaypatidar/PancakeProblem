#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <bits/stdc++.h>
#include <string> 
#include <unistd.h>

using namespace std;

vector<string> CANONICAL;
int factorial (int n){
	if(n==0) return 1;
	else return n*factorial(n-1);
}
vector<int> getpermutation(int n){
	vector<int> v;
	for(int i=1;i<n+1;i++){
		v.push_back(i);
	}
	return v;
}
struct node{
	int depth;
	bool visited;
	vector<int> permutation;
	vector< vector <int> > adjacent;
	vector<string> moves;
	node(){
		visited = false;
	}
}; 


void myreverse(string s,string &ans){
	ans="";
	for(int i=s.length()-1;i>0;i=i-2){
		ans = ans + "r" + s[i];
	}
	return;
}

void canonical(string path,string &ans){

	int start = 0;
	int max = path[1]-'0';
	vector<int> current;
	current.push_back(max);
	int i=3;
	while(i<path.length()){
		if(path[i]-'0' > max){
			max = path[i]-'0';
			start = i-1;
			current.clear();
			current.push_back(max);
			i=i+2;
		}
		else if(path[i]-'0' == max){
			vector<int> next;
			next.push_back(path[i]-'0');
			current.push_back(path[i]-'0');
			for(int j=2;j<current.size()+1;j=j+2){
				if(path[(i+j)%path.length()]-'0' > max){
					max = path[(i+j)%path.length()]-'0';
					start = (i+j-1)%path.length();
					current.clear();
					current.push_back(max);
					i=i+j+2;
					break;
				}
				else if(path[(i+j)%path.length()]-'0' == current[j/2]){
					current.push_back(path[(i+j)%path.length()]-'0');
					next.push_back(path[(i+j)%path.length()]-'0');
				}
				else if(path[(i+j)%path.length()]-'0' < current[j/2]){
					current.push_back(path[(i+j)%path.length()]-'0');
					i=(i+j+2);
					break;
				}
				else{
					next.push_back(path[(i+j)%path.length()]-'0');
					start = i-1;
					i=i+j+2;
					current = next;
					break;
				}
			}

		}
		else{
			current.push_back(path[i]-'0');
			i=i+2;
		}
		
	}

	ans="";
	for(int k=0;k<path.length();k++){
		ans=ans+path[(k+start)%path.length()];
	}
	return;

	
}

void canonical_form(string Path,string &ans){
	string possibilty1,possibilty2,temp;
	canonical(Path,possibilty1);
	myreverse(Path,temp);
	canonical(temp,possibilty2);
	string answer = possibilty1;

	for(int i=1;i<possibilty1.length();i=i+2){
		if(possibilty2[i] == possibilty1[i] ){

		}
		else if(possibilty2[i] - '0' > possibilty1[i] - '0'){
			answer = possibilty2;
			break;
		}
		else{
			break;
		}
	}
	canonical(answer,ans);
	return;
}

void print(vector<int> v){
	for(int i=0;i<v.size();i++)
		cout<<v[i];
}

void DFS_count_cycles(int size,vector<int> perm,vector<int> iden,int &count, map<vector<int>, node > pancakegraph,string path){
	pancakegraph[perm].visited = true;
	if(count > 0){return;}
	if(size == 0){

		pancakegraph[perm].visited=false;
		for(int i=0;i<pancakegraph[perm].adjacent.size();i++){
			if(iden == pancakegraph[perm].adjacent[i]){
				//cout<<path+pancakegraph[perm].moves[i]<<endl;
				//string s;
				//canonical_form(path+pancakegraph[perm].moves[i],s);
				//CANONICAL.push_back(s);
				count++;
			}			
		}
		return;
		//print(perm);cout<<endl;
	}
	else{
		for(int i=0;i<pancakegraph[perm].adjacent.size();i++){
			if(!pancakegraph[pancakegraph[perm].adjacent[i]].visited){
				DFS_count_cycles(size-1, pancakegraph[perm].adjacent[i],iden, count, pancakegraph,path+pancakegraph[perm].moves[i]);
			}
		}
		pancakegraph[perm].visited=false;
	}

}

int main(){
	int n;
	cin>>n;
	map<vector<int>, node > pancakegraph;
	vector<int> perm=getpermutation(n);
	node temp;
	temp.permutation=perm;
	temp.depth=0;

	pancakegraph[perm] = temp;
	queue<vector<int> > q;
	q.push(perm);

	while(!q.empty()){
		for(int i=0;i<n;i++){
			vector<int> temp=q.front();
			reverse(temp.begin(),temp.begin()+i+1);
			for(int j=0;j<i+1;j++){
				temp[j] = temp[j]*(-1);
			}
			pancakegraph[q.front()].adjacent.push_back(temp);
			pancakegraph[q.front()].moves.push_back("r"+to_string(i+1));
			if(pancakegraph.count(temp) == 0){
				node t;
				t.permutation = temp;
				t.depth = pancakegraph[q.front()].depth+1;
				pancakegraph[temp]=t;				
				q.push(temp);
			}
		}
		q.pop();
	}
	
	

	
	int size_of_cycle;
	int count=0;
	//cout<<"Enter Size of Cycle\n";
	//cin>>size_of_cycle;
	for(int i=8;i<48;i++){
		//size_of_cycle = i;
		count=0;
		DFS_count_cycles(i-1,perm,perm,count,pancakegraph,"");
		cout<<endl<<"There are "<<count<<" cycles of size "<<i<<endl;

		/*if(count > 0){
			map<string,int> uniqueforms;
			vector<string> canonicalform[6];
			cout<<endl<<"There are "<<count<<" cycles of size "<<size_of_cycle<<endl;
			/*for(int i=0;i<CANONICAL.size();i++){
				
				if(uniqueforms.count(CANONICAL[i]) == 0){
					int no = std::count(CANONICAL[i].begin(),CANONICAL[i].end(),n+'0');
					canonicalform[no].push_back(CANONICAL[i]);			
					uniqueforms[CANONICAL[i]] = 1;
				}
				else{
					uniqueforms[CANONICAL[i]]++;
				}
			}
			for(int i=2;i<6;i++){
				if(canonicalform[i].size()>0){
					cout<<"From "<<i<<" Copies "<<endl<<endl;
					for(int j=0;j<canonicalform[i].size();j++){
						cout<<canonicalform[i][j]<<endl;
					}
					cout<<endl;
				}
			}
		}
		else{
			cout<<"There are no cycle of size "<<size_of_cycle<<endl;
		}*/
	}


	return 0;	
}