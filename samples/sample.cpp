#include <string>
#include <vector>
#include "Tokenizer.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, vector<string> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		out << a[i] << endl;
	}
	return out;
}


int main()
{


	vector<string> v1 = { "if a == 10:", "	if b == 4:", "		print(a)", "print(b)"};

	cout << v1;

	vector<Token> v;

	Tokenizer a;

	v = a.Tokenize(v1);

	for (int i = 0; i < v.size(); i++)
	{
		cout << endl << i << " : \"" << v[i].name << "\" " << v[i].type;
	}

	return 0;
}