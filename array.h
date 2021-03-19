#include <iostream>
class Darray
{
private:
	int* Array;
	int size;
public:
	Darray(int n, int min, int max, int align);
	Darray(const Darray&);
	Darray(int* Array, int n);
	~Darray();
	void AddKey(int ix, int value);
	void Update(int min , int max , int align);
	void Sort(int);
	int FindKey(int) const;
	int& operator [] (int) const;
	bool operator == (Darray&);
	Darray operator+(const Darray& obj);
	Darray operator+(int value);
	Darray operator-(int value);
	const Darray& operator=(const Darray& obj);
	bool operator!=(const Darray& obj);
	friend std::istream& operator >> (std::istream& in, Darray& obj);
	friend std::ostream& operator << (std::ostream& out, Darray& obj);
};
