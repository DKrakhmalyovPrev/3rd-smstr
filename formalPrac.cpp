/*Практикум по формальным языкам.
Задание 9: Дан язык, заданный регулярным выражением и слово из алфавита {a,b,c}.
Проверить, содержит ли язык данное слово.

Правка 1: Программа не проходит тесты, содержащие вложенные "*". Будет исправлено в следующих версиях.
Правка 2: Налажена работа с вложенными "*", появились проблемы с чтением первого символа.
Правка 3: Программа работает корректно с первым символом и сложными конструкциями циклов и вариаций. Время работы остаётся
экспоненциальным(относительно количества "*" в выражении).
Правка 4: Выставлены комментарии, поясняющие алгоритм разбора регулярного выражения. Исключён вывод лишних символов 
(остались рудиментами-маркерами для первичного тестирования). Программа работает корректно благодаря небольшим правкам в алгоритм.
*/


#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

string ParseStupid(string regularExp)
//Рудимент, переводящий обратную польскую запись в традиционное регулярное выражение. Оставлен для пущего понимания схемы выражения. 
{
	vector<string> myStack;
	for (int i = 0; i < regularExp.length(); i++)
	{
		if (regularExp[i] == '.')
		{
			myStack[myStack.size() - 2] = myStack[myStack.size() - 2] + myStack[myStack.size() - 1];
			myStack.pop_back();
		}
		else
		if (regularExp[i] == '+')
		{

			myStack[myStack.size() - 2] = myStack[myStack.size() - 2] + "+" + myStack[myStack.size() - 1];
			myStack.pop_back();
		}
		else
		if (regularExp[i] == '*')
			myStack[myStack.size() - 1] = "(" + myStack[myStack.size() - 1] + ")*";
		else
		{
			string a = "0";
			a[0] = regularExp[i];
			//vector<string> t;
			//t.push_back(a);
			myStack.push_back(a);
		}
		return(myStack[0]);
	};
}

vector<vector<string>> ParseSmart(string regularExp)
//Метод, разбирающий регулярное выражение и выкатывающий двумерный вектор строк для дальнейшего разбора
{
	vector<vector<string>> ourStack;
	for (int i = 0; i < regularExp.length(); i++)
	{
		if ((regularExp[i] >= 'a') && (regularExp[i] <= 'd'))
		{
			vector<string> ti;
			string a = "0";
			a[0] = regularExp[i];
			ti.push_back(a);
			ourStack.push_back(ti);
		}
		// Для всякой следующей буквы из алфавита заводится вектор строк в порядке их использования в выражении
		else
		if ((regularExp[i] == '.') && ((regularExp[i - 1] >= 'a') && 
		(regularExp[i - 1] <= 'd')) && ((regularExp[i - 2] >= 'a') && (regularExp[i - 2] <= 'd')))
		{
			for (int j = 0; j < ourStack[ourStack.size() - 1].size(); j++)
				ourStack[ourStack.size() - 2][j] += ourStack[ourStack.size() - 1][j];
			ourStack.pop_back();
		}
		// Для двух букв из алфавита в выражении подряд выполняется конкатенация внутри одной строки
		else
		if (regularExp[i] == '+')
		{
			for (int i = 0; i < ourStack[ourStack.size() - 1].size(); i++)
				ourStack[ourStack.size() - 2].push_back(ourStack[ourStack.size() - 1][i]);
			ourStack.pop_back();
		}
		// Для оператора '+' выполняется конкатенация двух последних векторов
		else
		if (regularExp[i] == '*')
		{	
			int q = 1;
			string YC("YOUCANSKIPIT");
			ourStack[ourStack.size() - q].push_back(YC);
			string a("0");
			a[0] = '0' + q;
			ourStack[ourStack.size() - q].push_back(a);
			int hm = i - 1;
			while ((regularExp[hm] == '.') && (hm>=0))
			{
				ourStack[ourStack.size() - q].push_back(YC);
				a[0] = '0' + q;
				ourStack[ourStack.size() - q].push_back(a);
				q++;
				hm--;
			}
		}
		//Для оператора '*' по последнему вектору ставится маркер, который позже используется 
		//при разборе и количество символов, которое определяется длиной скобки, по которой стоит *
		else
		{
			cout << "Выполнен ввод неверного символа. Пожалуйста, перепроверьте входные данные.";
			vector<vector<string>> nul;
			return(nul);
			//Выводим ошибку, создавая фиктивный пустой вектор и возвращаем его, чтобы при дальнейшем разборе 
			//не удалось получить результатов
		}
	}
	return(ourStack);
	//Собственно, возвращаем вектор с разобранным выражением
}

int JustDoIt(vector<vector<string>>& ourStack, string ourWord, int stackPos, int wordPos)
//Рекурсивная функция, разбирающая выражение посимвольно и проходящая по всему недетерменированному автомату. 
//Если успех был достигнут хоть раз -- он выносится в ответ
{
	if ((stackPos == ourStack.size()) && (wordPos == ourWord.length()))
		return(1);
	if ((stackPos >= ourStack.size()) || (wordPos > ourWord.length()))
		return(0);
	string YC("YOUCANSKIPIT");

	int ifAns = 0;
	int ifstar = 0;
	if (ourStack[stackPos].size() >= 3) 
		if(ourStack[stackPos][ourStack[stackPos].size()-2].compare(YC) == 0)
			ifstar = 1;
	//т.н. Маркер звёздочки. Показывает, что данное состояние содержит пустой переход и некий цикл.
	for (int i = 0; i < ourStack[stackPos].size(); i++)
	{
		if (ourStack[stackPos][i].compare(YC) == 0)
		{
			ifAns += JustDoIt(ourStack, ourWord, stackPos + (ourStack[stackPos][i + 1][0] - '0'), wordPos);
		}
		//Переносит область работы на длину цикла по звезде(то, что можно не использовать в слове), запуская рекурсию
		int co = 0;
		int j = 0;
		if (ourStack[stackPos][i].length() <= ourWord.length() - wordPos)
		while (j < ourStack[stackPos][i].length())
		{
			if (ourStack[stackPos][i][j] != ourWord[wordPos + j])
				co = 1;
			j++;
		}
		if (co == 0)
		{
			ifAns += JustDoIt(ourStack, ourWord, stackPos + 1, wordPos + ourStack[stackPos][i].length());
			if (ifstar == 1)
				ifAns += JustDoIt(ourStack, ourWord, stackPos, wordPos + ourStack[stackPos][i].length());
		}
		//Соответственно, проверяет для всех вариантов из вектора, можно ли пройти по "ребру", который те задают. 
		//Если имелась звёздочка-- запускает цикл, возвращаясь в исходное состояние
	}
	if (ifAns>0)
		return(1);
	else
		return(0);
}
int main()
{
	string regularExp;
	string ourWord;

	cin >> regularExp;
	cin >> ourWord;
	vector<vector<string>> ourStack = ParseSmart(regularExp);
	if (JustDoIt(ourStack, ourWord, 0, 0))
		cout << "YES";
	else
		cout << "NO";
	/*for (int i = 0; i < ourStack.size(); i++)
	{
		cout << '\n';
		for (int j = 0; j < ourStack[i].size(); j++)
			cout << ourStack[i][j] << ' ';
	}*/ 
	//Рудимент, выводящий итоговый вид разбора регулярного выражения. Использовался при тестировании

	return(0);

}
