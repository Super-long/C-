#include<queue>
#include<map>
#include<vector>
#include<iostream>
#include<cstdio>
using namespace std;
typedef pair<int,int> pa;
int ans,root;
float sum;
map<int,string>mp;
map<string,char>se;
vector<int> vec[1000];
priority_queue<pa,vector<pa>,greater<pa>>que;
string book,str;
map<int,int>index_for_ans;
map<char,int>number;

void init(){
	while(que.size()!=1){
		pa xx = que.top();
		que.pop();
		pa yy = que.top();
		que.pop();
		que.push({xx.first+yy.first,++ans});
        vec[ans].push_back(xx.second);
        vec[ans].push_back(yy.second);
	}
	pa tmp = que.top();
	root = tmp.second;
}

void dfs(int index,const string& str){
	if(vec[index].empty()){
		mp[index_for_ans[index]] = str;
		se[str] = index_for_ans[index];
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
	getline(cin,book);
	size_t len = book.size();
	cin >> str;
	for(int i=0;i<len;++i){
		if(book[i]=='#') break;
		number[book[i]]++;
	}
	que.push({number[32],++ans});
    index_for_ans[ans] = 32;
    que.push({number[46],++ans});
    index_for_ans[ans] = 46;
	for(int i=65;i<=90;++i){
        que.push({number[i],++ans});
        index_for_ans[ans] = i;
    }
	for(int i=97;i<=122;++i){
        que.push({number[i],++ans});
        index_for_ans[ans] = i;
    }
 	init();
	dfs(root,"");
	for(int i=0;i<len;++i){
		cout << mp[book[i]];
		sum += mp[book[i]].size();
	}
	cout << endl;
	vector<char>temp;
	temp.assign(str.begin(),str.end());
	solve(temp,0);
	printf("%.2f\n",sum/len);
	return 0;
}