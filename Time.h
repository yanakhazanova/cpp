#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

// �������� ����������������� ����� Time
class Time
{
private:
	int min;
	int sec;
public:
	Time() : min(0), sec(0) {}  // ����������� (��� ����������)
	Time(int m, int s) : min(m), sec(s)  // ����������� (��� ���������)
	{
		if (sec > 59)  // ������� �� ����� ��������� �������� ������ 59
		{
			min = min + (sec / 60);  // ����������� ������� � ������ � �������
			sec = sec % 60;
		}
	}

	// ������������� ������� ���������� ��������� ������
	friend ostream &operator<<(ostream &os, const Time &t) { os << t.min << ":" << t.sec; return os; }  // ������� ����� :

	// ������������� ������� ���������� ��������� �����
	friend istream &operator>>(istream &is, Time &t)
	{
		cout << endl;
		cout << "Minutes: ";
		is >> t.min;  // ��������� �������� �����
		cout << "Seconds: ";
		is >> t.sec;  // ��������� �������� ������
		if (t.sec > 59)  // ����������� ������� � ������
		{
			t.min = t.min + (t.sec / 60);
			t.sec = t.sec % 60;
		}
		return is;
	}

	// ���������� ��������� ������������
	const Time &operator=(const Time &t) { min = t.min; sec = t.sec; return *this; }  // �������� ������������ �������� ��� ����� � ������

	// ���������� ��������� ���������
	bool operator==(const Time &t) const { return (min == t.min && sec == t.sec); }  // �������� ���������� �������� ��� ����� � ������

	// ���������� ��������� �����������
	bool operator!=(const Time &t) const { return !(min == t.min && sec == t.sec); }  // �������� ���������� �������� ��� ����� � ������ // ��������!!!

	// ���������� ��������� ���������
	bool operator>(const Time &t) const
	{
		if (min > t.min) { return true; }  // ������� ���������� ������
		else if (min == t.min)  // ���� ������ �����, �� ���������� �������
			if (sec > t.sec) { return true; }
		return false;
	}

	// ���������� ��������� ���������
	bool operator<(const Time &t) const
	{
		if (min < t.min) { return true; }  // ������� ���������� ������
		else if (min == t.min)  // ������� ���������� �������
			if (sec < t.sec) { return true; }
		return false;
	}

};
