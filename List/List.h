#pragma once
#ifndef LIST_
#define LIST_
#define NULL 0
#include"ListNode.h"
#include<cstdlib>
#include"..\BaseAPI\BaseAPI.h"
template<class T>
class List
{
private:
	int size;
	ListNode<T>* header, * trailer;
protected:
	void init();
	int clear();//清除所有节点
	void copyNodes(ListNode<T>* p, int n);//复制列表中从p起的n项
	void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*&, int);//归并
	void mergeSort(ListNode<T>*&, int);//对从p开始的n个节点进行归并排序
	void selectionSort(ListNode<T>*, int);//对从p开始的n个节点进行选择排序
	void insertionSort(ListNode<T>*, int);//对从p开始的n个节点进行插入排序
public:
	List() { init(); }
	List(List<T> const& l) { copyNodes(l.first(), l.size); } //整体复制列表l
	List(List<T> const& l, int r, int n) { copyNodes(l[r], n); }//复制列表l中第r项起的N项
	List(ListNode<T>* p, int n) { copyNodes(p, n); }//复制列表中位置p起的n项
	~List() { clear(); delete header; delete trailer; }
	//只读访问接口
	int getsize()const { return size; }
	bool empty()const { return !size; }
	T& operator[](int r)const;
	ListNode<T>* first() { return header->succ; }
	ListNode<T>* last() { return trailer->pred; }
	bool valid(ListNode<T>* p) { return p && (trailer != p) && (header != p); }
	ListNode<T>* search_unordered(T const& e)const { return search_unordered(e, size, trailer); }
	ListNode<T>* search_unordered(T const& e, int n, ListNode<T>* p)const;
	ListNode<T>* search(T const& e)const { return search(e, size, trailer); }
	ListNode<T>* search(T const& e, int n, ListNode<T>* p)const;
	ListNode<T>* selectMax(ListNode<T>* p, int n); //在p及其n-1个后继中选出最大者
	ListNode<T>* selectMax() { return selectMax(header->succ, size); } //整体最大者
 // 可写访问接口
	ListNode<T>* insertAsFirst(T const& e); //将e当作首节点插入
	ListNode<T>* insertAsLast(T const& e); //将e当作末节点插入
	ListNode<T>* insertA(ListNode<T>* p, T const& e); //将e当作p的后继插入
	ListNode<T>* insertB(T const& e, ListNode<T>* p); //将e当作p的前驱插入
	T remove(ListNode<T>* p); //删除合法位置p处的节点,返回被删除节点
	void merge(List<T>& L) { merge(header->succ, size, L, L.header->succ, L.size); } //全列表归并
	void sort(ListNode<T>* p, int n); //列表区间排序
	void sort() { sort(first(), size); } //列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置
 // 遍历
	void traverse(void (*) (T&)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
	template <typename VST> //操作器
	void traverse(VST&); //遍历，依次实施visit操作（函数对象，可全局性修改）
}; //List
template<class T>
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = nullptr;
	trailer->succ = nullptr;
	trailer->pred = header;
	size = 0;
}
template<class T>
int List<T>::clear()
{
	int oldsize = size;
	while (size)
		remove(header->succ);
	return oldsize;
}
template<class T>
void List<T>::copyNodes(ListNode<T>* p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}
template<class T>
ListNode<T>* List<T>::insertAsFirst(T const& e)
{
	size++;
	return header->insertAsSucc(e);
}
template<class T>
ListNode<T>* List<T>::insertAsLast(T const& e)
{
	size++;
	return trailer->insertAsPred(e);
}
template<class T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, T const& e)
{
	size++;
	return p->insertAsSucc(e);
}
template<class T>
ListNode<T>* List<T>::insertB(T const& e, ListNode<T>* p)
{
	size++;
	return p->insertAsPred(e);
}
template<class T>
T List<T>::remove(ListNode<T>* p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	size--;
	return e;
}
template<class T>
T& List<T>::operator[](int r)const
{
	ListNode<T>* p = first();
	while (r--)
	{
		p = p->succ;
	}
	return p->data;
}
template<class T>
ListNode<T>* List<T>::search_unordered(T const& e, int n, ListNode<T>* p)const
{
	while (n--)
	{
		if (p->data == e)
			return p;
		p = p->pred;
	}
	return NULL;
}
template<class T>
int List<T>::deduplicate()
{
	if (size < 2)return 0;
	ListNode<T>* p = header;
	int rank = 0;
	int oldsize = size;
	while (p != trailer)
	{
		ListNode<T>* q = search_unordered(p->data, rank, p);
		if (q)
			remove(q);
		p = p->succ;
		rank++;
	}
	return oldsize - size;
}
template<class T>
int List<T>::uniquify()
{
	if (size < 2)return 0;
	int oldsize = size;
	ListNode<T>* p = first();
	ListNode<T>* q = p->succ;
	while (trailer != q)
	{
		if (p->data != q->data) p = q;
		else
			remove(q);
		q = p->succ;
	}
	return oldsize - size;
}
template<class T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p)const
{
	while (0 <= n--)
		if (((p = p->pred)->data) <= e)break;
	return p;
}
template<class T>
ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
{
	T elem = p->data;
	for (int i = 0; i < n; i++, p = p->succ)
		if (elem < p->data)
			elem = p->data;
	return p;
}
template<class T>
void List<T>::insertionSort(ListNode<T>* p, int n)
{
	for (int i = 0; i < n; i++)
	{
		insertA(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}
template<class T>
void List<T>::selectionSort(ListNode<T>* p, int n)
{
	ListNode<T>* head = p->pred, * tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ;
	while (1 < n)
	{
		ListNode<T>* max = selectMax(head->succ, n);
		insertB(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}
template<class T>
void List<T>::sort(ListNode<T>* p, int n)
{
	switch (rand() % 1)
	{
	case 0:insertionSort(p, n); break;
	case 1:selectionSort(p, n); break;
	}
}
#endif