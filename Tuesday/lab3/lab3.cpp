#include <bits/stdc++.h>

using namespace std;
std::vector< std::vector<int> > processes;


bool func(std::vector<int> a,std::vector<int> b)
{
	return (a[1]<b[1]);
}


void strn()
{
	int n=0; //time counter
	bool flag=false;
	while(!flag)
	{
		sort(processes.begin(),processes.end(),func);
		n++;
		for (int i = 0; i < processes.size(); ++i)
		{
			std::vector<int> temp=processes[i];
			if (temp[0]<=n && temp[1]>0)
			{
				processes[i][1]--;//process executed.
			}
			else
			{
				processes[i][2]++;
			}
		}

		
		

		for (int i = 0; i < processes.size(); ++i)
		{
			if(processes[i][1]==0)
			{
				flag=true;
			}
			else
			{
				flag=false;
			}
		}

	}
}

int main()
{
	int n;
	cout << "Enter number of processes" << endl;
	cin >> n;

	cout << "generation of processes starts..." << endl;

	for (int i = 0; i < n; ++i)
	{
		std::vector<int> temp;
		int burst,arr;
		burst=rand()%10;
		arr=rand()%10;
		cout << "test:" << burst <<arr;
		temp.push_back(arr);
		temp.push_back(burst);
		temp.push_back(0);
		processes.push_back(temp);
	}
	cout << endl;

	for (int i = 0; i < processes.size(); ++i)
	{
		cout << processes[i][0] <<  "---" << processes[i][1] <<endl; 
	}
	//printst();
	strn();

	cout << "after algo execution"<< endl ;

	for (int i = 0; i < processes.size(); ++i)
	{
		cout << processes[i][0] <<  "---" << processes[i][1] << "--" << processes[i][2] <<endl; 
	}
}
