#include<queue>
#include<map>
#include<vector>
#include<iostream>
using namespace std;
int ans = 6;
typedef pair<int,int> pa;
int root;
map<int,string>mp;
map<string,char>se;
vector<int> vec[30];
int book[10];
priority_queue<pa,vector<pa>,greater<pa> >que;
void init(){
	while(que.size()!=1){
		pa xx = que.top();
		que.pop();
		pa yy = que.top();
		que.pop();
		pa curr = make_pair(xx.first+yy.first,++ans);
		que.push(curr);
		vec[ans].push_back(xx.second);
		vec[ans].push_back(yy.second);
	}
	pa tmp = que.top();
	root = tmp.second;
}

void dfs(int index,string str){
	if(vec[index].empty()){
		mp[index] = str;
		se[str] = index+'A'-1;
		return;
	}
	dfs(vec[index][0],str+'0');
	dfs(vec[index][1],str+'1');
}

void solve(vector<char>& temp,int index){
	size_t len = temp.size();
	string str;
	while(index != len){
		str.push_back(temp[index++]);
		if(se.find(str)!=se.end()){
			cout << se[str];
			str.clear();
		}
	}
	cout << endl;
}

int main(){
	for(int i=0;i<6;++i){
		cin >> book[i];
		que.push({book[i],i+1});
	}
	string str1,str2;
	cin >> str1 >> str2;
	init();
	dfs(root,"");
	for(int i=0;i<6;++i){
		char ch = 'A'+i;
		cout << ch << ":"<<mp[i+1] << endl;
	}
	vector<char>temp;
	temp.assign(str2.begin(),str2.end());
	for(int i=0;i<str1.size();++i){
		cout << mp[str1[i]-'A'+1];
	}
	cout << endl;
	solve(temp,0);
	return 0;
}