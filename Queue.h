#pragma once
#ifndef QUEUE_
#define QUEUE_
#include"..\List\List.h"
template<class T>
class Queue :public List<T>
{
public:
	void enqueue(T const& e) { this->insertAsLast(e); }
	T dequeue() { return remove(this->first()); }
	T& front() { return this->first()->data; }
};
#endif // !QUEUE_
