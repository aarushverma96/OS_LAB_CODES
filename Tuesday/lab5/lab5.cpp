#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

vector<int> adj[1000];
stack<char> s;
int visit[1000];
char str[10];

bool dfs(int i)
{
	bool check;
	
	if(visit[i]==1)
	{
		while(!s.empty())
		{
			char temp = s.top();
			s.pop();
			cout<< temp<<endl;
		}
		cout<< "Cycle Detected";
		return true;
	}
	
	//cout << i <<" was visited\n";
	s.push(i);
		
	visit[i]=1;
	check=false;
	for(int j=0;j<adj[i].size();j++)
	{
		check=dfs(adj[i][j]);
		if(check==true)
		{
			break;
		}
	}
	
	return check;
}


int main()
{
	int n,x,y,k;
	char a,b;
	bool cyc;
	
	ifstream f("graph.txt");
	while(f >> a >> b)
	{
		x=a;
		y=b;
		
		adj[x].push_back(y);
		memset(visit,0,sizeof(visit));		
		cyc=dfs(x);
		while(!s.empty())
			s.pop();
		
		
	}
	if(!cyc)
	{
		cout<< "Cycle Not Detected";
	}
}

