#include <iostream>
#include "array.h"
#include <time.h>
using namespace std;

Darray::Darray(int n=10, int min=0, int max=0, int align=0)//формирование случайного массива+сортировка по убыванию/возрастанию
{
	if (n < 1&&(max<min))
		throw 1;
	Array = new int[n];
		for (int i = 0; i < n; i++)
			Array[i] = min + rand() % (max - min + 1);
		size = n;
		if (align)
			Sort(align);
}
Darray::Darray(int* Mas,int n)//массив в объект
{
		if (!Mas)
			throw 2;
		if (n < 1)
			throw 1;
		Array = new int[n];
		for (int i = 0; i < n;i++)
		Array[i] = Mas[i];
		size = n;
}
Darray::Darray(const Darray& obj)//copy
{
	Array = new int[obj.size];
	size = obj.size;
	for (int i = 0; i < size; i++)
		Array[i] = obj.Array[i];
}
Darray::~Darray()
{
	delete[] Array;
}
void Darray::Sort(int oder = 1) // > 0 возрастание < 0 убывание
{
	int Lt = 0, R = 0, L = size - 1, Rt = size - 1;

	while (L != Lt)
	{
		R = Rt;
		for (int i = Lt; i < R; i++)
		{
			bool ch = false;
			if (oder > 0)
			{
				if (Array[i] > Array[i + 1])
					ch = true;
			}
			else
				if (Array[i] < Array[i + 1])
					ch = true;
			if (ch)
			{
				Array[i] = Array[i] ^ Array[i + 1];
				Array[i + 1] = Array[i] ^ Array[i + 1];
				Array[i] = Array[i] ^ Array[i + 1];

				Rt = i;
			}
		}
		if (R == Rt)
			return;
		L = Lt;
		for (int i = R; i > L; i--)
		{
			bool ch = false;
			if (oder > 0)
			{
				if (Array[i] < Array[i - 1])
					ch = true;
			}
			else
				if (Array[i] > Array[i - 1])
					ch = true;

			if (ch)
			{
				Array[i] = Array[i] ^ Array[i - 1];
				Array[i - 1] = Array[i] ^ Array[i - 1];
				Array[i] = Array[i] ^ Array[i - 1];
				Lt = i;
			}
		}
	}
}
int Darray::FindKey(int value) const//найти значение
{
	for (int i = 0; i < size; i++)
	{
		if (value == Array[i])
			return i;
	}
	return -1;
}
void Darray::AddKey(int ix, int value)//добавить элемент по индексу
{
	int* buffer = new int[size + 1];
	if (buffer)
	{
		for (int i = 0; i < ix; i++)
		{
			buffer[i] = Array[i];
		}
		buffer[ix] = value;
		for (int i = ix+1, k = ix; k < size; i++, k++)
		{
			buffer[i] = Array[k];
		}
		size++;
		Array = buffer;
	}
	else throw 2;
}
void Darray::Update(int min = 0, int max = 0, int align = 0)//обновить массив
{
	if (max < min)
		throw 1;
	for (int i = 0; i < size; i++)
		Array[i] = min + rand() % (min - max + 1);
	if (align)
			Sort(align);
}
const Darray& Darray::operator = (const Darray& obj)//присваивание обьектов
{
	if (this != &obj)//если изначально не равны
	{
		delete[] Array;
		Array = new int[obj.size];
		size = obj.size;
		for (int i = 0; i < size; i++)
			Array[i] = obj[i];
	}
	return *this;
}
Darray Darray::operator+(const Darray& obj)//склейка массивов
{
	Darray result(size + obj.size);
	for (int i = 0; i < size; i++)
		result[i] = Array[i];
	for (int i = 0, k = size; i < obj.size; i++, k++)
		result[k] = obj.Array[i];
	return result;
}
Darray Darray::operator+(int value)//добавить значение в конец
{
	Darray result(size + 1);
	for (int i = 0; i < size; i++)
		result[i] = Array[i];
	result[size + 1] = value;
	return result;
}
int& Darray::operator[](int i) const
{
	if (i > -1 && i < size)
	  return Array[i];
	throw 3;
}
bool Darray::operator==(Darray& obj)
{
	if (size == obj.size)
	{
		for (int i = 0; i < size; i++)
			if (Array[i] != obj[i])
				return false;
			return true;
	}
	return false;
}
Darray Darray::operator-(int value)//удалить значение
{
	int ix = FindKey(value);
		if (ix > -1)
		{
			Darray result(size - 1);
			for (int i = 0; i < ix; i++)
				result[i] = Array[i];
			for (int i = ix, k =ix+1; k < size; i++, k++)
				result[i] = Array[k];
			return result;
		}
		else throw 1;
}
bool Darray::operator!=(const Darray& obj)
{
	if (size == obj.size)
	{
		for (int i = 0; i < size; i++)
			if (Array[i] != obj[i])
				return true;
		return false;
	}
	return true;
}
istream& operator >>(istream& in, Darray& obj)
{
	if (obj.Array)
		delete[] obj.Array;
	int n;
	in >> n;
	obj.size = n;
	obj.Array = new int[n];
	for (int i = 0; i < obj.size; i++)
		in >> obj[i];
	return in;
}
ostream& operator <<(ostream& out, Darray& obj)
{
	for (int i = 0; i < obj.size; i++)
		out << obj[i]<<' ';
	return out;
}
int main()
{
	srand(time(0));
	try
	{
		Darray a(20, 3 ,100 , -1);
		Darray b(10, 2, 500 , -1);
		Darray c;
		cout << "a = " << a << endl;
		cout << "b = " << b << endl;
		c = a + b;
		cout << "c = a+b" << endl<< "c = " << c << endl;
		c[0] = a[0] + b[0];
		cout << "c = a[0] + b[0]"<<endl<<"c = " << c << endl;
		a.AddKey(1,5);
		cout << "a.Addkey(1,5) = " << a << endl;
		c = a - 5;
		cout << "c = a - 5 " << endl<< "c = " << c << endl;
	}
	catch (std::bad_array_new_length) {
		std::cerr << "wrong array size"<<endl;
	}
	catch (int i)
	{
		if (i == 1)
			cout << "wrong input" << endl;
		if (i == 2)
			cout << "wrong ptr" << endl;
		if (i == 3)
			cout << "wrong index" << endl;
	}
}