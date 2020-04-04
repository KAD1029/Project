#include <iostream>
#include "Tokenizer.h"
#include <vector>
#include <fstream>
#include <iomanip>


using namespace std;

ostream& operator<<(ostream& out, vector<string> a)
{
	for (const string s : a)
	{
		out << s << endl;
	}
	return out;
}

void print(vector<Token> a, vector<string> s)
{
	int i = 0;
	int j = 0;
	while(i < s.size())
	{
		cout << "------------------------------------------------------------" << endl;
		cout << s[i] << endl;
		i++;

		int k = 0;
		while (i < s.size() &&(s[i] == "" || s[i][s[i].size() - 1] == ','))
		{
			if (s[i] == "")
				k++;
			cout << s[i] << endl;
			i++;
		}
		cout << "------------------------------------------------------------" << endl;

		while (j < a.size())
		{
			if (a[j].name == "EndLine")
			{
				if (k == 0)
					break;
				k--;
			}
			cout << setw(60) << ' ' << setw(10) << a[j].name << " : " << a[j].type << endl;
			j++;
		}
		cout << setw(60) << ' ' << setw(10) << "EndLine" << " : " << EOL << endl;
		j++;
	}

}


int main()
{
	vector<string> program;
	string tmp;

	vector<Token> result;


	ifstream fin("..\\..\\Tests.txt");

	while (getline(fin, tmp))
	{
		program.push_back(tmp);
	}

	cout << program << endl << endl << endl;

	result = Tokenizer().Tokenize(program);

	print(result, program);

	return 0;
}