#include <iostream> // input / output
#include <thread>   // std::thread
#include <future>   // std::future, std::promise

int factorial(int N)
{
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;
	
	//std::this_thread::sleep_for(std::chrono::seconds(5));
	return res; // return as future
}

int main(int argc, char* argv[])
{
	int result = 0;
	
	// async has output
	std::future<int> fu = std::async(factorial, 4);	
	
	// let's wait till return value is ready
	result = fu.get();
	std::cout << "result = " << result << std::endl;

	return 0;
}

