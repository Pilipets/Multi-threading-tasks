#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "Default ctor called" << endl;
	}
	A(const A&)
	{
		cout << "Copy ctor called" << endl;
	}
	A(A&&)
	{
		cout << "Move ctor called" << endl;
	}
	A& operator=(A&&)
	{
		cout << "Move assignment called" << endl;
	}
	A& operator=(const A&)
	{
		cout << "Assignment called" << endl;
	}
};

void method(int a, A &&tmp)
{
	A res = std::move(tmp);
}
int main()
{
	method(2, A());
	system("pause");
	return 0;
}