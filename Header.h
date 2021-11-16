#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "Time.h"


using namespace std;


// ���������� ������ SetIterator
template <class T> class SetIterator;



// �������� ������-���������� 
template <class T>
class Set
{
private:
	T *ar;   // ���������
	int size;  // ������ ���������
public:
	Set();										// �����������
	void insert(const T & item);				// ���������� �������� �� ���������
	void erase(const T & item);				    // �������� �������� �� ��������� 
	int getsize() const;						// ����������� ������� ���������
	bool isinset(const T & item);				// �������� �������������� ���������
	bool isempty();								// �������� �� �������
	T getelem(int i) const;						// ���������� �������, ��������������� ������� �������
	virtual Set & operator=(Set & s);			// �������� ������������
	bool operator!=(const Set<T> & s) const;	// �������� ����������� ��������
	~Set();										// ����������

	SetIterator<T> createIterator() const { return SetIterator<T>(this); }	// ����� �������� ���������

	// ������ ������ ����������� �� �������; � ������ � ���������, ������ ��� ����������� ������ ���
	// � ������ ����������������� � ����.
	//SetIterator<T> Begin() const { return SetIterator<T>(this); }
	//SetIterator<T> End() const { return SetIterator<T>(this, 1); }	// ������������ ����������� � ����� �����������, ���������� ��������� ��� ���������� ����� ������

	// ���������� ��������� ������
	friend ostream &operator<<(ostream &os, Set<T> &s)
	{
		if (!s.isempty())  // �������� �� ������� ���������
		{
			cout << "Set: ";
			for (int i = 0; i < s.size; i++) { cout << s.ar[i] << " "; }  // �� ������� �������� ��� �������� ����� ������
			cout << endl;
		}
		else { cout << "Set is empty" << endl; }  // ���� ��������� �����
		return os;
	}

	// ���������� ��������� �����
	friend istream &operator>>(istream &is, Set<T> &s)
	{
		int n;  // ����������, ���������� �� ���������� ���������
		T item;  // ������� ���� �
		cout << "Enter how many elements you want to add: ";
		cin >> n;
		for (int i = 0; i < n; i++)  // ������ �������� ���������� ���������
		{
			cout << "Enter element: ";
			cin >> item;  // �������� �� ���� �������

			if (cin.fail())  // �������� ���������� ����
			{
				cout << "Inappropriate type of element, it will be skipped" << endl;
				cin.clear();  // ������� �������
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else { s.insert(item);  cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }  // ��������� ��������� �������
		}
		return is;
	}
};

// �����������
template <class T>
Set<T>::Set() { size = 0; cout << "Constructor called successfully" << endl; }

// ���������� ��������� �����������
template<class T>
bool Set<T>::operator!=(const Set<T> & s) const {
	if (s.size != size) { return true; }
	for (int i = 0; i < size; i++)  // ����������� ���������� 
	{
		if (s.ar[i] != ar[i]) { return true; }
	}
	return false;
}

// �������� �� ������� ���������
template <class T>
bool Set<T>::isempty() { return size == 0; }

// ����������� �������� �� �������
template <class T>
T Set<T>::getelem(int i) const { return ar[i]; }

// ��������� ������� ���������
template <class T>
int Set<T>::getsize() const { return size; }

// ��������, ��������� �� ������� � ���������
template <class T>
bool Set<T>::isinset(const T & item)
{
	if (!Set::isempty())  // �������� ��������� �� �������
	{
		for (int i = 0; i < size; i++)  // ����������� ���������� ��� ������� � ���������� �� ���������
		{
			if (item == ar[i]) { return 1; }
		}
	}
	return 0;
}

// ������� �������� � ���������
template <class T>
void Set<T>::insert(const T & item)
{
	if (!Set::isempty())  // �������� ��������� �� �������
	{
		if (Set::isinset(item)) { cout << "Element " << item << " is in set and "; }  // ���� ������� ��� �� ���������, ������ �� ������
		else
		{
			size++; // ��������� ������ ���������
			T *ar1 = new T[size]; // ������� ����� ������ �������� �������

			// ���� ������ �������
			int pos = size - 1;  // �� ��������� ������� - ��������� �����
			if (item < ar[0]) { pos = 0; }  // ���� ������� ������ �������, �� �������� ��� �� ������ �������
			else  // ���� ������� �� ������ �������
			{
				for (int i = 0; i < size - 1; i++)  // ���� ���������� �������
				{
					if ((item > ar[i]) && !(item > ar[i + 1])) { ar1[i] = ar[i]; pos = i + 1; break; }  // ���������� �������� � ����� ������, ���� �� ������ ������ �������
					else { ar1[i] = ar[i]; }
				}
			}

			// ��������� ������ ar1 ������ ��������� � �����������
			ar1[pos] = item;
			for (int j = pos + 1; j < size; j++) { ar1[j] = ar[j - 1]; }

			delete[] ar;  // ������� ������ ��-��� ��������� �������
			ar = new T[size];  // �������� ������ ��� ������
			for (int i = 0; i < size; i++) { ar[i] = ar1[i]; }  // ����������� ���������� �������� ������ ������� � ��������
			delete[] ar1;  // ������� ������ ��-��� ������ �������
		}
	}
	else  // ���� ��������� �����: ������ ������� �� ������ �����
	{
		size++;  // ����������� ������ �� 1
		ar = new T[size];  // �������� ������
		ar[0] = item;
	}
	cout << "Element " << item << " is inserted" << endl;
}

// �������� �������� �� ���������
template <class T>
void Set<T>::erase(const T & item)
{
	if (!Set::isinset(item)) { cout << "Element " << item << " is absent in this set" << endl; }  // ���� ������� �� ������ �� ���������
	else  // ���� ������� ������ �� ���������
	{
		T *ar1 = new T[size - 1];  // �������� ������ ��� ����� ������
		int pos = 0;
		for (int i = 0; i < size; i++)  // ���� ������� ��������� ��������
		{
			if (item == ar[i]) { pos = i; break; }
			else { ar1[i] = ar[i]; }  // ���� �� ����� ������ �������, ���������� �������� � ����� ������
		}
		for (int j = pos; j < size - 1; j++) { ar1[j] = ar[j + 1]; }  // ���������� ������� �� ��������� ������� � ���������� ��������� �������� � ����� ������

		delete[] ar;  // ������� ������ ��-��� ��������� �������
		size--;  // ��������� ������
		ar = new T[size];  // �������� ������ ��� ������
		for (int i = 0; i < size; i++) { ar[i] = ar1[i]; }  // ������������ �������� �������� �����������
		delete[] ar1;  // ������� ������

		cout << "Element " << item << " is erased" << endl;
	}
}

// ����������
template <class T>
Set<T>::~Set()
{
	if (size != 0) { delete[] ar; cout << "Memory cleared" << endl; }  // ���� ��� ��������� ���� �������� ������, ������� ��
	size = 0;
}

// ����������� �������� ������������
template <class T>
Set<T> & Set<T>::operator=(Set & s)
{
	size = s.getsize();  // �������� ������
	ar = new T[size];
	for (int i = 0; i < size; i++) { ar[i] = s.ar[i]; }  // ����������� ����������� �������� ���������
	return *this;
}



// ����� ��������
template<class T>
class SetIterator {
private:
	const Set<T> *_set;    // ��������� Set
	int _current;		   // ������, ����������� ������� ������� � ���������
public:

