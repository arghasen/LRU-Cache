#include<iostream>
#include<map>
#include<list>
#define cacheSize 5
using namespace std;
class LRUCache{
	int i;
	map<int,pair<int,list<int>::iterator> > mymap;
	list<int> freeFrames, refHistory;
	public:
	LRUCache();
	void cacheRef(int a);
	int findLRUAndEvict();
};
int LRUCache::findLRUAndEvict()
{
	  int lruPage=refHistory.front();
	  mymap.erase(mymap.find(lruPage));
	  refHistory.pop_front();
	  return lruPage;
}
LRUCache::LRUCache()
{
	for (i=0; i<cacheSize; i++) 
		freeFrames.push_back(i);
}
void LRUCache::cacheRef(int a)
{
	int curFrame,lruPage;
	map<int,pair<int,list<int>::iterator> >::iterator it;
	list<int>::iterator it1;
	//"Find if already in cache"
	if(mymap.size()!=0)
	{
		it=mymap.find(a);
		if(it!=mymap.end())//iterator points to end if value not found in map
		{
			cout<<"Already in Cache "<<a<<endl;
			//chage refhistory and move the recent acess to the end of the list
			refHistory.splice(refHistory.end(),refHistory,(*it).second.second);
			return;
		}
	}
	//check if cache is having free frames
	if(freeFrames.size()!=0)
	{
		curFrame=freeFrames.front();
		freeFrames.pop_front();		
		cout<<"Cache miss"<<a<<"\n";
	}
	else
	{
		cout<<"CacheFull ";
		lruPage=findLRUAndEvict();
		cout<<lruPage<<"to be repalced by "<<a<<endl;
	}
	it1=refHistory.insert(refHistory.end(),a);
	mymap.insert(make_pair(a,make_pair(curFrame,it1)));
}
int main()
{
	int refString[20]={5,7,3,4,6,3,4,6,3,4,1,2,10,4,11,7,6,3,4,2};
	LRUCache lru;
	int i;
	for(i=0;i<20;i++)
	{
		lru.cacheRef(refString[i]);
	}
}
