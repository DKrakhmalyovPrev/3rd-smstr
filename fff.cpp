/*#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>
#include <string>
#include <fstream>
#include<map>
using namespace std;
// std::ifstream cin("in_path");
template<typename top, typename data>
class Graph
{
public:
	vector<map<top, data> > matr;

	Graph(){};

	Graph(int a)
	{
		map<top, data> l;
		for (int j = 0; j < a; j++)
			matr.push_back(l);
	}

	Graph(Graph& x)
	{
		matr = x.matr;
	}
	Graph(const Graph& x, const Graph& y)
		{
		map<top, data> l;
		for (int i = 0; i < x.Size() + y.Size(); i++)
			 matr.push_back(l);
		for (auto it = x.matr[0].start(); it != x.matr[0].end(); it++)
			 matr[0][it.first] = it.second;
		for (auto it = y.matr[0].start(); it != y.matr[0].end(); it++)
			 matr[0][it.first + x.size() - 1] = it.second;
		for (int i = 1; i < x.Size(); i++)
			 {
			for (auto it = x.matr[i].start(); it != x.matr[i].end(); it++)
				+ matr[i][it.first] = it.second*0.8;
			for (auto it = y.matr[i].start(); it != y.matr[i].end(); it++)
				+ matr[i][it.first + x.size() - 1] = it.second;
			}
		for (int i = x.Size(); i < y.Size() + x.Size(); i++)
			 {
			for (auto it = x.matr[i].start(); it != x.matr[i].end(); it++)
				 matr[i][it.first] = it.second;
			for (auto it = y.matr[i].start(); it != y.matr[i].end(); it++)
				 matr[i][it.first - x.size()] = it.second*0.8;
			}
		
			}

	void ScanGraph(FILE*& inp)
	{
		for (int i = 0; i < this->Size(); i++)
		{
			int rib, data;
			fscanf(inp, "%d%d", &rib,&data);
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

	vector<int> BFS(int start) 
	{
		vector<int> result(matr.size(), -1);
		vector<bool> ifbeen(matr.size(), 0);
		queue<int> que;
		que.push(start);
		ifbeen[start] = 1;
		result[start] = 0;
		while (!que.empty())
		{
			int ti = que.front();
			que.pop();
			for (auto it = matr[ti].start(); it<matr[ti].end(); it++)
				if ((ifbeen[it.first()] == 0) || (result[it.first()]>result[ti] + 1))
				{
					ifbeen[it.first()] = 1;
					result[it.first()] = result[ti] + 1;
					que.push(it.first());
				}
		}
		return(result);
	}

	int BFS(int start, int finish) 
	{
		return(BFS(start)[finish]);
	}

	void step(int cur, vector<int> & res, vector<bool> & ifbeen)
	{
		ifbeen[cur] = 1;
		for (auto it = matr[ti].start(); it<matr[ti].end(); it++)
			if ((ifbeen[it.first()] == 0) || (res[it.first()]>res[cur] + 1))
			{
				res[it.first()] = res[cur] + 1;
				step(it.first(), res, ifbeen);
			}
	}

	vector<int> DFS(int start)
	{
		vector<int> result(matr.size(), -1);
		vector<bool> ifbeen(matr.size(), 0);
		stack<int> st;
		st.push(start);
		ifbeen[start] = 1;
		result[start] = 0;
		step(start, result, ifbeen);
		return(result);
	}

	int DFS(int start, int finish)
	{
		return(DFS(start)[finish]);
	}


	vector<double> Dijkstra(int start)
	{
		vector<double> result(matr.size(), INT_MAX);
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
				if ((ifbeen[(*it).first] == 0) || (result[(*it).first]>result[ti] + (*it).second))
				 {
					 result[(*it).first] = result[ti] + (*it).second;
					 ifbeen[(*it).first] = 1;
					 que.push((*it).first);
				}
		}
		return(result);
	}

	double Dijkstra(int start, int finish)
	{
		return(Dijkstra(start)[finish]);
	}
	int Find(int i, top s)
	{
		if (matr[i].find(s) != matr[i].end())
			return(matr[i][s]);
		else
			return(0);
	}


	void recLinks(vector<int>& links, int fathT, top symb)
	{
		if (matr[links[fathT]].find(symb) != matr[links[fathT]].end())
			if (matr[links[fathT]][symb] != matr[fathT][symb])
			{
				links[matr[fathT][symb]] = matr[links[fathT]][symb];
			}
			else
				links[matr[fathT][symb]] = 0;
		for (auto it = matr[matr[fathT][symb]].begin(); it != matr[matr[fathT][symb]].end(); it++)
		{
			recLinks(links, matr[fathT][symb], it->first);
		}
	}


	vector<int> Suff_link()
	{
		vector<int> links;
		for (int i = 0; i < matr.size(); i++)
			links.push_back(0);
		for (auto it = matr[0].begin(); it != matr[0].end(); it++)
		{
			recLinks(links, 0, it->first);
		}
		return(links);
	}


	vector<int> Fin_link(vector<int> links, vector<int> ifFin)
	{
		vector<int> finlinks;
		for (int i = 0; i < matr.size(); i++)
			finlinks.push_back(0);
		for (int i = 0; i < links.size(); i++)
			if (ifFin[i] == 1)
				if (ifFin[links[i]] == 1)
					finlinks[i] = links[i];
		return(finlinks);
	}


};

vector<double> transport(Graph<int, int>& first, Graph<int, int>& second, int start)
{
	Graph<int, int> i(first, second);
	return(i.Dijkstra(start));
}

double transport(Graph<int, int>& first, Graph<int, int>& second, int start, int finish)
{
	return(max(transport(first, second, start)[finish], transport(first, second, start)[finish + second.Size() - 1]));
}

Graph<char, int> ParsePat(vector<string>& pat, vector<int>& ifFin)
{
	Graph<char, int> bor(1);
	for (int i = 0; i < pat.size(); i++)
		ifFin.push_back(0);
	for (int i = 0; i < pat.size(); i++)
	{
		int curT = 0;
		for (int j = 0; j < pat[i].length(); j++)
		{
			if (bor.Find(curT, pat[i][j]))
			{
				curT = bor.Find(curT, pat[i][j]);
			}
			else
			{
				bor.AddRib();
				bor.SetRib(curT, pat[i][j], bor.Size() - 1);
				curT = bor.Size() - 1;
			}
		}
		ifFin[curT] = 1;
	}
	return(bor);
}

void Aho_Karasique()
{
	vector<string> patterns;
	string ourStr;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cin >> ourStr;
		patterns.push_back(ourStr);
	}
	cin >> ourStr;
	vector<int> ifFin;
	Graph<char, int> bor = ParsePat(patterns, ifFin);
	vector<int> links = bor.Suff_link();
	vector<int> fin_links = bor.Fin_link(links, ifFin);
}*/
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