	// �����������, ������� ������� �� ��������� = 0:
	SetIterator(const Set<T>* aSet) : _set(aSet), _current(0) {};

	// ����������� (����� �������� ����� ��������� ����� �� ����� ���������)
	//SetIterator(const Set<T>* aSet, int flag) : _set(aSet), _current(_set->getsize()) {};    

	// ���������� �������� �� ������� �������:
	void Begin() { _current = 0; }

	// ���������� �������� �� ��������� �������:
	void Next() { _current++; }	

	// ���������� �������� �� ����� ���������:
	void End() { _current = _set->getsize()-1; }	

	// ��������, ��������� �� �������� ������ ���������:
	bool IsDone() const { return (_current >= _set->getsize() )||(_current < 0) ; }	

	// ���������� �������, ��������������� ������� ������� ��������� (�� ��, ��� � ��������������� ���������):
	T Current() {	
		if (IsDone()) { 
			cout << "Iterator is out of bounds. Current position is " << _current << ". \nIt will return the nearest value." << endl;	// � ������ �������, �������� ������� ������� ��������� �� ��������� ������� ������� (������ ��� ����� ���������)
			if (_current < 0) { _current = 0; }
			else { _current = _set->getsize() - 1; ; }
		}
		return _set->getelem(_current);
	}

	SetIterator<T>& operator++();	// ���������� ���������
	SetIterator<T>& operator--();	// ���������� ���������
	SetIterator<T> operator++(int);	// ����������� ���������
	SetIterator<T> operator--(int);	// ����������� ���������

	T operator*();									// ��������������� ���������
	bool operator!=(const SetIterator<T> &i) const;	// �������� �����������
	bool operator==(const SetIterator<T> &i) const;	// �������� ���������
};

// ���������� ���������
template <class T>
SetIterator<T>& SetIterator<T>::operator++() {
	_current++;
	return *this;
};

// ���������� ���������
template <class T>
SetIterator<T>& SetIterator<T>::operator--() {
	_current--;
	return *this;
}

// ����������� ���������
template <class T>
SetIterator<T> SetIterator<T>::operator++(int) {
	SetIterator<T> temp(_set); // ������� ��������� ������ ������ SetIterator
	++(*this); // ���������� ���, ��� ���������� ��������� ��� �������
	return temp;
}

// ����������� ���������
template <class T>
SetIterator<T> SetIterator<T>::operator--(int) {
	SetIterator<T> temp(_set);
	--(*this); // ���������� ���, ��� ���������� ��������� ��� �������
	return temp;
}

// ��������������� ���������
template <class T>
T SetIterator<T>::operator*() {
	return this->Current();
}

// �������� �����������
template <class T>
bool SetIterator<T>::operator!=(const SetIterator<T> &i) const {
	if (i._current != _current) { return true; }
	if (*i._set != *_set) { return true; }
	return false;
}

// �������� ���������
template <class T>
bool SetIterator<T>::operator==(const SetIterator<T> &i) const {
	return !(i != *this);
}