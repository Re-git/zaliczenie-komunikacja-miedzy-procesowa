#include <iostream> // input / output
#include <thread>   // std::thread
#include <future>   // std::future, std::promise

int main(int argc, char* argv[])
{
	int result = 0;

	// INPUT
	std::promise<int> p;
	// OUTPUT
	std::future<int> f = p.get_future();
	// shared OUTPUT
	std::shared_future<int> sf = f.share();
	 
	std::future<int> fu_factorial = std::async(
		[](std::shared_future<int>& sf)
		{
			// wait till input is ready
			int N = sf.get();
			int res = 1;
			for(int i = 1 ; i <= N ; i++)
				res *= i;
			return res;
		}, 
		std::ref(sf)
	);

	std::future<int> fu_sum = std::async(
		[](std::shared_future<int>& sf)
		{
			// wait till input is ready
			int N = sf.get();
			int res = 0;
			for(int i = 1 ; i <= N ; i++)
				res += i;
			return res;
		}, 
		std::ref(sf)
	);	

	// data for syncs not ready yet
	std::this_thread::sleep_for(std::chrono::seconds(5));
		
	//set INPUT
    p.set_value(4);	
	
	result = fu_factorial.get();
	std::cout << "Main thread: factorial result = " << result << std::endl;
	
	result = fu_sum.get();
	std::cout << "Main thread: sum result = " << result << std::endl;

	return 0;
}

