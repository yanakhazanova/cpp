#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "Time.h"


using namespace std;


// Объявление класса SetIterator
template <class T> class SetIterator;



// Описание класса-контейнера 
template <class T>
class Set
{
private:
	T *ar;   // Указатель
	int size;  // Размер множества
public:
	Set();										// Конструктор
	void insert(const T & item);				// Добавление элемента во множество
	void erase(const T & item);				    // Удаление элемента из множества 
	int getsize() const;						// Определение размера множества
	bool isinset(const T & item);				// Проверка принадлежности множеству
	bool isempty();								// Проверка на пустоту
	T getelem(int i) const;						// Возвращает элемент, соответствующий текущей позиции
	virtual Set & operator=(Set & s);			// Операция присваивания
	bool operator!=(const Set<T> & s) const;	// Оператор неравенства множеств
	~Set();										// Деструктор

	SetIterator<T> createIterator() const { return SetIterator<T>(this); }	// Метод создания итератора

	// Данные методы требовались по заданию; в отчете я объяснила, почему они реализованы именно так
	// и почему закомментированны в коде.
	//SetIterator<T> Begin() const { return SetIterator<T>(this); }
	//SetIterator<T> End() const { return SetIterator<T>(this, 1); }	// Используется конструктор с двумя параметрами, специально созданный для реализации этого метода

	// Перегрузка оператора вывода
	friend ostream &operator<<(ostream &os, Set<T> &s)
	{
		if (!s.isempty())  // Проверка на пустоту множества
		{
			cout << "Set: ";
			for (int i = 0; i < s.size; i++) { cout << s.ar[i] << " "; }  // По очереди печатаем все элементы через пробел
			cout << endl;
		}
		else { cout << "Set is empty" << endl; }  // Если множество пусто
		return os;
	}

	// Перегрузка оператора ввода
	friend istream &operator>>(istream &is, Set<T> &s)
	{
		int n;  // Переменная, отвечающая за количество элементов
		T item;  // Элемент типа Т
		cout << "Enter how many elements you want to add: ";
		cin >> n;
		for (int i = 0; i < n; i++)  // Вводим заданное количество элементов
		{
			cout << "Enter element: ";
			cin >> item;  // Получаем на вход элемент

			if (cin.fail())  // Проверка введенного типа
			{
				cout << "Inappropriate type of element, it will be skipped" << endl;
				cin.clear();  // Очищаем консоль
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else { s.insert(item);  cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }  // Добавляем введенный элемент
		}
		return is;
	}
};

// Конструктор
template <class T>
Set<T>::Set() { size = 0; cout << "Constructor called successfully" << endl; }

// Перегрузка оператора неравенства
template<class T>
bool Set<T>::operator!=(const Set<T> & s) const {
	if (s.size != size) { return true; }
	for (int i = 0; i < size; i++)  // Поэлементно сравниваем 
	{
		if (s.ar[i] != ar[i]) { return true; }
	}
	return false;
}

// Проверка на пустоту множетсва
template <class T>
bool Set<T>::isempty() { return size == 0; }

// Возвращение элемента по индексу
template <class T>
T Set<T>::getelem(int i) const { return ar[i]; }

// Получение размера множества
template <class T>
int Set<T>::getsize() const { return size; }

// Проверка, находится ли элемент в множестве
template <class T>
bool Set<T>::isinset(const T & item)
{
	if (!Set::isempty())  // Проверка множества на пустоту
	{
		for (int i = 0; i < size; i++)  // Поэлементно сравниваем наш элемент с остальными из множества
		{
			if (item == ar[i]) { return 1; }
		}
	}
	return 0;
}

// Вставка элемента в множество
template <class T>
void Set<T>::insert(const T & item)
{
	if (!Set::isempty())  // Проверка множества на пустоту
	{
		if (Set::isinset(item)) { cout << "Element " << item << " is in set and "; }  // Если элемент уже во множестве, ничего не меняем
		else
		{
			size++; // Увеличили размер множества
			T *ar1 = new T[size]; // Создали новый массив большего размера

			// Ищем нужную позицию
			int pos = size - 1;  // По умолчанию позиция - последнее место
			if (item < ar[0]) { pos = 0; }  // Если элемент меньше первого, то поставим его на первую позицию
			else  // Если элемент не меньше первого
			{
				for (int i = 0; i < size - 1; i++)  // Ищем подходящую позицию
				{
					if ((item > ar[i]) && !(item > ar[i + 1])) { ar1[i] = ar[i]; pos = i + 1; break; }  // Записываем элементы в новый массив, пока не найдем нужную позицию
					else { ar1[i] = ar[i]; }
				}
			}

			// Заполняем массив ar1 данным элементом и оставшимися
			ar1[pos] = item;
			for (int j = pos + 1; j < size; j++) { ar1[j] = ar[j - 1]; }

			delete[] ar;  // Очищаем память из-под исходного массива
			ar = new T[size];  // Выделяем память под массив
			for (int i = 0; i < size; i++) { ar[i] = ar1[i]; }  // Поэлементно записываем элементы нового массива в исходный
			delete[] ar1;  // Очищаем память из-род нового массива
		}
	}
	else  // Если множество пусто: ставим элемент на первое место
	{
		size++;  // Увеличиваем размер на 1
		ar = new T[size];  // Выделяем память
		ar[0] = item;
	}
	cout << "Element " << item << " is inserted" << endl;
}

// Удаление элемента из множества
template <class T>
void Set<T>::erase(const T & item)
{
	if (!Set::isinset(item)) { cout << "Element " << item << " is absent in this set" << endl; }  // Если элемент не входит во множество
	else  // Если элемент входит во множество
	{
		T *ar1 = new T[size - 1];  // Выделяем память под новый массив
		int pos = 0;
		for (int i = 0; i < size; i++)  // Ищем позицию заданного элемента
		{
			if (item == ar[i]) { pos = i; break; }
			else { ar1[i] = ar[i]; }  // Пока не нашли нужную позицию, записываем элементы в новый массив
		}
		for (int j = pos; j < size - 1; j++) { ar1[j] = ar[j + 1]; }  // Пропускаем элемент на найденной позиции и записываем остальные элементы в новый массив

		delete[] ar;  // Очищаем память из-под исходного массива
		size--;  // Уменьшаем размер
		ar = new T[size];  // Выделяем память под массив
		for (int i = 0; i < size; i++) { ar[i] = ar1[i]; }  // Приравниваем значения массивов поэлементно
		delete[] ar1;  // Очищаем память

		cout << "Element " << item << " is erased" << endl;
	}
}

// Деструктор
template <class T>
Set<T>::~Set()
{
	if (size != 0) { delete[] ar; cout << "Memory cleared" << endl; }  // Если под множество была выделена память, очищаем ее
	size = 0;
}

// Перегружаем оператор присваивания
template <class T>
Set<T> & Set<T>::operator=(Set & s)
{
	size = s.getsize();  // Изменяем размер
	ar = new T[size];
	for (int i = 0; i < size; i++) { ar[i] = s.ar[i]; }  // Поэлементно присваиваем значения элементов
	return *this;
}



// класс Итератор
template<class T>
class SetIterator {
private:
	const Set<T> *_set;    // экземпляр Set
	int _current;		   // индекс, указывающий текущую позицию в множестве
public:

