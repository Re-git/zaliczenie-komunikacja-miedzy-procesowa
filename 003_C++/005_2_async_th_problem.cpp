#include <iostream> // input / output
#include <thread>   // std::thread

void factorial(int N, int& x)
{
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;

	x = res;
}

int main(int argc, char* argv[])
{
	int result;
	std::thread th(factorial, 4, std::ref(result));
	
	th.join();
	std::cout << "result = " << result << std::endl;

	return 0;
}

