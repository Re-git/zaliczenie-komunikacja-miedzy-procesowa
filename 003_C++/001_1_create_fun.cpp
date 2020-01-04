#include <iostream> // input / output
#include <thread>   // thread api

void fun()
{
	std::cout << "New thread\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main(int argc, char* argv[])
{
	std::cout << "Main thread\n";
	std::thread th{fun}; // uniform initialization
	//std::thread th(fun);
	
	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
