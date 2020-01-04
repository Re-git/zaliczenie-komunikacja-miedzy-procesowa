#include <iostream> // input / output
#include <thread>   // thread api

class My_Thread
{
public:
	void th_fun()  {
		std::cout << "New thread\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
};

int main(int argc, char* argv[])
{
	std::cout << "Main thread\n";
	My_Thread myTh;
	
	std::thread th{&My_Thread::th_fun, &myTh};
	//std::thread th(&My_Thread::th_fun, &myTh);
	
	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
