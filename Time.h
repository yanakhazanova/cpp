#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

// Описание пользовательского класа Time
class Time
{
private:
	int min;
	int sec;
public:
	Time() : min(0), sec(0) {}  // Конструктор (без аргументов)
	Time(int m, int s) : min(m), sec(s)  // Конструктор (два аргумента)
	{
		if (sec > 59)  // Секунды не могут принимать значения больше 59
		{
			min = min + (sec / 60);  // Преобразуем секунды в минуты и секунды
			sec = sec % 60;
		}
	}

	// Дружественная функция перегрузки оператора вывода
	friend ostream &operator<<(ostream &os, const Time &t) { os << t.min << ":" << t.sec; return os; }  // Выводим через :

	// Дружественная функция перегрузки оператора ввода
	friend istream &operator>>(istream &is, Time &t)
	{
		cout << endl;
		cout << "Minutes: ";
		is >> t.min;  // Считываем значения минут
		cout << "Seconds: ";
		is >> t.sec;  // Считываем значения секунд
		if (t.sec > 59)  // Преобразуем секунды и минуты
		{
			t.min = t.min + (t.sec / 60);
			t.sec = t.sec % 60;
		}
		return is;
	}

	// Перегрузка оператора присваивания
	const Time &operator=(const Time &t) { min = t.min; sec = t.sec; return *this; }  // Почленно приравниваем значения для минут и секунд

	// Перегрузка оператора равенства
	bool operator==(const Time &t) const { return (min == t.min && sec == t.sec); }  // Почленно сравниваем значения для минут и секунд

	// Перегрузка оператора неравенства
	bool operator!=(const Time &t) const { return !(min == t.min && sec == t.sec); }  // Почленно сравниваем значения для минут и секунд // дописали!!!

	// Перегрузка оператора сравнения
	bool operator>(const Time &t) const
	{
		if (min > t.min) { return true; }  // Сначала сравниваем минуты
		else if (min == t.min)  // Если минуты равны, то сравниваем секунды
			if (sec > t.sec) { return true; }
		return false;
	}

	// Перегрузка оператора сравнения
	bool operator<(const Time &t) const
	{
		if (min < t.min) { return true; }  // Сначала сравниваем минуты
		else if (min == t.min)  // Сначала сравниваем секунды
			if (sec < t.sec) { return true; }
		return false;
	}

};