	// Конструктор, текущая позиция по умолчанию = 0:
	SetIterator(const Set<T>* aSet) : _set(aSet), _current(0) {};

	// Конструктор (новый итератор будет указывать сразу на конец множества)
	//SetIterator(const Set<T>* aSet, int flag) : _set(aSet), _current(_set->getsize()) {};    

	// Перемещает итератор на нулевую позицию:
	void Begin() { _current = 0; }

	// Перемещает итератор на следующую позицию:
	void Next() { _current++; }	

	// Перемещает итератор на конец множества:
	void End() { _current = _set->getsize()-1; }	

	// Проверка, находится ли итератор внутри множества:
	bool IsDone() const { return (_current >= _set->getsize() )||(_current < 0) ; }	

	// Возвращает элемент, соответствующий текущей позиции итератора (то же, что и разыменовывание итератора):
	T Current() {	
		if (IsDone()) { 
			cout << "Iterator is out of bounds. Current position is " << _current << ". \nIt will return the nearest value." << endl;	// В случае неудачи, изменяет текущую позицию итератора на ближайшую крайнюю позицию (начало или конец множества)
			if (_current < 0) { _current = 0; }
			else { _current = _set->getsize() - 1; ; }
		}
		return _set->getelem(_current);
	}

	SetIterator<T>& operator++();	// префиксный инкремент
	SetIterator<T>& operator--();	// префиксный декремент
	SetIterator<T> operator++(int);	// постфиксный инкремент
	SetIterator<T> operator--(int);	// постфиксный декремент

	T operator*();									// разыменовывание итератора
	bool operator!=(const SetIterator<T> &i) const;	// оператор неравенства
	bool operator==(const SetIterator<T> &i) const;	// оператор равенства
};

// префиксный инкремент
template <class T>
SetIterator<T>& SetIterator<T>::operator++() {
	_current++;
	return *this;
};

// префиксный декремент
template <class T>
SetIterator<T>& SetIterator<T>::operator--() {
	_current--;
	return *this;
}

// постфиксный инкремент
template <class T>
SetIterator<T> SetIterator<T>::operator++(int) {
	SetIterator<T> temp(_set); // создаем временный объект класса SetIterator
	++(*this); // пользуемся тем, что префиксный инкремент уже написан
	return temp;
}

// постфиксный декремент
template <class T>
SetIterator<T> SetIterator<T>::operator--(int) {
	SetIterator<T> temp(_set);
	--(*this); // пользуемся тем, что префиксный инкремент уже написан
	return temp;
}

// разыменовывание итератора
template <class T>
T SetIterator<T>::operator*() {
	return this->Current();
}

// оператор неравенства
template <class T>
bool SetIterator<T>::operator!=(const SetIterator<T> &i) const {
	if (i._current != _current) { return true; }
	if (*i._set != *_set) { return true; }
	return false;
}

// оператор равенства
template <class T>
bool SetIterator<T>::operator==(const SetIterator<T> &i) const {
	return !(i != *this);
}