 #define _CRT_SECURE_NO_WARNINGS
 #include <iostream> 
 #include <stdio.h>
 #include <cstdlib>
 #include <math.h>
 #include <vector>
 #include <queue>
 #include <stack>
 #include <limits.h>
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
					for (int i = 0; i<matr.size(); i++)
						for (int j = 0; j<matr.size(); j++)
						 	cin >> matr[i][j];
				}
				

				void PrintGraph() const
				{
					for (int i = 0; i<matr.size(); i++)
					{
						for (int j = 0; j<matr.size(); j++)
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

					

};


 int main()
 {
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
	 
	 int st, fin;
	 Graph s(5);
	 scanf("%d%d", &st, &fin);
	 s.ScanGraph();
	 printf("%d", s.Dijkstra(st-1, fin-1));

	 return(0);

 };
