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

			 	vector<vector<int>> matr;
		
		public:
			 	Graph(){};
				
			 	Graph(int a)
			 	{
						vector<int> q(a, 0);
				 		for (int j = 0; j<a; j++)
				 			matr.push_back(q);
			 	}
				
				Graph(const Graph& x)
				{
					matr = x.matr;
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
				
				Graph(const vector<vector<int>> x)
				{
					 matr = x;
				}
				
				void SetRib(int a, int b, int s)
				{
					 matr[a][b] = s;
				}
				

				int GetRib(int a, int b) const
				{
					return(matr[a][b]);
				}

				void AddRib()
				{
					vector<int> q(matr.size(), 0);
					matr.push_back(q);
					for (int i = 0; i < matr.size(); i++)
						matr[i].push_back(0);
				}
					
				Graph Trans() const
				{
					Graph a(matr.size());
					for (int i = 0; i<a.matr.size(); i++)
						for (int j = 0; j<a.matr.size(); j++)
						 	a.SetRib(i, j, this->GetRib(j, i));
					return(a);
				}
				
				vector<int> BFS(int start) const
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
						for (int i = 0; i < matr.size(); i++)
						if ((matr[ti][i] == 1) && ((ifbeen[i] == 0) || (result[i]>result[ti] + 1)) && (ti!=i))
						{
							ifbeen[i] = 1;
							result[i] = result[ti] + 1;
							que.push(i);
						}
					}
					return(result);
				}

				int BFS(int start, int finish) const
				{
					return(BFS(start)[finish]);
				}

						
				vector<int> Dijkstra(int start) const
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
						for (int i = 0; i < matr.size(); i++)
						if ((matr[ti][i] != -1) && ((ifbeen[i] == 0) || (result[i] > result[ti] + matr[ti][i])) && (i!=ti))
						{
							result[i] = result[ti] + matr[ti][i];
							ifbeen[i] = 1;
							que.push(i);
						}
					}
					return(result);
				}

				int Dijkstra(int start, int finish) const
				{
					return(Dijkstra(start)[finish]);
				}

				void step(int cur, vector<int> & res, vector<bool> & ifbeen )
				{
					ifbeen[cur] = 1;
					for (int i = 0; i < matr.size();i++)
					if ((matr[cur][i] == 1) && ((ifbeen[i] == 0) || (res[i]>res[cur] + 1)) && (i != cur))
					{
						res[i] = res[cur] + 1;
						step(i, res, ifbeen);
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

/*				vector<int> Kosaraju()
				{
					
				}
				bool Sat2(string &str)
				{
					vector<char> let;
					for (int i = 0; i < str.length; i++)
					{

					}
				}
*/
				vector<int> findComp(int top)
				{
					Graph rev(this->Trans());
					vector<int> comp;
					vector<int> temp1= this->DFS(top);
					vector<int> temp2 = rev.DFS(top);
					for (int i = 0; i < this->matr.size();i++)
					if ((temp1[i] != -1) && (temp2[i] != -1))
						comp.push_back(i);
					return(comp);

				}

				vector<vector<int>> Components()
				{
					vector<vector<int>> compCon;
					vector<int> ifBeen;
					for (int i = 0; i < this->matr.size(); i++)
						ifBeen.push_back(i);
					while (ifBeen.size() != 0)
					{
						vector<int> temp=findComp(ifBeen[0]);
						for (int i = 0; i < temp.size();i++)
						for (int j = 0; j < ifBeen.size();j++)
						if (temp[i] == ifBeen[j])
						{
							for (int k = j; k < ifBeen.size() - 1; k++)
								ifBeen[k] = ifBeen[k + 1];
							ifBeen.pop_back();
						}
						compCon.push_back(temp);
					}

					return(compCon);
				}

				vector<double> transport(Graph& second, int start) const
				{
					vector<double> result(matr.size(), INT_MAX);
					vector<bool> ifbeen(matr.size(), 0);
					queue<int> que;
					vector<int> fromwhere(matr.size(),0);
					que.push(start);
					ifbeen[start] = 1;
					result[start] = 0;
					while (!que.empty())
					{
						int ti = que.front();
						que.pop();
						for (int i = 0; i < matr.size(); i++)
						{

							if ( (matr[ti][i] != -1) && ((ifbeen[i] == 0) || (result[i] > result[ti] + matr[ti][i]) || 
								((fromwhere[ti] == 1) && (result[i] > result[ti] + matr[ti][i]*0.8)) ) && (i != ti))
							{
								if (fromwhere[ti] == 1)
									result[i] = result[ti] + matr[ti][i] * 0.8;
								else
									result[i] = result[ti] + matr[ti][i];
								ifbeen[i] = 1;
								fromwhere[i] = 1;
								que.push(i);
							}
							if ((second.matr[ti][i] != -1) && ((ifbeen[i] == 0) || (result[i] > result[ti] + second.matr[ti][i]) ||
								((fromwhere[ti] == 2) && (result[i] > result[ti] + second.matr[ti][i] * 0.8))) && (i != ti))
							{
								if (fromwhere[ti] == 2)
									result[i] = result[ti] + second.matr[ti][i]*0.8;
								else
								result[i] = result[ti] + second.matr[ti][i];
								ifbeen[i] = 1;
								fromwhere[i] = 2;
								if (que.front()!=i)
								que.push(i);
							}
						}

					}
					return(result);
				}

				double transport(Graph& second, int start, int finish) const
				{
					return(transport(second,start)[finish]);
				}


};


int tiestep(vector<vector<int>>& OurMap, vector<vector<int>>& heur, vector<vector<int>>& result, int curv, int curh, int sidev, int sideh)
{
	if ((curv == sidev) && (curh == sideh))
		return(result[curv][curh]);

	if ((curv > 0) && (result[curv - 1][curh] == 0))
	{
		result[curv - 1][curh] = result[curv][curh] + OurMap[curv - 1][curh];
		heur[curv - 1][curh] = heur[curv][curh] + abs(sidev - curv) + abs(sideh - curh);
	}

	if ((curh > 0) && (result[curv][curh-1] == 0))
	{
		result[curv][curh-1] = result[curv][curh] + OurMap[curv][curh-1];
		heur[curv][curh-1] = heur[curv][curh] + abs(sidev - curv) + abs(sideh - curh);
	}

	if ((curh <99) && (result[curv][curh +1] == 0))
	{
		result[curv][curh + 1] = result[curv][curh] + OurMap[curv][curh + 1];
		heur[curv][curh + 1] = heur[curv][curh] + abs(sidev - curv) + abs(sideh - curh);
	}

	if ((curv <99) && (result[curv+1][curh] == 0))
	{
		result[curv+1][curh] = result[curv][curh] + OurMap[curv+1][curh];
		heur[curv+1][curh] = heur[curv][curh] + abs(sidev - curv) + abs(sideh - curh);
	}

	int minv, minh, minhe; minhe = heur[curv][curh];
	for (int i = 0; i < 100;i++)
	for (int j = 0; j < 100; j++)
		if ((heur[i][j] != 0) && (heur[i][j] < minhe) &&
			((result[i + 1][j] == 0) || (result[i][j + 1] == 0) || (result[i - 1][j] == 0) || (result[i][j - 1] == 0)))
		{
			minhe = heur[i][j];
			minv = i;
			minh = j;
		}
		int r = tiestep(OurMap, heur, result, minv, minh, sidev, sideh);
		return(r);
}

vector<int> tie(vector<vector<int>> & OurMap)
{
	vector<int> ti(100, 0);
	vector<vector<int>> heur;
	vector<vector<int>> result;
	for (int i = 0; i < 100; i++)
	{
		heur.push_back(ti);
		result.push_back(ti);
	}
	vector<int> tier(4);
	tier[0] = tiestep(OurMap, heur, result, 50, 50, 0, 0);
	for (int i = 0; i < 100; i++)
	{
		heur[i]=ti;
		result[i]=ti;
	}
	tier[3] = tiestep(OurMap, heur, result, 50, 50, 99, 99);
	for (int i = 0; i < 100; i++)
	{
		heur[i] = ti;
		result[i] = ti;
	}
	tier[2] = tiestep(OurMap, heur, result, 50, 50, 99, 0);
	for (int i = 0; i < 100; i++)
	{
		heur[i] = ti;
		result[i] = ti;
	}
	tier[1] = tiestep(OurMap, heur, result, 50, 50, 0, 99);
	return(tier);
}

int TwoSat(string ourStr)
{
	Graph relations;
	map<char, int> symbNum;
	int numLast=0;
	int co = 0;
	while(co < ourStr.length()-2)
	{
		while ((ourStr[co] < 'a') || (ourStr[co] > 'z'))
			co++;
		int dis1 = co;
		co++;
		while ((ourStr[co] < 'a') || (ourStr[co] > 'z'))
			co++;
		int dis2 = co;
		co++;
		{
			char q = ourStr[dis1];
			if (symbNum.find(q) == symbNum.end())
			{
				symbNum[q] = numLast;
				relations.AddRib();
				relations.AddRib();
				numLast += 2;
			}
			q = ourStr[dis2];
			if (symbNum.find(q) == symbNum.end())
			{
				symbNum[q] = numLast;
				relations.AddRib();
				relations.AddRib();
				numLast += 2;
			}
			
			if (ourStr[dis2 - 1] == '!')
			if (ourStr[dis1 - 1] == '!') 
			{
				relations.SetRib(symbNum[ourStr[dis2]]+1, symbNum[ourStr[dis1]], 1);
				relations.SetRib(symbNum[ourStr[dis1]]+1, symbNum[ourStr[dis2]], 1);
			}
			else
			{
				relations.SetRib(symbNum[ourStr[dis2]]+1, symbNum[ourStr[dis1]]+1, 1);
				relations.SetRib(symbNum[ourStr[dis1]], symbNum[ourStr[dis2]], 1);
			}
			else
			if (ourStr[dis1 - 1] == '!')
			{
				relations.SetRib(symbNum[ourStr[dis2]], symbNum[ourStr[dis1]], 1);
				relations.SetRib(symbNum[ourStr[dis1]]+1, symbNum[ourStr[dis2]]+1, 1);
			}
			else
			{
				relations.SetRib(symbNum[ourStr[dis2]], symbNum[ourStr[dis1]] + 1, 1);
				relations.SetRib(symbNum[ourStr[dis1]], symbNum[ourStr[dis2]] + 1, 1);
			}
			
		}

	}

	vector<vector<int>> comp = relations.Components();
	int result = 1;
	for (int i = 0; i < comp.size(); i++)
		sort(comp[i].begin(), comp[i].end());
	for (int i = 0; i < comp.size(); i++)
	for (int j = 0; j < comp[i].size()-1 ; j++)
	if ((comp[i][j] == comp[i][j + 1] - 1) && (comp[i][j] / 2 == comp[i][j + 1] / 2))
		result = 0;

	return(result);

}

int Salesman(Graph& roads)
{
	return(0);
}

 int main()
 {
	 //transport sol
	 int s;
	 cin >> s;
	 Graph gr(s);
	 gr.ScanGraph();
	 Graph gr2(s);
	 gr2.ScanGraph();
	 int st, fin;
	 cin >> st >> fin;
	 double g;
	 g = gr.transport(gr2, st, fin);
	 if (g == INT_MAX)
		 cout << "-1";
	 else
		 cout << g; 

	 return(0);
	 /*FILE* input = fopen("input.txt", "r");
	 FILE* output = fopen("output.txt", "w");
	 int n,g;
	 int st, fin;
	 fscanf(input, "%d%d%d", &n,&st, &fin);
	 vector<vector<int>> s;
	 vector<int> q(n, 0);
	 for (int j = 0; j<n; j++)
		 s.push_back(q);
	 for (int i = 0; i < n;i++)
	 for (int j = 0; j < n; j++)
	 {
		 fscanf(input, "%d", &g);
		 s[i][j] = g;
	 }

	 Graph gr(s);
	 g = gr.Dijkstra(st-1, fin-1);
	 if (g == INT_MAX) fprintf(output, "-1");
	 else
	 fprintf(output, "%d", g);*/
	 
	 /*string a;
	 getline(std::cin, a);
	 int i=TwoSat(a);
	 if (i)
		 cout << "YES";
	 else
		 cout << "NO";
	 return(0);*/

	 /*vector<int> ti(100, 2);
	 vector<vector<int>> test;
	 for (int i = 0; i < 100; i++)
		 test.push_back(ti);
	 vector<int> res = tie(test);
	 for (int i = 0; i < 4; i++)
		 cout << res[i] << " ";
	 return(0);*/


 };
