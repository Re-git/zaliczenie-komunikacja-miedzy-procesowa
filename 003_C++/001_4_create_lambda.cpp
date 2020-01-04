#include <iostream> // input / output
#include <thread>   // thread api

int main(int argc, char* argv[])
{
	std::cout << "Main thread\n";

	std::thread th([]() {
			std::cout << "New thread\n";
			std::this_thread::sleep_for(std::chrono::seconds(5));
		});

	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
