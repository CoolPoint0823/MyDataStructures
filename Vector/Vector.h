#pragma once
#ifndef VECTOR_
#define VECTOR_
#include<cstdlib>
#include"..\BaseAPI\BaseAPI.h"
template<class T>
class Vector
{
protected:
	int capacity;
	int size;
	T* elem;
	void copyFrom(T* const targ, int lo, int hi);
	void expand();
	void shrink();
	bool bubble(int lo, int hi);
	void bubbleSort(int lo, int hi);
	int max(int lo, int hi);
	
	void selectionSort(int lo, int hi);
	void merge(int lo, int mi, int hi);
	void mergeSort(int lo, int hi);
	int partition(int lo, int hi);
	void heapSort(int lo, int hi);
public:
	Vector(int c = 3, int s = 0, T v = 0)
	{
		elem = new T[capacity = c];
		for (size = 0; size < s; elem[size++] = v);
	}
	Vector(T const* targ, int n) { copyFrom(targ, 0, n); }
	Vector(T const* targ, int lo, int hi) { copyFrom(targ, lo, hi); }
	Vector(Vector<T> const& V) { copyFrom(V.elem, 0, V.size); }
	Vector(Vector<T> const& V, int lo, int hi) { copyFrom(V.elem, lo, hi); }
	~Vector() { delete[]elem; }
	//只读访问接口
	int min(int lo, int hi);
	int get_size() { return size; }
	int get_capacity() { return capacity; }
	int empty() { return !size; }
	bool disordered()const;
	int search_unordered(T const& e)const { return search_unordered(e, 0, size); }
	int search_unordered(T const& e, int lo, int hi)const;//查找[lo,hi)中等于e的元素，返回查找值的下标，未找到则返回-1
	int search(T const& e)const { return (0 >= size) ? -1 : search(e, 0, size); }
	int search(T const& e, int lo, int hi)const;
	//可写访问接口
	T& operator[](int r) { return elem[r]; }
	Vector<T>& operator=(Vector<T> v)
	{
		if (elem)
			delete[] elem;
		copyFrom(v, 0, v.size);
		return *this;
	}
	T remove(int r);
	int remove(int lo, int hi);
	int insert(int r, T const& e);
	int insert(T const& e) { return insert(size, e); }
	void sort(int lo, int hi);
	void sort() { sort(0, size); }
	void unsort(int lo, int hi);
	void unsort() { unsort(0, size); }
	int deduplicate_unordered();
	int deduplicate();
};
//Protected function
template<typename T>
void Vector<T>::copyFrom(T* const targ, int lo, int hi)
{
	elem = new T[2 * (hi - lo)]; size = 0;
	for (lo; lo < hi; lo++)
		elem[size++] = targ[lo];
}
template<class T>
void Vector<T>::expand()
{
	if (size < capacity)return;
	T* oldElem = elem;
	elem = new T[capacity <<= 1];
	for (int i = 0; i < size; i++)
		elem[i] = oldElem[i];
	delete[]oldElem;
}
template<class T>
void Vector<T>::shrink()
{
	if (size << 2 > capacity)return;
	T* oldElem = elem;
	elem = new T[capacity >>= 1];
	for (int i = 0; i < size; i++)
		elem[i] = oldElem[i];
	delete[]oldElem;
}
template<class T>
bool Vector<T>::bubble(int lo, int hi)
{
	bool sorted = true;
	while (++lo < hi)
	{
		if (elem[lo-1] > elem[lo])
		{
			sorted = false;
			swap(elem[lo], elem[lo + 1]);
		}
	}
	return sorted;
}
template<class T>
void Vector<T>::bubbleSort(int lo, int hi)
{
	while (!bubble(lo, hi--));
}
template<class T>
int Vector<T>::max(int lo, int hi)
{
	T tmp = elem[lo];
	int rank = lo;
	while (++lo< hi)
	{
		if (tmp < elem[lo])
		{
			tmp = elem[lo];
			rank = lo;
		}
	}
	return rank;
}
template<class T>
int Vector<T>::min(int lo, int hi)
{
	T tmp = elem[lo];
	int rank = lo;
	while (++lo < hi)
	{
		if (tmp > elem[lo])
		{
			tmp = elem[lo];
			rank = lo;
		}
	}
	return rank;
}
template<class T>
void Vector<T>::selectionSort(int lo, int hi)
{
	while (lo < hi)
	{
		swap(elem[lo], elem[min(lo, hi)]);
		lo++;
	}
}
template<class T>
void Vector<T>::merge(int lo, int mi, int hi)
{
	T* A = elem + lo;
	int lb = mi - lo; 
	T* B = new T[lb];
	for (int i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi;
	T* C = elem + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))	A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] < B[j])))	A[i++] = C[k++];
	}
	delete[]B;

}
template<class T>
void Vector<T>::mergeSort(int lo, int hi)
{
	if (hi - lo < 2)return;
	int mi = (hi + lo) / 2;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}
//Public Functions
template<class T>
bool Vector<T>::disordered()const
{
	int rank = 0;
	while (rank++ < size)
	{
		if (elem[rank] > elem[rank + 1])
		{
			return false;
		}
	}
	return true;
}
template<class T>
int Vector<T>::search_unordered(T const& e, int lo, int hi)const
{
	for (lo; lo < hi; lo++)
	{
		if (elem[lo] == e)
			return lo;
	}
	return -1;
}
template<class T>
int Vector<T>::search(T const& e, int lo, int hi)const
{
	while (lo < hi)
	{
		int mi = (hi + lo) >> 1;
		if (elem[mi] < e)
			lo = mi + 1;
		else
			hi = mi;
	}
	if (elem[lo] == e)
		return lo;
	else return -1;
	
}
template<class T>
T Vector<T>::remove(int r)
{
	if (r >= size)
		return -1;
	T temp = elem[r];
	remove(r, r + 1);
	return temp;
}
template<class T>
int Vector<T>::remove(int lo, int hi)
{
	if (lo == hi)return 0;
	while (hi < size)
	{
		elem[lo++] = elem[hi++];
	}
	size = lo;
	shrink();
	return hi - lo;
}
template<class T>
int Vector<T>::insert(int r, T const& e)
{
	expand();
	for (int i = size; i > r; i--)
		elem[i] = elem[i - 1];
	elem[r] = e;
	size++;
	return r;
}
template<class T>
void Vector<T>::sort(int lo, int hi)
{
	selectionSort(lo, hi);
}
template<class T>
void Vector<T>::unsort(int lo, int hi)
{
	T* v = elem + lo;
	for (int i = hi - lo; i > 0; i--)
		swap(v[i - 1], v[rand() % i]);
}
template<class T>
int Vector<T>::deduplicate_unordered()
{
	int oldsize = size;
	int i = 1;
	while (i<size)
	{
		(search_unordered(elem[i], 0, i) < 0) ? i++ : remove(i);
	}
	return oldsize - size;
}
template<class T>
int Vector<T>::deduplicate()
{
	int i = 0, j = 0;
	while (++j < size)
		if (elem[i] != elem[j])
			elem[++i] = elem[j];
	size = ++i;
	shrink();
	return j - i;
}
#endif