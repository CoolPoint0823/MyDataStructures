#pragma once
#ifndef LISTNODE_
#define LISTNODE_
template<class T>
struct ListNode
{
	T data;
	ListNode<T>* pred, * succ;
	ListNode(){}
	ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr)
		:data(e),pred(p),succ(s){}
	ListNode<T>* insertAsPred(T const& e);
	ListNode<T>* insertAsSucc(T const& e);
};
template<class T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e)
{
	ListNode<T>* p = new ListNode<T>(e, this->pred, this);
	pred->succ = p;
	pred = p;
	return p;
}
template<class T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
{
	ListNode<T>* p = new ListNode<T>(e, this, this->succ);
	succ->pred = p;
	succ = p;
	return p;
}
#endif