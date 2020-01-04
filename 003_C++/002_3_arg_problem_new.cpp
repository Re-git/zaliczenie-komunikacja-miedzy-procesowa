#include <iostream> // input / output
#include <thread>   // thread api

void fun(int* ptr)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "zapisujemy...\n";
	*ptr = 20;
}

void createThread()
{
	int* i = new int();
	std::thread th(fun, i);
	delete i;
	th.detach(); // nie czekamy na zakonczenie watku
}

int main(int argc, char* argv[])
{
	createThread();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}
