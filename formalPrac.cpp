#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

string ParseStupid(string regularExp)
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
{
	vector<vector<string>> ourStack;
	for (int i = 0; i < regularExp.length(); i++)
	{
		if ((regularExp[i] >= 'a') && (regularExp[i] <= 'z'))
		{
			vector<string> ti;
			string a = "0";
			a[0] = regularExp[i];
			ti.push_back(a);
			ourStack.push_back(ti);
		}

		if ((regularExp[i] == '.') && ((regularExp[i - 1] > 'a') && (regularExp[i - 1] < 'z')))
		{
			for (int j = 0; j < ourStack[ourStack.size()-1].size(); j++)
				ourStack[ourStack.size() - 2][j] += ourStack[ourStack.size() - 1][j];
			ourStack.pop_back();
		}
		if (regularExp[i] == '+')
		{
			ourStack[ourStack.size() - 2].push_back(ourStack[ourStack.size() - 1][0]);
			ourStack.pop_back();
		}
		if (regularExp[i] == '*')
		{
			ourStack[ourStack.size() - 1].push_back("YOUCANSKIPIT");
		}
		
	}
	return(ourStack);
}

int JustDoIt(vector<vector<string>>& ourStack, string ourWord, int stackPos, int wordPos)
{
	if ((stackPos > ourStack.size()-1) || (wordPos > ourWord.length() - 1))
		return(0);
	if ((stackPos == ourStack.size()-1) && (wordPos == ourWord.length() - 1))
		return(1);
	
	int ifAns = 0;
	int ifstar = 0;
	if (ourStack[stackPos][ourStack[stackPos].size()-1] == "YOUCANSKIPIT")
		ifstar = 1;
	if (ifstar == 1)
		ifAns += JustDoIt(ourStack, ourWord, stackPos+1, wordPos);
	for (int i = 0; i < ourStack[stackPos].size()-1; i++)
	{
		
		int co = 0;
		for (int j = 0; j < ourStack[stackPos][i].length();j++)
		if (ourStack[stackPos][i][j] != ourWord[wordPos + j])
			co = 1;
		if (co == 0)
		{
			ifAns+=JustDoIt(ourStack, ourWord, stackPos + 1, wordPos + ourStack[stackPos][i].length());
			if (ifstar==1)
				ifAns += JustDoIt(ourStack, ourWord, stackPos, wordPos + ourStack[stackPos][i].length());
		}
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
	return(0);

}
