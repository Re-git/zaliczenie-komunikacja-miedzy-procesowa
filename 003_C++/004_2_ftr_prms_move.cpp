#include <iostream> // input / output
#include <string>   // std::string
#include <future>   // std::future, std::promise
#include <thread>   // std::thread

void thFun(std::promise<std::string>&& prms)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//set input (promise)
	prms.set_value("Hello world");
}

int main(int argc, char* argv[])
{
	//create promise (input) - shared state is alocated
	std::promise<std::string> prms;

	//obtain future from promise (output) - shared state is shared
	std::future<std::string> ftr = prms.get_future();

	//move the input(promise) to new thread
	//input is no loger available to this thread
	std::thread th(&thFun, std::move(prms));

	//get output (future) - wait till is ready
	std::string str = ftr.get();

	std::cout << str << std::endl;
	th.join();
	return 0;
}

