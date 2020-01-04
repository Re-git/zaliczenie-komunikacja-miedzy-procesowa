#include <iostream> // input / output
#include <thread>   // thread api
#include <vector>   // std::vector

int main(int argc, char* argv[])
{
	std::vector<std::thread> my_threads;
	for(int i = 0 ; i < 10 ; i++) {
		my_threads.push_back(std::thread([](){
			std::cout << "New thread id = " << std::this_thread::get_id() << std::endl;
		}));
	}

	for(std::thread& th : my_threads) {
		std::cout << "Main thread id = " << th.get_id() << std::endl;
		th.join();
	}

	return 0;
}
