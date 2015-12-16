/* Реализован Алгоритм Ахо-Карасика. По данному массиву паттернов строится бор разбора и выдаётся отдельная структура
с суффиксными ссылками. При необходимости и в зависимости от задачи можно написать функции нахождения подстроки, кол-ва вхождений подстрок 
и т.д. */

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


class Graph
{
private:
	vector<map<char,int>> matr;
	vector<int> ifFin;
	

public:
	Graph(){};

	Graph(int a)
	{
		map<char, int> l;
		for (int j = 0; j < a; j++)
		{
			matr.push_back(l);
			ifFin.push_back(0);
		}
	}

	Graph(const Graph& x)
	{
		matr = x.matr;
		ifFin = x.ifFin;
	}

	void SetRib(int a, char b, int s)
	{
		matr[a][b] = s;
	}


	int GetRib(int a, char b)
	{
		return(matr[a][b]);
	}

	void AddRib()
	{
		map<char, int> q;
		matr.push_back(q);
		ifFin.push_back(0);
	}

	int Size()
	{
		return(matr.size());
	}
	
	void SetFin(int i)
	{
		ifFin[i] = 1;
	}

	int Find(int i, char s)
	{
		if (matr[i].find(s) != matr[i].end())
			return(matr[i][s]);
		else
			return(0);
	}

	void recLinks(vector<int>& links, int fathT, char symb)
	{
		if (matr[links[fathT]].find(symb) != matr[links[fathT]].end())
			if(matr[links[fathT]][symb] != matr[fathT][symb])
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

};

Graph ParsePat(vector<string>& pat)
{
	Graph bor(1);
	for (int i = 0; i < pat.size(); i++)
	{
		int curT = 0;
		for (int j = 0; j < pat[i].length(); j++)
		{
			if (bor.Find(curT,pat[i][j]))
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
		bor.SetFin(curT);
	}
	return(bor);
}


int main()
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
	Graph bor = ParsePat(patterns);
	vector<int> links = bor.Suff_link();
	for (int i = 0; i < links.size(); i++)
		cout << links[i] << " ";
	return(0);
}
