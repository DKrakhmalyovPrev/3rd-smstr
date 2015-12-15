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
		vector<map<char, int>> q(a);
		for (int j = 0; j < a; j++)
			ifFin.push_back(0);

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
		ifFin[matr.size() - 1] = 0;
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


}
