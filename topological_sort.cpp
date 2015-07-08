#include <bits/stdc++.h>
using namespace std;

vector<int> graph[10];
int n;
stack<int> s;
int visited[10];

void topological_sort(int index)
{
    visited[index]=1;
	for(int i=0;i<graph[index].size();i++)
	{
	   if(!visited[graph[index][i]]) topological_sort(graph[index][i]);
	}
	s.push(index);
}



void topological()
{
   for(int i=0;i<n;i++) visited[i]=0;
   for(int i=0;i<n;i++)
   {
       if(!visited[i])
	   {
	       topological_sort(i);
	   }
   }
   cout<<"topological sort: ";
   while(!s.empty()) 
   {
       cout<<s.top()<<" ";
	   s.pop();
   }   
}

int main()
{
   n=6;
   graph[5].push_back(2);
   graph[5].push_back(0);
   graph[2].push_back(3);
   graph[3].push_back(1);
   graph[4].push_back(0);
   graph[4].push_back(1);
   topological();
   return 0;
}
