#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>
#include <string>
#include<map>
using namespace std;

template<typename top, typename data>
class Graph
{
private:
	vector<map<top, data>> matr;
public:
	Graph(){};

	Graph(int a)
	{
		map<top, data> l;
		for (int j = 0; j < a; j++)
			matr.push_back(l);
	}

	Graph( Graph& x)
	{
		matr = x.matr;
	}

	Graph(Graph& x, Graph& y)
	{	map<top, data> l;
		for (int i = 0; i < x.Size() + y.Size(); i++)
			matr.push_back(l);
		for (auto it = x.matr[0].begin(); it != x.matr[0].end(); it++)
			matr[0][it->first] = it->second;
		for (auto it = y.matr[0].begin(); it != y.matr[0].end(); it++)
			matr[0][it->first + x.Size() - 1] = it->second;
		for (int i = 1; i < x.Size(); i++)
		{
			for (auto it = x.matr[i].begin(); it != x.matr[i].end(); it++)
				matr[i][it->first] = it->second*0.8;
			for (auto it = y.matr[i].begin(); it != y.matr[i].end(); it++)
				matr[i][it->first + x.Size() - 1] = it->second;
		}
		for (int i = x.Size()+1; i < y.Size() + x.Size(); i++)
		{
			for (auto it = x.matr[i - x.Size()].begin(); it != x.matr[i - x.Size()].end(); it++)
				matr[i-1][it->first] = it->second;
			for (auto it = y.matr[i - x.Size()].begin(); it != y.matr[i - x.Size()].end(); it++)
				matr[i-1][it->first + x.Size() - 1] = it->second*0.8;
		}

	}

	void ScanGraph(FILE*& inp)
	{
		for (int i = 0; i < this->Size(); i++)
		{
			int rib, data;
			fscanf(inp, "%d%d", &rib, &data);
			for (int j = 0; j < data; j++)
			{
				int l, m;
				fscanf(inp, "%d%d", &l, &m);
				matr[i][l] = m;
			}
		}
	}

	void SetRib(int a, top b, data s)
	{
		matr[a][b] = s;
	}


	int GetRib(int a, top b) 
	{
		return(matr[a][b]);
	}

	void AddRib()
	{
		map<top, data> q;
		matr.push_back(q);
	}

	int Size()
	{
		return(matr.size());
	}



	vector<int> Dijkstra(int start) 
	{
		vector<int> result(matr.size(), INT_MAX);
		vector<bool> ifbeen(matr.size(), 0);
		queue<int> que;
		que.push(start);
		ifbeen[start] = 1;
		result[start] = 0;
		while (!que.empty())
		{
			int ti = que.front();
			que.pop();
			for (auto it = matr[ti].begin(); it!=matr[ti].end(); it++)
				if ((ifbeen[it->first] == 0) || (result[it->first]>result[ti] + it->second))
				{
					result[it->first] = result[ti] + it->second;
					ifbeen[it->first] = 1;
					que.push(it->first);
				}
		}
		return(result);
	}

	int Dijkstra(int start, int finish) 
	{
		return(Dijkstra(start)[finish]);
	}




	vector<int> transport(Graph& second, int start) 
	{
		Graph i(*this, second);
		return(i.Dijkstra(start));
	}

	int transport(Graph& second, int start, int finish) 
	{
		return(transport(second, start)[finish] < transport(second, start)[finish + second.Size() - 1]
			? transport(second, start)[finish] : transport(second, start)[finish + second.Size() - 1]);

	}

};





void test_transport()
{
	FILE* inp = fopen("D:\\testtrans.txt.txt", "r+");
	cout << inp;
	
	int num_t;
	fscanf(inp, "%d", &num_t);
	for (int i = 0; i < num_t; i++)
	{
		int nr;
		fscanf(inp, "%d", &nr);
		Graph<int, int> frs(nr), snd(nr);
		frs.ScanGraph(inp);
		snd.ScanGraph(inp);
		int st, fin;
		fscanf(inp, "%d%d", &st, &fin);
		int res;
		fscanf(inp, "%d", &res);
		if (res != frs.transport( snd, st, fin))
			cout << "Invalid test";
		cout << frs.transport( snd, st, fin);
	}
	cout << "Tests fin";
}
int main()
{
	test_transport();
	
	
	return(0);
}
