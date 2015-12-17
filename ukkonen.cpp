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

#define TOP_MAX 1000000 
#define INF 1000000000 
using namespace std;

//Тот же самый код, прокомментированный:

void ukkadd(int c, string in_str, int t[][26], int *l_edge, int *r_edge, int * par, int* s_link,
	int cur_t, int cur_pos, int num_t, int cur_symb) { // дописать к дереву символ c
suff:;      // будем приходить сюда после каждого перехода к суффиксу (и заново добавлять символ)
	if (r_edge[cur_t]<cur_pos) { // проверим, не вылезли ли мы за пределы текущего ребра
		// если вылезли, найдем следующее ребро. Если его нет - создадим лист и прицепим к дереву
		if (t[cur_t][c] == -1) {
			t[cur_t][c] = num_t; l_edge[num_t] = cur_symb; par[num_t++] = cur_t; cur_t = s_link[cur_t];
		cur_pos = r_edge[cur_t] + 1; goto suff; }
		cur_t = t[cur_t][c]; cur_pos = l_edge[cur_t]; // в противном случае просто перейдем к следующему ребру
	}
	if (cur_pos == -1 || c == in_str[cur_pos] - 'a') cur_pos++; else { // если буква на ребре совпадает с c то идем по ребру, а иначе
		// разделяем ребро на два. Посередине - вершина num_t
		l_edge[num_t] = l_edge[cur_t]; r_edge[num_t] = cur_pos - 1; par[num_t] = par[cur_t]; t[num_t][in_str[cur_pos] - 'a'] = cur_t;
		// ставим лист num_t+1. Он соответствует переходу по c.
		t[num_t][c] = num_t + 1; l_edge[num_t + 1] = cur_symb; p[num_t + 1] = num_t;
		// обновляем параметры текущей вершины. Не забыть про переход от предка cur_t к num_t.
		l_edge[cur_t] = cur_pos; par[cur_t] = num_t; t[par[num_t]][in_str[l_edge[num_t]] - 'a'] = num_t; num_t += 2;
		// готовимся к спуску: поднялись на ребро и перешли по суффиксной ссылке.
		// cur_pos будет отмечать, где мы в текущем суффиксе.
		cur_t = s[par[num_t - 2]]; cur_pos = l_edge[num_t - 2];
		// пока текущий суффикс не кончился, топаем вниз
		while (cur_pos <= r_edge[num_t - 2]) { cur_t = t[cur_t][in_str[cur_pos] - 'a']; cur_pos += r_edge[cur_t] - l_edge[cur_t] + 1; }
		// если мы пришли в вершину, то поставим в нее суффиксную ссылку, иначе поставим в num_t
		// (ведь на след. итерации мы создадим num_t).
		if (cur_pos == r_edge[num_t - 2] + 1) s_link[num_t - 2] = cur_t; else s_link[num_t - 2] = num_t;
		// устанавливаем cur_pos на новое ребро и идем добавлять букву к суффиксу.
		cur_pos = r_edge[cur_t] - (cur_pos - r_edge[num_t - 2]) + 2; goto suff;
	}
}

void build(string in_str, int t[][26], int *l_edge, int *r_edge, int * par, int* s_link,
	int cur_t, int cur_pos,int num_t,int cur_symb) 
{
	num_t = 2;
	cur_t = 0;
	cur_pos = 0;
	fill(r_edge, r_edge + TOP_MAX, (int)in_str.size() - 1);
	// инициализируем данные для корня дерева
	s_link[0] = 1;
	l_edge[0] = -1;
	r_edge[0] = -1;
	l_edge[1] = -1;
	r_edge[1] = -1;
	memset(t, -1, sizeof t);
	fill(t[1], t[1] + 26, 0);
	// добавляем текст в дерево по одной букве
	for (cur_symb = 0; cur_symb<(int)in_str.size(); ++cur_symb)
		ukkadd(in_str[cur_symb] - 'a', in_str, t, l_edge, r_edge, par, s_link, cur_t, cur_pos, num_t, cur_symb);
}

int main()
{
	string in_str; 
	int t[TOP_MAX][26],  // массив переходов (состояние, буква)
		l_edge[TOP_MAX],   // левая 
		r_edge[TOP_MAX],   // и правая границы подстроки из a, отвечающие ребру, входящему в вершину
		par[TOP_MAX],   // предок вершины
		s_link[TOP_MAX],   // суффиксная ссылка
		cur_t,     // вершина текущего суффикса (если мы посередине ребра, то нижняя вершина ребра)
		cur_pos,     // положение в строке соответствующее месту на ребре (от l[cur_t] до r[cur_t] включительно)
		num_t,     // количество вершин
		cur_symb;     // текущий символ строки
	build(in_str, t , l_edge, r_edge, par, s_link, cur_t, cur_pos, num_t, cur_symb);
	return(0);
}
