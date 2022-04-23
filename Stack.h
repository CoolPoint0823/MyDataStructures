#pragma once
#ifndef STACK_
#define STACK_
#include"..\Vector\Vector.h"
template<class T>
class Stack :public Vector<T>
{
public:
	void push(T const& e) { this->insert(this->get_size(), e); }
	T pop() { return this->remove(this->get_size() - 1); }
	T& top() { return(*this)[this->get_size() - 1]; }
};
#endif