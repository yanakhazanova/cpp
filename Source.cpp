#include "Header.h"



using namespace std;

int main()
{
	Set<int> pr;
	pr.insert(4);
	pr.insert(7);
	pr.insert(2);
	pr.insert(5);
	pr.insert(7);

	cout << pr;

	// Внешний итератор для множества типа int
	SetIterator<int> iter = pr.createIterator();

	// Выводим на экран элементы множества, используя функции Next() и Current()
	cout << "Set (using Current()):" << endl;
	for (iter.Begin(); !iter.IsDone(); iter.Next()) {
		cout << iter.Current() << " " ; 
	}
	cout << endl;

	// Выводим на экран элементы множества, используя перегруженные операторы: постфиксный инкремент и разыменовывание итератора
	cout << "Set (using operator*):" << endl;
	for (iter.Begin(); !iter.IsDone(); iter++) {
		cout << *iter << " " ;
	}
	cout << endl;

//----------------------------------------------------------------------------------
	cout << endl << endl;

	Set<Time> h;
	Set<Time> t;
	int a, b, c;
	a = 9;
	b = 13;
	c = 21;
	Time time1(a, b);
	Time time2(b, c);
	Time time3(c, a);
	h.insert(time3);
	h.insert(time2);
	h.insert(time1);
	Time time4(b, b);
	Time time5(c, c);
	Time time6(a, a);
	t.insert(time1);
	t.insert(time2);
	t.insert(time3);

	// Внешний итератор для множества типа Time
	SetIterator<Time> i = h.createIterator();
	SetIterator<Time> k = t.createIterator();

	// Выводим на экран элементы множества, используя функции Next() и Current()
	cout << "Set h:" << endl;
	for (i.Begin(); !i.IsDone(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	// Выводим на экран элементы множества, используя функции Next() и Current()
	cout << "Set t:" << endl;
	for (k.Begin(); !k.IsDone(); k++) {
		cout << *k << " ";
	}
	cout << endl;
	
	cout << "i == k return ";
	cout << (i == k) << endl;
	i++;
	--k;
	cout << (i == k) << endl;

	

	system("pause");

	return 0;
}