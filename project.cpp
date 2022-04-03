#include<bits/stdc++.h>
using namespace std;
int gd,bs;
map<string,vector<int>> mp;
map<string,int> tim;
set<string> wh;
int global_time;
/*
Functions of my extendible hash program:
(i) Insert
(ii) Search
(iii) Delete
(iv) Modified Delete
(v) Display
(vi) Debugger (for easier analysis of data)
*/
void debugger(){
	for(int i=0;i<10;i++) cout<<"---";
	cout<<endl;
	cout<<"Time Array"<<endl;
	for(auto &i: tim){
		cout<<i.first<<' '<<i.second<<endl;
	}
	cout<<"Hash Array"<<endl;
	for(auto &i: mp){
		cout<<i.first<<" -> ";
		for(auto &j: i.second) cout<<j<<' ';
		cout<<endl;
	}
	cout<<"Present Array"<<endl;
	for(auto i: wh){
		cout<<i<<endl;
	}
	for(int i=0;i<10;i++) cout<<"---";
	cout<<endl;
}
void merge(string temp){
	if (temp.size()==1) return;
	string todiv;
	for(int i=0;i<temp.size()-1;i++){
		todiv.push_back(temp[i]);
	}
	string t1,t2;
	tim[todiv]=tim[temp];
	wh.insert(todiv);
	t1=todiv+"0";
	t2=todiv+"1";;
	for(auto &i: mp[t1]) mp[todiv].push_back(i);
	for(auto &i: mp[t2]) mp[todiv].push_back(i);
	mp.erase(t1);
	wh.erase(t1);
	tim.erase(t1);
	mp.erase(t2);
	wh.erase(t2);
	tim.erase(t2);
	string m1=todiv,m2=todiv;
	m1.pop_back();
	m2.pop_back();
	m1=m1+"0";
	m2=m2+"1";
	if (mp[m1].size()==0 || mp[m2].size()==0){
		merge(todiv);
	}
}
void div(vector<int> &data,string todiv){
	if (gd>=20){
		data.pop_back();
		cout<<"Sorry to say, but we can't accomodate this key"<<endl;
		return;
	}
	string t1=todiv+"0";
	string t2=todiv+"1";
	tim[t1]=tim[todiv];
	tim[t2]=global_time;
	//cout<<global_time<<endl;
	global_time++;
	tim.erase(todiv);
	mp.erase(todiv);
	wh.erase(todiv);
	wh.insert(t1);
	wh.insert(t2);
	mp[t1];
	mp[t2];
	gd=max(gd,(int)t1.size());
	for(auto &i: data){
		int xx=i;
		string temp;
		for(int i=0;i<gd;i++){
			temp.push_back(xx%2+48);
			xx/=2;
			if (wh.find(temp)!=wh.end()){
				break;
			}
		}
		mp[temp].push_back(i);
	}
	if (mp[t1].size()>bs){
		vector<int> tr=mp[t1];
		div(tr,t1);
	}
	if (mp[t2].size()>bs){
		vector<int> tr=mp[t2];
		div(tr,t1);
	}
}
void ins(int x){
	int xx=x;
	string temp;
	for(int i=0;i<gd;i++){
		temp.push_back(xx%2+48);
		xx/=2;
		if (wh.find(temp)!=wh.end()){
			break;
		}
	}
	if (mp[temp].size()<bs){
		mp[temp].push_back(x);
	}else{
		vector<int> tr=mp[temp];
		tr.push_back(x);
		div(tr,temp);
	}
}
void search(int x){
	int xx=x;
	string temp;
	for(int i=0;i<gd;i++){
		temp.push_back(xx%2+48);
		xx/=2;
		if (wh.find(temp)!=wh.end()){
			break;
		}
	}
	bool yon=false;
	for(auto &i: mp[temp]){
		if (i==x){
			yon=true;
			cout<<"Required query is in the table of "<<temp<<endl;
		}
	}
	if (!yon){
		cout<<"Required query is not there at all"<<endl;
	}
}
void del(int x){
	int xx=x;
	string temp;
	for(int i=0;i<gd;i++){
		temp.push_back(xx%2+48);
		xx/=2;
		if (wh.find(temp)!=wh.end()){
			break;
		}
	}
	bool yon=false;
	vector<int> newp;
	for(auto &i: mp[temp]){
		if (i==x){
			yon=true;
		}else{
			newp.push_back(i);
		}
	}
	mp[temp]=newp;
	if (!yon){
		cout<<"This key is not even there, how would I delete it?"<<endl;
	}else{
		cout<<"This key is deleted"<<endl;
	}
}
void fancy_del(int x){
	int xx=x;
	string temp;
	for(int i=0;i<gd;i++){
		temp.push_back(xx%2+48);
		xx/=2;
		if (wh.find(temp)!=wh.end()){
			break;
		}
	}
	bool yon=false;
	vector<int> newp;
	for(auto &i: mp[temp]){
		if (i==x){
			yon=true;
		}else{
			newp.push_back(i);
		}
	}
	mp[temp]=newp;
	if (!yon){
		cout<<"This key is not even there, how would I delete it?"<<endl;
	}else{
		cout<<"This key is deleted"<<endl;
	}
	if (mp[temp].size()==0){
		merge(temp);
	}
}
void display(){
	vector<pair<int,string>> v;
	for(auto &i: tim){
		v.push_back({i.second,i.first});
	}
	sort(v.begin(),v.end());
	cout<<gd<<endl;
	cout<<v.size()<<endl;
	for(auto &i: v){
		cout<<mp[i.second].size()<<' '<<i.second.size()<<endl;
	}
}
int main(){
	cin>>gd>>bs;
	global_time=(1<<gd)+1;
	for(int i=0;i<(1<<gd);i++){
		string temp;
		int ii=i;
		for(int j=0;j<gd;j++){
			temp.push_back(ii%2+48);
			ii/=2;
		}
		mp[temp];
		tim[temp]=i+1;
		wh.insert(temp);
	}
	while(true){
		int temp_gd=0;
		for(auto &i: wh) temp_gd=max(temp_gd,(int)i.size());
		gd=temp_gd;
		int inp;
		cin>>inp;
		if (inp==2){
			int x;
			cin>>x;
			ins(x);
		}else if(inp==3){
			int x;
			cin>>x;
			search(x);
		}else if(inp==4){
			int x;
			cin>>x;
			//del(x);
			fancy_del(x);
		}else if(inp==5){
			display();
		}else break;
		//debugger();
	}
}
