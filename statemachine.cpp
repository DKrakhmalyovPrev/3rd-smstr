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
	vector<vector<char>> matr;
	vector<int> ifFin;

public:
	Graph(){};

	Graph(int a)
	{
		vector<char> q(a, 0);
		for (int j = 0; j < a; j++)
		{
			matr.push_back(q);
			ifFin.push_back(0);
		}

	}

	Graph(const Graph& x)
	{
		matr = x.matr;
		ifFin = x.ifFin;
	}


	void ScanGraph()
	{
		for (int i = 0; i < matr.size(); i++)
		for (int j = 0; j < matr.size(); j++)
			cin >> matr[i][j];
	}


	void PrintGraph() const
	{
		for (int i = 0; i < matr.size(); i++)
		{
			for (int j = 0; j < matr.size(); j++)
				cout << matr[i][j] << " ";
			cout << "\n";
		}
	}

	Graph(const vector<vector<char>> x)
	{
		matr = x;
	}

	void SetRib(int a, int b, char s)
	{
		matr[a][b] = s;
	}


	char GetRib(int a, int b) const
	{
		return(matr[a][b]);
	}

	void AddRib()
	{
		vector<char> q(matr.size(), 0);
		matr.push_back(q);
		for (int i = 0; i < matr.size(); i++)
			matr[i].push_back(0);
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
};

Graph ParsePat(vector<string>& pat)
{
	Graph bor(1);
	for (int i = 0; i < pat.size(); i++)
	{
		int curT = 0;
		for (int j = 0; j < pat[i].length(); j++)
		{
			int t = 0;
			for (int k = 0; k < bor.Size(); k++)
				if (bor.GetRib(curT, k) == pat[i][j])
				{
					curT = k;
					t = 1;
					k = bor.Size();
				}
			if (t == 0)
			{
				bor.AddRib();
				bor.SetRib(curT, bor.Size() - 1, pat[i][j]);
				curT = bor.Size() - 1;				
			}
		}
		bor.SetFin(curT);
	}

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
