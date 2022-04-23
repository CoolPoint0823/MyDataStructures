#include"Stack.h"
#include<iostream>
using namespace std;

int main()
{
	Stack<int> s;
	for (int i = 5; i > 0; i--)
	{
		s.push(i);
		cout << "Inserting element: " << i << endl;
		cout << "Size: " << s.get_size() << endl;
	}
	s.sort();
	s.remove(2);
	for (int i = 0; i < 5; i++)
	{
		cout << s[i] << endl;
	}
	cout << "Size: " << s.get_size() << endl;
}