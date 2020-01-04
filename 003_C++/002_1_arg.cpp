#include <iostream> // input / output
#include <thread>   // thread api

void fun(int arg1, int* arg2, int& arg3, int && arg4)
{
	arg1  = 10;
	*arg2 = 20;
	arg3  = 30;
}

int foo()
{
	return 4;
}

int main(int argc, char* argv[])
{
	int a = 1; 
	int b = 2;
	int c = 3;

	std::thread th{fun, a, &b, std::ref(c), foo()};
	th.join(); 

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;

	return 0;
}
