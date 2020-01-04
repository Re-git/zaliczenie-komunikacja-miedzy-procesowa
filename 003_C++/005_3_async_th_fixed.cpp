#include <iostream>           // input / output
#include <thread>             // std::thread
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable

std::mutex my_mutex;
std::condition_variable my_cond;

void factorial(int N, int& x)
{
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;

	std::unique_lock<std::mutex> lk(my_mutex);
		x = res;
		my_cond.notify_one();
}

int main(int argc, char* argv[])
{
	int result = 0;
	std::thread th(factorial, 4, std::ref(result));
	
	//when the result will be ready?
	//we could just th.join()
	
	std::unique_lock<std::mutex> lk(my_mutex);
		while(result == 0) { //spurious wakeup
			my_cond.wait(lk);
		}
	lk.unlock();
	std::cout << "result = " << result << std::endl;
	
	th.join();

	return 0;
}

