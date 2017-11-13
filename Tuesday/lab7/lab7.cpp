#include <bits/stdc++.h>

using namespace std;



unordered_set<int> s;
vector<int> page;
unordered_map<int,int> recPages; 
int pageFault=0;
	



int main()
{


	int capacity;
	int pageRef;
	cout << "Enter Total number od Physical Mempry frames." << endl;
	cin >> capacity;
	cout << "Enter Number of page refrences" << endl;
	cin >> pageRef;

	cout << "Enter Page Refrences"<< endl;

	for(int i=0;i<pageRef;i++)
	{
		int temp;
		cin >> temp;
		page.push_back(temp);
	} 

	for (int i = 0; i < page.size(); ++i)
	{
		if(s.size()<capacity)
		{
			if(s.find(page[i])==s.end())
			{
				pageFault++;
				s.insert(page[i]);
			}
			recPages[page[i]]=i;
		}

		else
		{
			if(s.find(page[i])==s.end())
			{
				int lru,val;
				lru=INT_MAX;
				for (auto it=s.begin(); it!=s.end(); it++)
				{
					if (recPages[*it] < lru)
					{
						lru = recPages[*it];
						val = *it;
					}
				}

				s.erase(val);
				s.insert(page[i]);
				pageFault++;
			}
		}
	
		unordered_set<int>::iterator iter;

		for(iter=s.begin(); iter!=s.end();++iter) 
		{
			cout << *iter; 
		}
		
	}

	cout << endl << pageFault << endl;
}