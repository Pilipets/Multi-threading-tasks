#include <iostream>
using namespace std;

template<class T = int>
class Sample {};

int main()
{
	Sample<>* instance;
	return 0;
}