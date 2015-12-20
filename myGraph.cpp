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

	Graph(const Graph& x)
	{
		matr = x.matr;
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
		map<top,data> q;
		matr.push_back(q);
	}

	int Size()
	{
		return(matr.size());
	}

	void SetFin(int i)
	{
		ifFin[i] = 1;
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

Graph<char,int> ParsePat(vector<string>& pat, vector<int>& ifFin)
{
	Graph<char,int> bor(1);
	for (int i = 0; i < pat.size(), i++)
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
		ifFin[curT]=1;
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
	vector<int> fin_links = bor.Fin_link(links,ifFin);
}

int main()
{
	
	return(0);
}
