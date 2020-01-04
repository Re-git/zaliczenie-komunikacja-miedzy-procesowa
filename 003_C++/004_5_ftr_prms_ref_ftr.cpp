#include <iostream> // input / output
#include <string>   // std::string
#include <future>   // std::future, std::promise
#include <thread>   // std::thread

void thFun(std::future<std::string>& ftr)
{
	//get output (future)
	std::string str = ftr.get();
	std::cout << "New thread after get : " << str << std::endl;
}

// important - future & promise can be used nly once !!!

int main(int argc, char* argv[])
{
	//create promise (input) - shared state is alocated
	std::promise<std::string> prms;

	//obtain future from promise (output) - shared state is shared
	std::future<std::string> ftr = prms.get_future();

	//share the output(fututre) with new thread
	//output is still available to this thread (now it's shared)
	std::thread th(&thFun, std::ref(ftr));
	
	//set input (promise)
	std::this_thread::sleep_for(std::chrono::seconds(5));
	prms.set_value("Hello world");

	th.join();
	return 0;
}

