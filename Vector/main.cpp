#include"Vector.h"
#include<iostream>
using std::cout;
using std::endl;

int main()
{
	Vector<int> v = Vector<int>(10);
	for (int i = 10; i >0 ; i--)
	{
		v.insert(i);
	}
	cout << "Size: " << v.get_size() << endl;
	v.sort();
	
	for (int i = 0; i < 10; i++)
	{
		cout << v[i] << endl;
	}
	cout << v[v.min(0, v.get_size())];
}