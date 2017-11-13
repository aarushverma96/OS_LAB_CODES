
#include <bits/stdc++.h>
using namespace std;
map<int, pair<int,int> > allocatedMem;
map<int,int>freedMem;
map<int,int>freedWorst;
map<int, pair<int,int> > allocatedWorst;
unordered_map<int,int> process;
int totalMem;
int totalFreeMem,totalFreeMemWorst;
int totalFreeBlk=0,totalFreeBlkWorst;
void allocator1(int id,int size)
{
    if(freedMem.size()==0)
    {
        printf("ERROR : OUT OF MEMEORY\n");
        return;
    }
    else if(allocatedMem.find(id)!=allocatedMem.end())
    {
        printf("ERROR : CANNOT ALLOCATE SPACE TO SAME PROCESS MORE THAN ONCE\n");
        return;
    }
    else if(totalFreeMem < size)
    {
        printf("ERROR : TOO LARGE SPACE REQUIRED\n");
        return;
    }
    map<int,int> :: iterator it = freedMem.lower_bound(size);
    if(it == freedMem.end())
    {
        printf("ERROR : REQUESTED SIZE CANNOT BE FULFILLED NOW TRY LATER\n");
        return;
    }
    pair<int,int> temp = *it;
    freedMem.erase(it);
    int startAddr = temp.second;
    temp.first -= size;
    temp.second += size;
    if(temp.first > 0)
        freedMem.insert(temp);
    else
        totalFreeBlk--;
    allocatedMem.insert(make_pair(id,make_pair(startAddr,size)));
    totalFreeMem -= size;
    printf("REQUEST %d : %dK\nBest Fit : Allocated at address %dK\n",id,size,startAddr);
    printf("%dk free ,%d block(s) , average size = %dk\n",totalFreeMem,totalFreeBlk,totalFreeMem/totalFreeBlk);
}
void deleter(int id)
{
    if(allocatedMem.find(id) == allocatedMem.end())
    {
        printf("ERROR : PROCESS DOES NOT EXIST CANNOT FREE MEMORY\n");
        return;
    }
    map<int,pair<int,int> > :: iterator it = allocatedMem.find(id);
    int size = it->second.second;
    int startAddr = it->second.first;
    freedMem.insert(make_pair(size,startAddr));
    allocatedMem.erase(it);
    totalFreeMem += size;
    totalFreeBlk++;
    printf("FREE REQUEST %d (%dk)\nBest Fit : Freed at address %d\n",id,size,startAddr);
    printf("%dk free ,%d block(s) , average size = %dk\n",totalFreeMem,totalFreeBlk,totalFreeMem/totalFreeBlk);
}
void worstAllocator(int id,int size)
{
    if(freedWorst.size()==0)
    {
        printf("ERROR : OUT OF MEMEORY\n");
        return;
    }
    else if(allocatedWorst.find(id)!=allocatedWorst.end())
    {
        printf("ERROR : CANNOT ALLOCATE SPACE TO SAME PROCESS MORE THAN ONCE\n");
        return;
    }
    else if(totalFreeMemWorst < size)
    {
        printf("ERROR : TOO LARGE SPACE REQUIRED\n");
        return;
    }
    auto it = freedWorst.crbegin();
    if(it->first < size)
    {
        printf("ERROR : TOO LARGE SPACE REQUIRED\n");
        return;
    }
    map<int,int> :: iterator irt = (--freedWorst.end());
    pair<int,int> temp = *it;
    freedWorst.erase(irt);
    int startAddr = temp.second;
    temp.first -= size;
    temp.second += size;
    if(temp.first > 0)
        freedWorst.insert(temp);
    else
        totalFreeBlkWorst--;
    allocatedWorst.insert(make_pair(id,make_pair(startAddr,size)));
    totalFreeMemWorst -= size;
    printf("REQUEST %d : %dK\nWorst Fit : Allocated at address %dK\n",id,size,startAddr);
    printf("%dk free ,%d block(s) , average size = %dk\n",totalFreeMemWorst,totalFreeBlkWorst,totalFreeMemWorst/totalFreeBlkWorst);
}
void deleterWorst(int id)
{
    if(allocatedWorst.find(id) == allocatedWorst.end())
    {
        printf("ERROR : PROCESS DOES NOT EXIST CANNOT FREE MEMORY\n");
        return;
    }
    map<int,pair<int,int> > :: iterator it = allocatedWorst.find(id);
    int size = it->second.second;
    int startAddr = it->second.first;
    freedWorst.insert(make_pair(size,startAddr));
    allocatedWorst.erase(it);
    totalFreeMemWorst += size;
    totalFreeBlkWorst++;
    printf("FREE REQUEST %d (%dk)\nWorst Fit : Freed at address %d\n",id,size,startAddr);
    printf("%dk free ,%d block(s) , average size = %dk\n",totalFreeMemWorst,totalFreeBlkWorst,totalFreeMemWorst/totalFreeBlkWorst);
}
int main()
{
    cin >> totalMem;
    freedMem[totalMem] = 0;
    freedWorst[totalMem] = 0;
    totalFreeBlk =1;
    totalFreeBlkWorst=1;
    totalFreeMem = totalMem;
    totalFreeMemWorst = totalMem;
    do
    {
        int id;
        cin >> id;
        if(id==-1)
            break;
        int request;
        cin >> request;
        if(request)
        {
            allocator1(id,request);
            worstAllocator(id,request);
        }
        else
        {
            deleter(id);
            deleterWorst(id);
        }
    }while(1);
    return 0;
}
